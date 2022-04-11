#include <SPI.h>
#include "RF24.h"
#include "FlightControllerTX.h"

/* ---------- */

#define ROLE 1      // 0 - RX, 1 - TX

#define CE_PIN 49
#define CSN_PIN 53

#define REPORT_INTERVAL 2 // interval between sending data in ms

/* ---------- */

RF24 radio(CE_PIN, CSN_PIN);
uint8_t address[][6] = {"1Node", "2Node"};
bool radioNumber = ROLE;
bool role = ROLE; 

float payload = 0.0;

int i = 0;

bool newDataAvailable = false;

unsigned long lastSentTime = 0; 
unsigned long lastStructUpd = 0;

struct DataPackage {
  char sensor;    // 1B
  int valInt;     // 4B
  long valLong;   // 8B
  float valFloat; // 4B
};

DataPackage data;

float pwr; 

bool online; 
unsigned long lastRecvTime = 0;

void setup() {

	Serial.begin(9600);
	while (!Serial) {	}
	
	if (!radio.begin()) {
		Serial.println(F("Radio is not responding"));
		while (1) {} 
	}

	radio.setPALevel(RF24_PA_LOW);  // LOW / MAX
	radio.setPayloadSize(sizeof(DataPackage));

	// TX address of the RX node into the TX pipe
	radio.openWritingPipe(address[ROLE]);
	// RX address of the TX node into a RX pipe
	radio.openReadingPipe(1, address[!ROLE]);

	radio.stopListening();  // TX mode

	data.sensor = '0';
	data.valFloat = 0;
	data.valInt = 0;
	data.valLong = 0;

	initTemp();
	initThrust();
	initTaho();
	initGyro();
	initGPS();

	pinMode(ACC_PIN, INPUT);
	pinMode(WIND_PIN, INPUT);

} // setup

void loop() {

	bool led_state = false;

	updateHardware();

	if (millis() - lastSentTime >= REPORT_INTERVAL) 
	{
		unsigned long start_timer = micros();                   
		bool report = radio.write(&data, sizeof(DataPackage)); 
		unsigned long end_timer = micros();
		
		if (report) 
		{
			Serial.print(F("Latency:"));
			Serial.print(end_timer - start_timer);
			Serial.print(F(" us. Sent: "));
			Serial.print(data.sensor);
			Serial.print("\t");
			Serial.print(data.valInt);
			Serial.print("\t");
			Serial.print(data.valFloat);
			Serial.print("\t");
			Serial.println(data.valLong);

			led_state = !led_state;
			digitalWrite(LED_BUILTIN, led_state);

			i++;
			lastSentTime = millis();
		} 
		else 
		{
			Serial.println(F("Transmission failed or timed out"));
			lastSentTime = millis();
		}
	}
}

void updateHardware() 
{
	
	if (millis() - lastStructUpd >= 1000)
	{
		l = readGPS(); // read GPS once per second
		lastStructUpd = millis();
	}
	p = readGyro();
	float air = analogRead(WIND_PIN);
	pwr = analogRead(ACC_PIN) / 1024.0 * 100;

	if (i == 18) 
	{
		i = 0;
	}
	
	if (i == 0) {data.sensor = 't'; data.valFloat = readTemp();}
	if (i == 1) {data.sensor = 'P'; data.valFloat = readPres();}
	if (i == 2) {data.sensor = 'H'; data.valInt = (int)readAlt();}
	if (i == 3) {data.sensor = 'h'; data.valInt = (int)readHum();}
	if (i == 4) {data.sensor = 'L'; data.valLong = l.lat;}
	if (i == 5) {data.sensor = 'l'; data.valLong = l.lon;}
	if (i == 6) {data.sensor = 'X'; data.valInt = (int)p.x;}
	if (i == 7) {data.sensor = 'Y'; data.valInt = (int)p.y;}
	if (i == 8) {data.sensor = 'Z'; data.valInt = (int)p.z;}
	if (i == 9) {data.sensor = 'p'; data.valInt = (int)p.p;}
	if (i == 10) {data.sensor = 'r'; data.valInt = (int)p.r;}
	if (i == 11) {data.sensor = 'y'; data.valInt = (int)p.w;}
	if (i == 12) {data.sensor = 'R'; data.valInt = (int)readTaho();}
	if (i == 13) {data.sensor = 'T'; data.valInt = (int)readThrustUnits();}
	if (i == 14) {data.sensor = 'A'; data.valFloat = air;}
	if (i == 15) {data.sensor = 'a'; data.valFloat = pwr;}
	if (i == 16) {data.sensor = 'e'; data.valLong = l.time;}
	if (i == 17) {data.sensor = 'd'; data.valLong = l.date;}
	
	
}
