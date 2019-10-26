 #include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "dht.h"

LiquidCrystal lcd(8, 6, 5, 4, 3, 2); // LiquidCrystal(RS, E, D4, D5, D6, D7)

#define dht_apin 12
#define PERIOD 2000000 // 2s or 200 ms

dht DHT;

SoftwareSerial SerialBT(10, 11); // RX | TX 
Servo myServo;

const int buttonPin = 7;
const int servoPin = 9;
int switchState = 0;

char flag = '0'; 

unsigned long S_START = 0L;

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Serial Port
  Serial.begin(9600);
  Serial.println("Connect to HC-05 with 1234 as pairing key!");

  // Bluetooth Serial
  SerialBT.begin(9600); 
  
  // Servo
  myServo.attach(servoPin);
  myServo.write(0);

  // LCD
  lcd.begin(16, 2);
  lcd.print("Hello, world!");
  lcd.clear();
  lcd.setCursor(0,0); 
}

void pressButton() {
  myServo.write(35);
  delay(500);
  myServo.write(0);
}

void loop() {

  if (micros() - S_START > PERIOD)
  {
    S_START = micros();
    DHT.read11(dht_apin);
    lcd.setCursor(0,0); 
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
  }
//  Serial.print("Current humidity = ");
//  Serial.print(DHT.humidity);
//  Serial.print("%  ");
//  Serial.print("temperature = ");
//  Serial.print(DHT.temperature); 
//  Serial.println("C  ");
  
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
