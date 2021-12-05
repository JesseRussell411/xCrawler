class Interval{
private:
  int (*action)();
  unsigned long interval;
  unsigned long start;
public:
  Interval() = default;
  Interval(int (*action)(), unsigned long interval){
    this->interval = interval;
    this->action = action;
    this->start = millis();
  }

  unsigned long getInterval() const { return interval; }
  void setInterval(unsigned long value) { interval = value; }

  int update(){
    unsigned long now = millis();
    unsigned long ellapsed = now - start;
    if (ellapsed >= interval){
      start = now - (ellapsed - interval);
      return action();
    } else return 0;
  }
};

int sign(int value){
    if (value < 0)
        return -1;
    else if (value > 0)
        return 1;
    else
        return 0;
}

class ControlPoint{
private:
    int value = 0;
    int initialValue = 0;
    int max = 100;
    int min = 100;
    int growRate = 1;
    int decayRate = 1;

public:
    ControlPoint(int initialValue, int max, int min, int growRate, int decayRate) {
        this->initialValue = initialValue;
        this->max = max;
        this->min = min;
        this->growRate = growRate;
        this->decayRate = decayRate;
    }
    int getValue() { return value; }
    int setValue(int value){
        if (value > max)
            this->value = max;
        else if (value < min)
            this->value = min;
        else
            this->value = value;
    }
    int getMax() { return max;}
    int getMin() { return min;}
    int getDecayRate() { return decayRate; }
    int getGrowRate() { return growRate; }

    void grow(int amount){
        setValue(getValue() + amount);
    }
    void grow() { grow(growRate); }

    // decays value
    void decay(int amount){
        if (amount < 0){
            grow(-amount);
            return;
        }
        int value_abs = abs(value);

        if (value_abs <= amount){
            value = 0;
        } else{
            value = (value_abs - amount) * sign(value);
        }
    }
    // decays value at default rate
    void decay(){
        decay(decayRate);
    }
};

#define CONTROL 3
ControlPoint speed = ControlPoint(0, 255, 0, 20, 5);
const int intervalCount = 2;
Interval intervals[intervalCount];


void setup() 
{
  Serial.begin(38400);         //Sets the data rate in bits per second (baud) for serial data transmission
  intervals[0] = Interval([](){
//    Serial.print(speed.getValue());
//    Serial.print('\n');

    return 0;
}, 5000);

intervals[1] = Interval([](){
    speed.decay();
    analogWrite(CONTROL, speed.getValue());

    return 0;
}, 100);

}
void loop()
{
  if(Serial.available() > 0)  
  {
   char incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
   Serial.print(incoming_value);
   Serial.print('\n');
   if (incoming_value == 'F') {
       speed.grow();
   } else if (incoming_value == 'R') {
       speed.grow(speed.getGrowRate() * -1);
   }

    

     analogWrite(CONTROL, speed.getValue());
  }               

  for(int i = 0; i < intervalCount; ++i){
      intervals[i].update();
  }          
 
}                 
