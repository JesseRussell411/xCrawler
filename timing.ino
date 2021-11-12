class Interval{
private:
  bool (*action)();
  unsigned long interval;
  unsigned long start;
public:
  Interval(bool (*action)(), unsigned long interval){
    this->interval = interval;
    this->action = action;
  }

  bool update(){
    unsigned long now = millis();
    unsigned long ellapsed = now - start;
    if (ellapsed >= interval){
      return action();
      start = now - (ellapsed - interval);
    } else return false;
  }
}

class Timing{
private:
  
}




void (*todo1)();
void (*todo2)();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  todo1 = [](){digitalWrite(LED_BUILTIN, HIGH);};
  todo2 = [](){digitalWrite(LED_BUILTIN, LOW);};

}

void loop() {
  // put your main code here, to run repeatedly:
  todo1();
  delay(1000);
  todo2();
  delay(1000);
}
