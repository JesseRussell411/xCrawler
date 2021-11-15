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