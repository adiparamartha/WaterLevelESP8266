#include "DHT.h"

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHTPIN D1
#define DHTTYPE DHT22

#define WIFI_SSID "Dewena" 
#define WIFI_PASSWORD "0361777828" 
#define FIREBASE_HOST "smartled-a8094.firebaseio.com" 
#define FIREBASE_AUTH "PF6qx8TC5Lt2tRMzaMs0eGESTYrNfcqdjdLd7Faa" 


#define waterLevelPin A0

String waterStatus;

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("Connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
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
 
  //updateDatabase
  updateDatabase(temp,hum,waterStatus);

  delay(2000);

}

void updateDatabase(float temp, float hum, String waterStatus){
  Firebase.setFloat("Project2/Temperature",temp);
  if (Firebase.failed()) { 
        Serial.print("setting /message failed:"); 
        Serial.println(Firebase.error());   
        return; 
      } else{
        Serial.println("Database Upload Success");
      }
     delay(100);
     
  Firebase.setFloat("Project2/Humidity",hum);
  if (Firebase.failed()) { 
        Serial.print("setting /message failed:"); 
        Serial.println(Firebase.error());   
        return; 
      } else{
        Serial.println("Database Upload Success");
      }     
      delay(100);

  Firebase.setString("Project2/WaterLevel",waterStatus);
  if (Firebase.failed()) { 
        Serial.print("setting /message failed:"); 
        Serial.println(Firebase.error());   
        return; 
      } else{
        Serial.println("Database Upload Success");
      }     
      delay(100);   
}
