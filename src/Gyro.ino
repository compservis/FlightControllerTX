#include <I2Cdev.h>
#include <MPU6050.h> 

MPU6050 mpu;

int16_t xval, yval, zval, roll, pitch, yaw; 

bool mpuState; 

int initGyro() 
{
  mpu.initialize();
  mpuState = mpu.testConnection();
  return mpuState;
}

struct position readGyro() 
{
  if (mpuState)
  {
    mpu.getMotion6(&xval, &yval, &zval, &roll, &pitch, &yaw);
    p.x = (int)map(xval, -32768, 32767, -360, 359); // X-axis
    p.y = (int)map(yval, -32768, 32767, -360, 359); // Y-axis
    p.z = (int)map(zval, -32768, 32767, -360, 359); // Z-axis
    p.p = (int)map(pitch, -32768, 32767, -360, 359); // pitch
    p.r = (int)map(roll, -32768, 32767, -360, 359); // roll
    p.w = (int)map(yaw, -32768, 32767, -360, 359); // yaw

  }
  return p;
}
