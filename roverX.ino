
char inputByte;

int moter1pin1 = 2;
int moter1pin2 = 3;

int moter2pin1 = 4;
int moter2pin2 = 5;

int bluetoothpin = 1

avoid setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) {

    //bluetooth
    pinMode(bluetoothpin, OUTPUT);

    //motors
    pinMode(moter1pin1, OUTPUT);
    pinMode(moter1pin2, OUTPUT);
    pinMode(moter2pin1, OUTPUT);
    pinMode(moter2pin2, OUTPUT);

    //speed control
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    //LED
    pinMode(13, OUTPUT);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0) {
    inputByte = Serial.read();
    Serial.println(inputByte);

    // 0 = off and 255 = max
    analogWrite(9, 100); //ENA pin
    analogWrite(10, 200); //ENB pin

    if (inputByte == 'F') {
      //move forward
      digitalWrite(moter1pin1, HIGH)
      digitalWrite(moter2pin1, HIGH)
      
    } else if (inputByte == 'B') {
      //move backward

    } else if (inputByte == 'R')  {
      // turn right
      digitalWrite(moter1pin1, HIGH)
      digitalWrite(moter2pin1, LOW)
    } else if (inputByte == 'L') {
      // turn left
      digitalWrite(moter1pin1, LOW)
      digitalWrite(moter2pin1, HIGH)
    }
  }
}
