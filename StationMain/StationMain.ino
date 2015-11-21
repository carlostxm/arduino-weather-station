#include <Statistic.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
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
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // int heat_index = dht.computeHeatIndex(t, h, false);

  statTemp.add(t);
  statHum.add(h);

  if (statTemp.count() == 10)  {
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

  delay(1000);
}

