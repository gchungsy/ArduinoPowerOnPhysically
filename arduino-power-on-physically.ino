 #include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial SerialBT(10, 11); // RX | TX 
Servo myServo;

const int buttonPin = 2;
int switchState = 0;

char flag = '0'; 

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Serial Port
  Serial.begin(9600);
  Serial.println("Connect to HC-05 with 1234 as pairing key!");

  // Bluetooth Serial
  SerialBT.begin(9600); 
  
  // Servo
  myServo.attach(9);
  myServo.write(0);
}

void pressButton() {
  myServo.write(35);
  delay(500);
  myServo.write(0);
}

void loop() {
  if (SerialBT.available()) {
    flag = SerialBT.read();
    Serial.write(flag);
  }
  switchState = digitalRead(buttonPin);
  if(switchState == HIGH) {
    pressButton();
    delay(3000);
  } else {
    if(flag == '1') {
    pressButton();
    flag = '0';
    }
  }
}
