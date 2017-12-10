int extendPin = 2;
int retractPin = 3;
String data;
int state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(extendPin, OUTPUT);
  pinMode(retractPin, OUTPUT);
  digitalWrite(extendPin, HIGH);
  digitalWrite(retractPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    delay(6);  
    char c = Serial.read();
    data += c; 
  }
  if(data == "open") {
    digitalWrite(retractPin, LOW);
    digitalWrite(extendPin, HIGH);
  }
  else if (data == "close") {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, LOW);
  }
  else if (data == "stop") {
    digitalWrite(retractPin, HIGH);
    digitalWrite(extendPin, HIGH);
  }
  data = "";
}
