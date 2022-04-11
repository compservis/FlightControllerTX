// ------ HARDWARE ------

// GPS -----
#define GPS_RX 5
#define GPS_TX 4
// ---------

// Temperature, pressure and humidity 
#define TEMP_ADDR 0x76
// ---------

// RPM -----
#define PMS_PIN 9 // Pin for signal from Photomicrosensor
// ---------

// Thrust --
#define LOADCELL_DOUT_PIN A0
#define LOADCELL_SCK_PIN A1
// ---------

// Accumulator
#define ACC_PIN A8
// ---------

// Wind speed
#define WIND_PIN A4
// ---------

// ----------------------


// ----- DATA TYPES -----

/*
Char sensor codes:
t - temperature, float
P - pressure, float
H - height, int
h - humidity, int
L - latitude, long
l - longtitude, long
X - x, uint16
Y - y, uint16
Z - z, uint16
p - pitch, uint16
r - roll, uint16
y - yaw, uint16
R - RPM, int
T - thrust, double
e - time, ulong
d - date, ulong
a - power, float
*/

struct Sensors {
  float temp;
  float pressure;
  int height;
  int humidity;
  long latitude;
  long longtitude;
  long time;
  long date;
  int x;
  int y;
  int z;
  int roll;
  int pitch;
  int yaw;
  int rpm;
  float thrust;
  float power;
};

Sensors s;

struct position
{
  int x, y, z;
  int r, p, w;
}position;

struct position p;


struct location
{
    long lat, lon;
    unsigned long time, date;
}location;

struct location l;

// -------------------

