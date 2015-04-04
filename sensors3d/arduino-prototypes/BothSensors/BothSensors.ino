#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define GYRO 0x68         // gyro I2C address
#define REG_GYRO_X 0x1D   // IMU-3000 Register address for GYRO_XOUT_H
#define ACCEL 0x53        // Accel I2c Address
#define ADXL345_POWER_CTL 0x2D

byte buffer[12];   // Array to store ADC values 
int gyro_x;
int gyro_y;
int gyro_z;
int accel_x;
int accel_y;
int accel_z;

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial1.begin(57600);
  
  // Setup Magnetometer
  Serial1.println("HMC5883 Magnetometer Test"); 
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial1.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  // Setup Accelerometer
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
void writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}


// correct static magnetic field
float cX = -12.86;
float cY = -15.27;
float cZ = -38.47;    

void normalize(float& x, float& y, float& z)
{
  float len = sqrt(x*x + y*y + z*z) / 255.0;
  x/= len;
  y/= len;  
  z/= len;
}  

void loop(void) 
{
  
  while (1) 
  {  
    /* Get a new sensor event */ 
    sensors_event_t event; 
    mag.getEvent(&event);
    
    // arrange axes
    float mx = -(event.magnetic.y - cY);
    float my =  (event.magnetic.z - cZ);    
    float mz = -(event.magnetic.x - cX);        
    
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
    gyro_x = buffer[0] << 8 | buffer[1];
    gyro_y = buffer[2] << 8 | buffer[3];
    gyro_z = buffer[4] << 8 | buffer[5];
    // Accel is LSB first. Also because of orientation of chips
    // accel y output is in same orientation as gyro x
    // and accel x is gyro -y
    accel_y = buffer[7] << 8 | buffer[6];
    accel_x = buffer[9] << 8 | buffer[8];
    accel_z = buffer[11] << 8 | buffer[10];
    
    // re-arrange axes
    float ax = -accel_x;
    float ay =  accel_z;
    float az = -accel_y;
    
    normalize(mx, my, mz);
    normalize(ax, ay, az);    
    
    int iax = ax;
    int iay = ay;    
    int iaz = az;        
    int imx = mx;
    int imy = my;    
    int imz = mz;        
    
    char buf[80];
    
    sprintf(buf, "%d,%d,%d,%d,%d,%d@", iax, iay, iaz, imx, imy, imz);
    Serial1.println(buf);

    delay(50);
  }
}
