/* 
Dependencies:
*/

#include "sensors.h"

#define GYRO 0x68         // gyro I2C address
#define REG_GYRO_X 0x1D   // IMU-3000 Register address for GYRO_XOUT_H
#define ACCEL 0x53        // Accel I2c Address
#define ADXL345_POWER_CTL 0x2D

#define HMC5883_ADDRESS_MAG            (0x3C >> 1)         // 0011110x
#define HMC5883_REGISTER_MAG_CRB_REG_M 0x01
#define HMC5883_REGISTER_MAG_MR_REG_M  0x02
#define HMC5883_REGISTER_MAG_OUT_X_H_M 0x03

// Compensate static magnetic field
// Use sensorscalibration.ino to mesure these values for your baord
#define CalibrateX  -139
#define CalibrateY  -188
#define CalibrateZ  -372

void Sensors::init(void) {
  Wire.begin();  
  initAccelerometer();
  initMagnetometer();
}

void Sensors::initAccelerometer()
{
  // Set Gyro settings
  // Sample Rate 1kHz, Filter Bandwidth 42Hz, Gyro Range 500 d/s 
  writeTo(GYRO, 0x16, 0x0B);       
  //set accel register data address
  writeTo(GYRO, 0x18, 0x32);     
  // set accel i2c slave address
  writeTo(GYRO, 0x14, ACCEL);     
    
  // Set passthrough mode to Accel so we can turn it on
  writeTo(GYRO, 0x3D, 0x08);     
  // set accel power control to 'measure'
  writeTo(ACCEL, ADXL345_POWER_CTL, 8);     
  //cancel pass through to accel, gyro will now read accel for us   
  writeTo(GYRO, 0x3D, 0x28);   
}  

// Write a value to address register on device
void Sensors::writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}

void Sensors::readAccelerometer(int &x, int &y, int &z)
{
  byte buffer[12];   // Array to store ADC values 
  int accel_x;
  int accel_y;
  int accel_z;

  // read accelerometer
  // First set the register start address for X on Gyro  
  Wire.beginTransmission(GYRO);
  Wire.write(REG_GYRO_X); //Register Address GYRO_XOUT_H
  Wire.endTransmission();

  // New read the 12 data bytes
  Wire.beginTransmission(GYRO);
  Wire.requestFrom(GYRO,12); // Read 12 bytes
  int i = 0;
  while(Wire.available())
  {
      buffer[i] = Wire.read();
      i++;
  }
  Wire.endTransmission();

  //Combine bytes into integers
  // Gyro format is MSB first
  //gyro_x = buffer[0] << 8 | buffer[1];
  //gyro_y = buffer[2] << 8 | buffer[3];
  //gyro_z = buffer[4] << 8 | buffer[5];

  // Accel is LSB first. Also because of orientation of chips
  // accel y output is in same orientation as gyro x
  // and accel x is gyro -y
  accel_y = buffer[7] << 8 | buffer[6];
  accel_x = buffer[9] << 8 | buffer[8];
  accel_z = buffer[11] << 8 | buffer[10];
  
  // map axes
  x = -accel_x;
  y =  accel_z;
  z = -accel_y;
}    

void Sensors::initMagnetometer()
{
  // Enable the magnetometer
  writeTo(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_MR_REG_M, 0x00);
  
  // Set the gain to +/-1.3 (max sensitivity)  
  writeTo(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_CRB_REG_M, 0x20);
}  

void Sensors::readMagnetometer(int &x, int &y, int &z)
{
  Wire.beginTransmission((byte)HMC5883_ADDRESS_MAG);
  Wire.write(HMC5883_REGISTER_MAG_OUT_X_H_M);
  Wire.endTransmission();
  Wire.requestFrom(HMC5883_ADDRESS_MAG, 6);
  
  uint8_t buffer[6];   // Array to store Magnetometer values 

  while (Wire.available() < 6);

  for (int i = 0; i < 6; i++)
  {
      buffer[i] = Wire.read();
  }
  
  int rawX = (int16_t)(buffer[1] | ((int16_t)buffer[0] << 8));
  int rawY = (int16_t)(buffer[5] | ((int16_t)buffer[4] << 8));
  int rawZ = (int16_t)(buffer[3] | ((int16_t)buffer[2] << 8));

  // Compensate static field and map axes
  x = - (rawX - CalibrateX);
  y = rawZ - CalibrateZ;
  z = - (rawY - CalibrateY);
}

