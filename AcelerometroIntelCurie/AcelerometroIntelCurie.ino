#include "CurieIMU.h"

void setup() {
  Serial.begin(9600); //initialize serial communi
  while (!Serial);    //wait for the serial port

  //initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();
  
  //Set the accelerometer range to 250 degrees/se
  CurieIMU.setGyroRange(250);
}

void loop() {
  int gxRaw, gyRaw, gzRaw; //raw gyro values
  float gx, gy, gz;

  //read raw gyro measuremnts from device
  CurieIMU.readGyro(gxRaw, gyRaw, gzRaw);

  //convert the raw gyro data to degrees/seco
  gx = convertRawGyro(gxRaw);
  gy = convertRawGyro(gyRaw);
  gz = convertRawGyro(gzRaw);

  //display tab-separated gyro x/y/z values
  Serial.print("g:\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.print(gz);
  Serial.println();

  delay(700);
}

float convertRawGyro(int gRaw) {
  //since we are using 250 degrees/seconds range
  //-250 maps to a raw value of -32768
  //+250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 327768.0;

  return g;
}
