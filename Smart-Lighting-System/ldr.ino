// https://forum.arduino.cc/t/speed-measurement-with-2-ldr-sensors-help/537046
// https://forum.arduino.cc/t/calculate-distance-of-light-source-with-voltage-changes-of-analog-input-with-ldr/521967/6
// 

int LDRSensor = 7;

int ldrflag1 = 0, ldrflag2 = 0;
// the most first time that a car passes throught the ldr and stay some time then departure it
long int first_arrival_time, arrival_time;
long int first_departure_time;

double distance; // distance between the two sensors

void setup()
 {
  //Initialize Sensor (pin2) as an INPUT.
  pinMode (LDRSensor, INPUT);
  //Define baud rate for serial communication
  Serial.begin (9600);
  
 }
 
void loop()
 {
  //Read Digital output value from sensor using digitalRead()function
  int Sensordata = digitalRead (LDRSensor);
  //Print the sensor value on your serial monitor window

  readSensorValOnce(Sensordata);
  Serial.print("tt ");
  Serial.println(first_arrival_time);
//  readSensorValEachArrival(Sensordata);
  if (ldrflag2){
    Serial.print("total taken time ");
    Serial.println(first_departure_time - first_arrival_time);
  }
  
  //Delay for 1 second to get clear output on the serial monitor
  delay(1000);
 }

 void readSensorValOnce(int data){
  if (data && !ldrflag1) {
  first_arrival_time = millis();
  Serial.print("Sensor value:");
  Serial.println(data);
  ldrflag1 = 1;
  }
  if ( !data && first_arrival_time !=0 && !ldrflag2){
    first_departure_time = millis();
    Serial.print("Departure time:");
    Serial.println(first_departure_time);
    ldrflag2 = 1;
  }
 }

 void readSensorValEachArrival(int data){
  if (data) {
  arrival_time = millis();
  Serial.print("time value:");
  Serial.println(arrival_time);
  
  }
 }
