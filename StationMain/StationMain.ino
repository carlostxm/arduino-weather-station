#include <Statistic.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

/* Global Variables */
Statistic statTemp;
Statistic statHum;
int count = 1;

void setup() {
  Serial.begin(9600);
  dht.begin();
  statTemp.clear();
  statHum.clear();
}

void loop() {
  // int heat_index = dht.computeHeatIndex(t, h, false);

  statTemp.add(getTemperature());
  statHum.add(getHumidity());

  displayResults();

  delay(1000);
}

float getHumidity(){
  return dht.readHumidity();
}

float getTemperature(){
  return dht.readTemperature();
}

void displayResults(){
   if (statTemp.count() == 5)  {
     Serial.print("Count: ");
     Serial.print(count++);
      
     Serial.print("  Temp. AVG: ");
     Serial.print(statTemp.average(), 1);
  
     Serial.print("  Humid. AVG: ");
     Serial.print(statHum.average(), 1);
  
     Serial.print("  Heat index: ");
     Serial.print(dht.computeHeatIndex(statTemp.average(), statHum.average(), false), 1);
  
     Serial.println();
      
     statTemp.clear();
     statHum.clear();
  }
}

