#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h> 

DHT dht(D5, DHT11);

WiFiClient client;

long myChannelNumber = 1671932;
const char myWriteAPIKey[] = "MORDHKF0MZHYAPEG";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Sachin", "Sachin@1212");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(2000);
}
void moisture() {
  int rainSensor = analogRead(A0);
  rainSensor = map(rainSensor, 0, 1023, 0, 100);
  Blynk.virtualWrite(V0, rainSensor);
  Serial.println(rainSensor);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, moisture);

}
void loop() 
{
  Blynk.run();
  timer.run();
}
