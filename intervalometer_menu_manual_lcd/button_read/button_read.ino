
int sensorPin;
int sensorValue;
void setup(){
sensorPin = 0;    // select the input pin for the potentiometer

sensorValue = 0;
Serial.begin(9600);
}


void loop(){
  sensorValue = analogRead(sensorPin); 
  Serial.println(sensorValue);
  
}
