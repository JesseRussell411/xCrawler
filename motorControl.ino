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
        this->maxSpeed;
        this->minSpeed;
    }

    void setSpeed(int speed)
    {
        this->speed = abs(speed);
        this->direction = speed > 0;
        apply();
    }

    int getSpeed() { return speed * ((direction > 0) ? 1 : -1); }
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