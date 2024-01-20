#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial mySerial(D1, D2); //RX, TX

const char* ssid = "SURESH_HOME4G";
const char* password = "krishnakumari";

//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client; //--> Create a WiFiClientSecure object.

String GAS_ID = "AKfycbwJG0Fr96FbkJKqKvTmrX60qwYh8JPhJceyLcon4O7EV1Ub8t20bH27rzN3kkCDCKZqxQ"; //--> spreadsheet script ID

#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
ESP8266WebServer server(80);

int ser_count = 0;

//https://script.google.com/macros/s/AKfycbwJG0Fr96FbkJKqKvTmrX60qwYh8JPhJceyLcon4O7EV1Ub8t20bH27rzN3kkCDCKZqxQ/exec

void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void sens(){
  String stat = mySerial.readStringUntil('\r');
  Serial.println(stat);

  String in_ard = stat;
  String strs[5];
  int StringCount = 0;
  
  while (in_ard.length() >0){
    int index = in_ard.indexOf(',');
    if (index == -1) // No space found
    {
      strs[StringCount++] = in_ard;
      break;
    }
    else
    {
      strs[StringCount++] = in_ard.substring(0, index);
      in_ard = in_ard.substring(index+1);
    }
  }
  
  sensors.requestTemperatures();
  String tmp = String(sensors.getTempCByIndex(0));
  stat = stat+","+tmp;
  int str_len = stat.length() + 1;
  char recieved[str_len];
  stat.toCharArray(recieved, str_len);
//  Serial.println(recieved);
  server.send(200, "text/plane", stat);
  
  ser_count = ser_count+1;
  if (ser_count == 7) {
    Serial.println("Clearing server count");
    int g_tmp = tmp.toInt();
    int g_tds = strs[0].toInt();
    int g_pH = strs[1].toInt();
    sendData(g_tmp, g_pH, g_tds);
//    sendData(int tem, int ph, int tds);
    ser_count=0;
  }
}

void setup(void) {
  Serial.begin(115200);  
  mySerial.begin(9600);
//  sensors.begin();

  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/sens", sens);
  server.begin();

  client.setInsecure();
}

void loop(void) {
//  String msg = mySerial.readStringUntil('\r');
//  int str_len = msg.length() + 1;
//  char recieved[str_len];
//  msg.toCharArray(recieved, str_len);
//  recieved[5]='5';
  server.handleClient();
//  sendData(53.5, 6.2, 555.25);  
//  delay(20000);
}

void sendData(int tem, int ph, int tds) {
  Serial.println(tem);
  Serial.println(ph);
  Serial.println(tds);

  
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  //----------------------------------------Processing data and sending data
  String string_temperature =  String(tem);
  String string_ph =  String(ph);
  String string_tds =  String(tds);
  // String string_temperature =  String(tem, DEC); 
//  String string_humidity =  String(hum, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature + "&humidity=" + string_ph + "&tds=" + string_tds;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------

  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 
