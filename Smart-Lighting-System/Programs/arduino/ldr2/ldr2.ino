// https://forum.arduino.cc/t/speed-measurement-with-2-LDR-sensors-help/537046
// https://forum.arduino.cc/t/calculate-distance-of-light-source-with-voltage-changes-of-analog-input-with-LDR/521967/6
// 

int LDR1 = 2;
int LDR2 = 3;

int LDR1_flag1 = 0, LDR1_flag2 = 0, LDR2_flag1=0, LDR2_flag2=0;

// the most first time that a car passes throught the LDR and stay some time then departure it
long int LDR1_first_arrival_time, LDR2_first_arrival_time, LDR1_arrival_time, LDR2_arrival_time;
long int LDR1_first_departure_time, LDR2_first_departure_time;

double distance; // distance between the two sensors
long int time_from_LDR1_to_LDR2; // it is the time since the arrival of first sensor to second sensor


void setup()
 {
  //Initialize Sensor (pin2) as an INPUT.
  pinMode (LDR1, INPUT);
  pinMode (LDR2, INPUT);
  //Define baud rate for serial communication
  Serial.begin (9600);
  
 }
 
void loop()
 {
  //Read Digital output value from sensor using digitalRead()function
  int LDR1Data = digitalRead (LDR1);
  int LDR2Data = digitalRead (LDR2);
  //Print the sensor value on your serial monitor window

  readSensorValOnce(LDR1Data, 1);
  readSensorValOnce(LDR2Data, 2);
  
  if (LDR1_flag2 && LDR2_flag1){
    Serial.print("Time between two sensors: ");
    time_from_LDR1_to_LDR2 = LDR2_first_arrival_time - LDR1_first_departure_time;
    Serial.println(time_from_LDR1_to_LDR2);
     
  }
  Serial.print("Sensor value: ");
  Serial.print(LDR1Data);
  Serial.print(" -- ");
  Serial.println(LDR2Data);
  
  
//  readSensorValEachArrival(LDR1Data, 1);
//  readSensorValEachArrival(LDR2Data, 2);
 
//  if (LDR1_flag2){
//    Serial.print("total taken time ");
//    Serial.println(LDR1_first_departure_time - LDR1_first_arrival_time);
//  }
  
  //Delay for 1 second to get clear output on the serial monitor
  delay(500);
 }

 void readSensorValOnce(int data, int sensor_no){
  if (sensor_no == 1){
    if (data && !LDR1_flag1) {
    LDR1_first_arrival_time = millis();
    
    Serial.print("ldr1 first arriaval time: ");
    Serial.println(LDR1_first_arrival_time);
    LDR1_flag1 = 1;
    }
    if ( !data && LDR1_first_arrival_time !=0 && !LDR1_flag2){
      LDR1_first_departure_time = millis();
      Serial.print("Departure time 1:");
      Serial.println(LDR1_first_departure_time);
      LDR1_flag2 = 1;
    }
   }
   else if(sensor_no == 2){
    if (data && !LDR2_flag1) {
      
    LDR2_first_arrival_time = millis();
    
    Serial.print("ldr2 first arriaval time: ");
    Serial.println(LDR2_first_arrival_time);
    LDR2_flag1 = 1;
    }
    if ( !data && LDR2_first_arrival_time !=0 && !LDR2_flag2){
      LDR2_first_departure_time = millis();
      Serial.print("Departure time 2:");
      Serial.println(LDR2_first_departure_time);
      LDR2_flag2 = 1;
    }
   }
 }

 void readSensorValEachArrival(int data, int sensor_no){
  if (data) {
  if (sensor_no ==1) {
    LDR1_arrival_time = millis();
    Serial.print("time arrive 1:");
    Serial.println(LDR1_arrival_time);
  }else{
    LDR2_arrival_time = millis();
    Serial.print("time arrive 2:");
    Serial.println(LDR2_arrival_time);
  }
  
  }
 }
