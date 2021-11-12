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

  int update(){
    unsigned long now = millis();
    unsigned long ellapsed = now - start;
    if (ellapsed >= interval){
      start = now - (ellapsed - interval);
      return action();
    } else return 0;
  }
};

#define LED_2 12
#define LED_3 11
#define INTERVAL_COUNT 3

Interval intervals[INTERVAL_COUNT];


int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_2, OUTPUT);

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

 intervals[2] = Interval([](){
    
    if(ledState3 == LOW){
      ledState3 = HIGH;
    }else{
      ledState3 = LOW;
    }
    

    digitalWrite(LED_3, ledState3);

    return 0;
  }, 1000);

}

void loop() {
  for(int i = 0; i < INTERVAL_COUNT; ++i){
    intervals[i].update();
  }
}
