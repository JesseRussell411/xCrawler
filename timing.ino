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


Interval interval;
int ledState = LOW;



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  interval = Interval([](){
    if(ledState == LOW){
      ledState = HIGH;
      Serial.println("H");
    }else{
      ledState = LOW;
      Serial.println("L");
    }
    

    digitalWrite(LED_BUILTIN, ledState);

    return 0;
  }, 900);

}

void loop() {
  // put your main code here, to run repeatedly:
  interval.update();
}
