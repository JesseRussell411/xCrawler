/*
Work in Progress
----------------

This code isn't even functional yet. It's just spaughetti thrown at the wall
in the hopes that some of it sticks.
*/


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


ControlPoint test(0, 100, -100, 1, 5);
void setup(){
    Serial.begin(9600);

}

void loop(){
    if (Serial.available() > 0){
        char 
    }
}