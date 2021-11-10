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
    int grow_rate = 1;
    int decay_rate = 1;
public:
    ControlPoint(int initialValue, int max, int min, int growRate, int decayRate) {
        this->initialValue = initialValue;
        this->max = max;
        this->min = min;
        this->grow_rate = growRate;
        this->decay_rate = decayRate;
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
    int getDecayRate() { return decay_rate; }
    int getGrowRate() { return grow_rate; }

    void grow(int amount){
        setValue(getValue() + amount);
    }
    void grow() { grow(grow_rate); }

    void decay(int amount){
        if (amount < 0){
            grow(-amount);
        }
        
    }

    void decay(){
        decay(decay_rate);
    }
};


void setup(){

}

void loop(){

}