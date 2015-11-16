// Reading environmental data via DHT humidity/temperature sensors
// Written by ladyada originally, heavily modified by HoogieMan

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// define sensor type
#define DHTTYPE DHT11   // DHT 11 

// Setting up Arduino board
// Connected pin 1 (on the left) of the sensor to +5V
// Connected pin 2 of the sensor to whatever your DHTPIN is
// Connected pin 4 (on the right) of the sensor to GROUND
// Connected a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  //Serial.println("DHT11 test!");
  //delay(3000);
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds
  // Sensor readings may also be up to 2 seconds 'old' (slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature() * 1.8 + 32;

  // check if returns are valid, if they are NaN (not a number) then something went wrong
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    //print header row if needed
    //Serial.println("Humidity (%) \t Temperature (*C) \t Temperature (*F)");
    Serial.print("{");
    Serial.print("'Humidity': "); 
    Serial.print(h);
    Serial.print(", ");
    //Serial.print("%\t ");
    Serial.print("'Temperature Celsius': "); 
    Serial.print(t);
    Serial.print(", ");
    //Serial.print("\t ");
    //Serial.println(" *C, ");
    Serial.print("'Temperature Fahrenheit': ");
    Serial.print(f);
    Serial.print("}");
    //Serial.println("\t ");
    //Serial.println(" *F");
    Serial.print('\n');
  delay(10000);//Don't try to access too frequently...this will make for a gigantic dataset very quickly
  }
}

