#include <SoftwareSerial.h>

#define EXTEND 0
#define RETRACT 1
#define HOLD 2

int sensorPin = 2;
SoftwareSerial bluetooth(4,5);
int extendPin = 6;
int retractPin = 7;
String data;
int pos = 0;
int state = HOLD;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(extendPin, OUTPUT);
  pinMode(retractPin, OUTPUT);
  digitalWrite(extendPin, HIGH);
  digitalWrite(retractPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulse, RISING); 
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bluetooth.listen();
  while (bluetooth.available()) {
    delay(6);
    char c = bluetooth.read();
    data += c;
  }
  if (data == "open" && pos > 0) {
    digitalWrite(retractPin, LOW);
    digitalWrite(extendPin, HIGH);
    state = RETRACT;
  }
  else if (data == "close" && pos < 852) {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, LOW);
    state = EXTEND;
  }
  else if (data == "stop") {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, HIGH);
    state = HOLD;
  }
  if (pos >= 852 && state == EXTEND) {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, HIGH);
    state = HOLD;
  }
  else if (pos <= 0 && state == RETRACT) {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, HIGH);
    state = HOLD;    
  }
  data = "";
}

void pulse(){
  if(state == EXTEND) {
    pos++;
  }
  else if(state == RETRACT) {
    pos--;
  }
}

