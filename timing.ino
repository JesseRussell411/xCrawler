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

class PulseInterval{
private:
  int (*action)(bool);
  unsigned long onTime, offTime;
  unsigned long start;
  bool on = false;
public:
  PulseInterval() = default;
  PulseInterval(int (*action)(), unsigned long onTime, unsigned long offTime){
    this->onTime = onTime;
    this->offTime = offTime;
    this->action = action;
    this->start = millis();
  }

  unsigned long getOnTime() const { return onTime; }
  unsigned long getOffTime() const { return offTime; }
  void setOnTime(unsigned long value) { onTime = value; }
  void setOffTime(unsigned long vlaue) { offTime = vlaue; }


  int update(){
    unsigned long now = millis();
    unsigned long ellapsed = now - start;
    unsigned long time = on ? onTime : offTime;

    if (ellapsed >= time){
      start = now - (ellapsed - time);
      on = !on;
      return action(on);
    } else return 0;
  }
};

#define LED_2 12
#define LED_3 11
#define INTERVAL_COUNT 2
#define PULSE_INTERVAL_COUNT 1

PulseInterval pulseIntervals[PULSE_INTERVAL_COUNT];
Interval intervals[INTERVAL_COUNT];


int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  intervals[0] = Interval([](){
    
    if(ledState1 == LOW){
      ledState1 = HIGH;
    }else{
      ledState1 = LOW;
    }
    

    digitalWrite(LED_BUILTIN, ledState1);

    return 0;
  }, 500);

  intervals[1] = Interval([](){
    
    if(ledState2 == LOW){
      ledState2 = HIGH;
    }else{
      ledState2 = LOW;
    }
    

    digitalWrite(LED_2, ledState2);

    return 0;
  }, 200);

  pulseIntervals[0] = PulseInterval([](bool on){
    digitalWrite(LED_3, on);

    return 0;
  }, 200, 800);

//  intervals[2] = Interval([](){
    
//     if(ledState3 == LOW){
//       ledState3 = HIGH;
//     }else{
//       ledState3 = LOW;
//     }
    

//     digitalWrite(LED_3, ledState3);

//     return 0;
//   }, 1000);

}

void loop() {
  for(int i = 0; i < INTERVAL_COUNT; ++i){
    intervals[i].update();
  }
  for(int i = 0; i < PULSE_INTERVAL_COUNT; ++i){
    pulseIntervals[i].update();
  }
}
