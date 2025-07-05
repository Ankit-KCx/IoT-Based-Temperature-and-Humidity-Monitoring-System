#include<WiFi.h>
#include<HTTPClient.h>
#include"DHT.h"

#define DHT1PIN 15
#define DHT1TYPE DHT11
#define SWITCHPIN 13

DHT dht1(DHT1PIN, DHT1YPE);

const char *ssi="STAFF";
const char*password="staff@321#";
Stirng GOOGLE_SCRIPT_ID="AKfycbyniLVwh3AAAyWYKy4bsW9RftUFatH5sjrUODhrfw7bJksCmINDMsIC72fIXoZpTFfhCA";//copy form googlesheet app script code

WiFiClient client;

const int sendInterval=50;

void setup() 
{
  pinMode(SWITCHPIN,INPUT);
  Serial.begin(9600);
  delay(10);
  Wifi,mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() !=WL_CONNECTED)
  {
    digitalWrite(2,LOW);
    delay(500);
    Serial.print(".");
    digitalWrite(2,HIGH);
    delay(500);
  }
  Serial.println("OK");


}
String gettDirection(int val)
{
  if(val==0)
  {
    return "ON";
  }
  else
  {
    return "OFF";
  }
}

void loop() {
 int switchpin1_op=digitalRead(SWITCHPIN);
 String switchpin1_direction=gettDirection(switchpin1_op);
 float t1=100.1;
 float f1=25.5;
 float h1=80;

 Serial.print("Temperature in celcius=");
 Serial.println(t1);
 Serial.print("Temperature in faranheit=");
 Serial.println(f1);
 Serial.print("Humidity=");
 Serial.println(h1);
 Serial.print("Switch=");
 Serial.println(switchpin1_op);
 write_google_sheet("value=1"+String(t1)+"&value2="+String(h1));


}
void write_google_sheet(string params)
{
  HTTPClient http;
  String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
  Serial.println(url);
  Serial.println("Updating Temperature & Humidity Status");
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode=http.GET();
  Serial.print("HTTP Status Code:");
  Serial.println(httpCode);

  String payload;
  if(httpCode > 0)
  {
    payload = http.getString();
    Serial.println("Payload:"+payload);
  }
  http.end();

}
