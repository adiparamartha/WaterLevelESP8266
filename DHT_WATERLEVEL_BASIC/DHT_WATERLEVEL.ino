#include "DHT.h"

#define DHTPIN D1
#define DHTTYPE DHT22

#define waterLevelPin A0

String waterStatus;

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  //Read Temp
  float temp = dht.readTemperature();
  //Read Humidity
  float hum = dht.readHumidity();

  Serial.print("Temp: ");
  Serial.println(temp);

  Serial.print("Humidity: ");
  Serial.println(hum);

  //Read Water Level
  int waterLevel=analogRead(waterLevelPin); 

  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  if(waterLevel >=500){
    waterStatus = "HIGH";
  }
  else if( waterLevel > 250 && waterLevel<500){
    waterStatus = "CAREFULL";
  } else{
    waterStatus = "NORMAL";
  }

  Serial.println(waterStatus);
  delay(2000);

}
