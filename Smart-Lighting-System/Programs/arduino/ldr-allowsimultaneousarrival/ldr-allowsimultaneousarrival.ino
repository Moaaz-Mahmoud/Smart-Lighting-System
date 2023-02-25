// https://forum.arduino.cc/t/speed-measurement-with-2-LDR-sensors-help/537046
// https://forum.arduino.cc/t/calculate-distance-of-light-source-with-voltage-changes-of-analog-input-with-LDR/521967/6
// 

#include "protothreads.h"
#include <Wire.h>


// I don't know what is this???????????????????
const int I2C_ADD =0x50;

pt ptReadSensors;
pt ptSerialPrint;

int LDR1 = 2;
int LDR2 = 4;
int LDR1Data, LDR2Data;

int LDR1_flag1 = 0, LDR1_flag2 = 0, LDR2_flag1=0, LDR2_flag2=0;

// the most first time that a car passes throught the LDR and stay some time then departure it
long int LDR1_first_arrival_time, LDR2_first_arrival_time, LDR1_arrival_time, LDR2_arrival_time;
long int LDR1_first_departure_time, LDR2_first_departure_time;

double distance = 0.172 ; // distance between the two sensors in meter
long int time_from_LDR1_to_LDR2; // it is the time since the arrival of first sensor to second sensor


void setup()
 {
  Wire.begin();

  PT_INIT(&ptReadSensors);
  PT_INIT(&ptSerialPrint);

  
  //Initialize Sensor (pin2) as an INPUT.
  pinMode (LDR1, INPUT);
  pinMode (LDR2, INPUT);
  //Define baud rate for serial communication
  Serial.begin (9600);
  
 }

 
 int readSensorsThread(struct pt* pt)
{
  PT_BEGIN(pt);
 
  while(true)
  {
   LDR1Data = digitalRead (LDR1);
   LDR2Data = digitalRead (LDR2);

  readSensorValOnce(LDR1Data, 1);
  readSensorValOnce(LDR2Data, 2);


   if (LDR1_flag2 && LDR2_flag1){
    time_from_LDR1_to_LDR2 = LDR2_first_arrival_time - LDR1_first_departure_time;
  }
//

  
  
//  readSensorValEachArrival(LDR2Data, 2);
//  readSensorValEachArrival(LDR1Data, 1);
  

  PT_SLEEP(pt, 50);
  }

  PT_END(pt);
}
 

int serialPrintThread(struct pt* pt)
{
  PT_BEGIN(pt);
 
  while(true)
  {
    


if (LDR1_flag2 && LDR2_flag1){
    Serial.print("Time between two sensors in s: ");
//    time_from_LDR1_to_LDR2 = LDR2_first_arrival_time - LDR1_first_departure_time;
    Serial.println((double)(time_from_LDR1_to_LDR2)/1000);
    Serial.print("Velocity in m/s is : ");
    Serial.println( (double)distance / (double)(time_from_LDR1_to_LDR2/1000) );
}
//Serial.print("Sensor value: ");
//  Serial.print(LDR1Data);
//  Serial.print(" -- ");
//  Serial.println(LDR2Data);
  
 
//  if (LDR1_flag2){
//    Serial.print("total taken time for sensor 1 ");
//    Serial.println(LDR1_first_departure_time - LDR1_first_arrival_time);
//  }

   if ( LDR1_flag1 && !LDR1_flag2 ){
    // You are still there in sensor 1
    if (LDR2_flag1 && !LDR2_flag2){
      // there are something on sensor 2 ALSO
      Serial.println("It is CROWDED!!");
    }
    
//    Serial.println(LDR2Data);
   }


  Wire.beginTransmission(I2C_ADD );
 Wire.write("We are sending from arduino!!!");
 Wire.endTransmission();

  PT_SLEEP(pt, 1000);
  }

  PT_END(pt);
}

void loop()
 {


  
  //Print the sensor value on your serial monitor window

  PT_SCHEDULE(readSensorsThread(&ptReadSensors));
  PT_SCHEDULE(serialPrintThread(&ptSerialPrint));


 }

// ----------------------------------------------------------- To split the sensors in two threads -------------------
 void readSensorValOnce(int data, int sensor_no){
  if (sensor_no == 1){
    if (data && !LDR1_flag1) {
    LDR1_first_arrival_time = millis();
    
    Serial.print("ldr1 first arriaval time: ");
    Serial.println(LDR1_first_arrival_time);
    
    LDR1_flag1 = 1;
  LDR1_flag2 = 0; //these additional lines . to be able to repeat the process
    }
    if ( !data && LDR1_first_arrival_time !=0 && !LDR1_flag2){
      LDR1_first_departure_time = millis();
      
      Serial.print("Departure time 1:");
      Serial.println(LDR1_first_departure_time);
      LDR1_flag2 = 1;
      LDR1_flag1 = 0;
    }
   }
   else if(sensor_no == 2){
    
    //if (LDR1_flag2){
      if (data && !LDR2_flag1) {
      
    LDR2_first_arrival_time = millis();
    
    Serial.print("ldr2 first arriaval time: ");
    Serial.println(LDR2_first_arrival_time);
    LDR2_flag1 = 1;
    LDR2_flag2 = 0;
    }
    if ( !data && LDR2_first_arrival_time !=0 && !LDR2_flag2){
      LDR2_first_departure_time = millis();
      Serial.print("Departure time 2:");
      Serial.println(LDR2_first_departure_time);
      LDR2_flag2 = 1;
      LDR2_flag1 = 0;
    }
  //  }
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



void sendToRaspPico(){
  
}
 
