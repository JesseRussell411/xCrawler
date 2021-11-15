class Motor
{
private:
    int speed;
    bool direction;
    int speedControlPin;
    int directionControlPin1;
    int directionControlPin2;

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
    Motor(int speedControlPin, int directionControlPin1, int directionControlPin2)
    {
        this->speedControlPin = speedControlPin;
        this->directionControlPin1 = directionControlPin1;
        this->directionControlPin2 = directionControlPin2;
    }

    void setSpeed(int speed)
    {
        this->speed = abs(speed);
        this->direction = speed > 0;
        apply();
    }

    int getSpeed()
    {
        return speed * direction > 0 ? 1 : -1;
    }

    void addSpeed(int speed)
    {
        setSpeed(getSpeed() + speed);
    }
};