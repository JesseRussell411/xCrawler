/////////////
// Author: Jesse Russell

int sign(int value)
{
  if (value < 0)
    return -1;
  else if (value > 0)
    return 1;
  else
    return 0;
}

class Interval
{
private:
  int (*action)();
  unsigned long interval;
  unsigned long start;

public:
  Interval() = default;
  Interval(int (*action)(), unsigned long interval)
  {
    this->interval = interval;
    this->action = action;
    this->start = millis();
  }

  unsigned long getInterval() const { return interval; }
  void setInterval(unsigned long value) { interval = value; }

  int update()
  {
    unsigned long now = millis();
    unsigned long ellapsed = now - start;
    if (ellapsed >= interval)
    {
      start = now - (ellapsed - interval);
      return action();
    }
    else
      return 0;
  }
};

class Motor
{
private:
  int speed;
  bool direction;
  int speedControlPin;
  int directionControlPin1;
  int directionControlPin2;
  int maxSpeed;
  int minSpeed;

  void apply()
  {
    if (direction)
    {
      digitalWrite(directionControlPin1, HIGH);
      digitalWrite(directionControlPin2, LOW);
    }
    else
    {
      digitalWrite(directionControlPin1, LOW);
      digitalWrite(directionControlPin2, HIGH);
    }

    analogWrite(speedControlPin, speed);
  }

public:
  Motor(int speedControlPin, int directionControlPin1, int directionControlPin2, int maxSpeed, int minSpeed)
  {
    this->speedControlPin = speedControlPin;
    this->directionControlPin1 = directionControlPin1;
    this->directionControlPin2 = directionControlPin2;
    this->maxSpeed = maxSpeed;
    this->minSpeed = minSpeed;
  }
  Motor() = default;

  void setSpeed(int speed)
  {
    speed = max(min(speed, maxSpeed), minSpeed);

    this->speed = abs(speed);
    //this->speed = speed;
    this->direction = speed > 0;
    apply();
  }

  int getSpeed() { return speed * (direction ? 1 : -1); }
  int getMaxSpeed() { return maxSpeed; }
  int getMinSpeed() { return minSpeed; }
  int getSpeedControlPin() { return speedControlPin; }
  int getDirectionControlPin1() { return directionControlPin1; }
  int getDirectionControlPin2() { return directionControlPin2; }

  void addSpeed(int speed)
  {
    setSpeed(min(max(getSpeed() + speed, minSpeed), maxSpeed));
  }
};

//=============================================================================================================================

//============== parameters ===========
const int decay = 15;
const int decay_f = 50;
const int acceleration = 200;
//===================================

Motor left = Motor(5, 6, 7, 255, -255);
Motor right = Motor(10, 8, 9, 255, -255);

// Interval left_decay, right_decay, status;
Interval left_decay = Interval([]()
                               {
                                 if (abs(left.getSpeed()) <= decay)
                                   left.setSpeed(0);
                                 else
                                   left.addSpeed(sign(left.getSpeed()) * -decay);
                                 return 1;
                               },
                               decay_f);

Interval right_decay = Interval([]()
                                {
                                  if (abs(right.getSpeed()) <= decay)
                                    right.setSpeed(0);
                                  else
                                    right.addSpeed(sign(right.getSpeed()) * -decay);
                                  return 1;
                                },
                                decay_f);

Interval status = Interval([]()
                           {
                             Serial.println(left.getSpeed());
                             Serial.println(right.getSpeed());
                             Serial.println();
                             return 1;
                           },
                           500);

// =============== accessories ===========
const int seedSowerControlPin = 11;
bool seedSowerRunning = false;
int seedSowerSpeed = 150;
bool accessory0_toggle()
{
  seedSowerRunning = !seedSowerRunning;

  if (seedSowerRunning)
  {
    analogWrite(seedSowerControlPin, seedSowerSpeed);
  }
  else
  {
    analogWrite(seedSowerControlPin, 0);
  }
}
//=========================================

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  left.setSpeed(0);
  right.setSpeed(0);

  Serial.begin(38400);
  Serial.setTimeout(10);

  Serial.print("ready!\n");
}

void loop()
{

  left_decay.update();
  right_decay.update();
  //  status.update();

  if (Serial.available())
  {
    char c = Serial.read();

    switch (c)
    {
    case 'R':
      right.addSpeed(acceleration);
      break;
    case 'r':
      right.addSpeed(-acceleration);
      break;
    case 'L':
      left.addSpeed(acceleration);
      break;
    case 'l':
      left.addSpeed(-acceleration);
      break;
    case 's':
      left.setSpeed(0);
      right.setSpeed(0);
      break;
    case '0':
      accessory0_toggle();
      break;

    // case '1':
    //   seedSowerSpeed += 1;
    //   digitalWrite(seedSowerControlPin, seedSowerSpeed);
    //   break;
    // case '2':
    //   seedSowerSpeed -= 1;
    //   digitalWrite(seedSowerControlPin, seedSowerSpeed);
    //   break;
    // case '3':
    //   Serial.println(seedSowerSpeed);
    //   break;
    }
  }
}