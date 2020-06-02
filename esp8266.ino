#include "DHTesp.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TridentTD_LineNotify.h>
#define SSID "xxxxxxxxxx"
#define PASSWORD "xxxxxxxxxx"
#define LINE_TOKEN1 "xxxxxxxxxx" //Line token - with Owner
#define LINE_TOKEN2 "xxxxxxxxxx" //Line token - for Family Group

DHTesp dht;
String IPaddress;

int dustPin = A0;
int ledPin = D2;    
 
float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

const long utcOffsetInSeconds = 25200;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  dht.setup(D4, DHTesp::DHT22);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN1);
  IPaddress =  WiFi.localIP().toString();
  LINE.notify("WeMos D1 R1 ทำการเชื่อมต่อ WiFi เรียบร้อย \nIP Address : "+ IPaddress);
  timeClient.begin();
}
 
 
void loop()
{
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());

  float h = dht.getHumidity();
  float t = dht.getTemperature();
  float f = dht.toFahrenheit(t);
  
  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(280);
 
  voltsMeasured = analogRead(dustPin); // read the dust value
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
 
  //measure your 5v and change below
  calcVoltage = voltsMeasured * (3.3 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.1;
  dustDensity = dustDensity * 1000;
  if (dustDensity <= 0.00) {
    dustDensity = 0.00;
  }
  
  Serial.println("GP2Y1010AU0F readings"); 
  Serial.print("Raw Signal Value (ค่าดิบจากเครื่องวัด) = ");
  Serial.println(voltsMeasured); 
  Serial.print("Voltage = ");
  Serial.println(calcVoltage);
  Serial.print("Dust Density (ความหนาแน่นของฝุ่นละอองในอากาศ) = ");
  Serial.print(dustDensity); // mg/m3
  Serial.println(" µg/m³");
  Serial.print("");

  Serial.println("Status\t\tHumidity (%)\tTemperature (°C)\t(°F)");
  Serial.print(dht.getStatusString());
  Serial.print("\t\t");
  Serial.print(h, 1);
  Serial.print("\t\t\t");
  Serial.print(t, 1);
  Serial.print("\t\t\t\t");
  Serial.println(dht.toFahrenheit(t), 1);

  int hour = 0;
  for (int i = 0; i <= 23;i++) {
    if ( timeClient.getHours()  == hour && timeClient.getMinutes()  == 0 && timeClient.getSeconds()  < 5) {
      LINE.setToken(LINE_TOKEN2);
      //LINE.notify("รายงานสถานภาพอากาศ ณ ปัจจุบัน");
      //LINE.notify("ความชื้นในอากาศ "+ String (h) +" %" );
      //LINE.notify("อุณหภูมิภายในบ้าน " + String (t) +" องศาเซลเซียส (" + (f) + " Fํ)");
      //LINE.notify("คุณภาพอากาศ , ความหนาแน่นของฝุ่นละออง PM 2.5 ในอากาศ " + String (dustDensity) +" µg/m³");
      LINE.notify("รายงานสถานภาพอากาศ ณ ปัจจุบัน\nความชื้นในอากาศ "+ String (h) +" %\nอุณหภูมิภายในบ้านเรือน " + String (t) +" °C (" + (f) + " Fํ)\nคุณภาพอากาศ , PM 2.5 ภายในบ้านเรือน " + String (dustDensity) +" µg/m³");
    }
    hour = hour+1;
  }
  
  if ((timeClient.getMinutes()  == 0 || timeClient.getMinutes()  == 30) && timeClient.getSeconds()  < 5) {
      LINE.setToken(LINE_TOKEN1);
    LINE.notify("GP2Y1010AU0F - Raw Signal Value =" + String (voltsMeasured) + "\nVoltage = " + String (calcVoltage) + "\nDust Density = " + String (dustDensity)
    + " µg/m³\n\nDHT22 - Status = " + String (dht.getStatusString()) + "\nHumidity (%) = " + String (h) + "\nTemperature °C (°F) = " + String (t) + "( " + String (f)
    + " )");
      LINE.notify("รายงานสถานภาพอากาศ ณ ปัจจุบัน\nความชื้นในอากาศ "+ String (h) +" %\nอุณหภูมิภายในบ้านเรือน " + String (t) +" °C (" + (f) + " Fํ)\nคุณภาพอากาศ , ความหนาแน่นของฝุ่นละออง PM 2.5 ภายในบ้านเรือน " + String (dustDensity) +" µg/m³");
  }
  
  delay(5000);
}
