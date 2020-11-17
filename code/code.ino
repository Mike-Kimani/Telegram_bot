#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

float resistance;
// Replace with your network credentials
const char* ssid = "Gakibia hostel";
const char* password = "emmakim19";

#define BOTtoken "1474270395:AAFEelu8R4CD-ON2gb8FExKE39p9WYv9MlI"
#define CHAT_ID "975573852"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//bool lightsDetected = false;

//void ICACHE_RAM_ATTR detectsLights() {
  //Serial.println("LIGHTS DETECTED!!!");
  //lightsDetected = true;
//}
int i;
void getSensorReadings(){
  resistance = analogRead(A0);
  resistance = map(resistance, 0, 1023, 0, 255);
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setInsecure();
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  getSensorReadings();
  bot.sendMessage(CHAT_ID, "Bot started up", "");
  
  if (resistance> 15.00){
   bot.sendMessage(CHAT_ID, "Lights on!!", "");
   i =1;
    }
    else{
      bot.sendMessage(CHAT_ID, "Lights out!!", "");
      i =2;      
      }
  Serial.print(i);

}

void loop() {
  // put your main code here, to run repeatedly:
  getSensorReadings();
  
  if ((resistance> 15.00) && i ==2){
   bot.sendMessage(CHAT_ID, "Lights on!!", "");
   i = 1;
   //boolean old = on;
    }
    if((resistance<15.00) && i ==1){
      bot.sendMessage(CHAT_ID, "Lights off!!", "");
   i = 2;
      }
  Serial.println(i);    
  delay(1000);
}
