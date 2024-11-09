#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define btn 33
#define red 4
#define green 5
#define yellow 19
#define blue 22 

// Wireless connection data
const char* ssid = "#Turin.uz";
const char* pass = "Turin_2024@!";
const char* wifi_status = "Trying to connect";
int count_wifi = 0;

WiFiClient wifi_client;
PubSubClient mqtt_client (wifi_client);


void setup() {
  //defining button input
  pinMode(btn, INPUT);
  //serial begin
  Serial.begin(115200);
  
  //led configureation
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);

  // WIFI connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  delay(100);
 
  //check wifi connected
  while (WiFi.status() != WL_CONNECTED){
    count_wifi ++;
    Serial.println(wifi_status);
    Serial.println(count_wifi);
    delay(1000);
 
  }
  count_wifi=0;
  Serial.println("WiFi Connected"); 
  
  Serial.println("IP: "); 
  Serial.println(WiFi.localIP()); 
  
  Serial.println("MAC: "); 
  Serial.println(WiFi.macAddress()); 

  mqtt_client.setServer("mqtt.iotserver.uz", 1883);
  mqtt_client.setCallback(my_callback);

}

void loop() {
  while (!mqtt_client.connected()){
    String macAddr = WiFi.macAddress();
    String macSuffix = macAddr.substring(macAddr.length() - 5);
    macSuffix.replace(":", "");

    String myID = "edacs_lab4";
    myID += macSuffix;

    int mres = mqtt_client.connect(myID.c_str(),"userTTPU", "mqttpass");
      if (mres){
        Serial.print("mqtt connected: ");
        Serial.print(mres);
        mqtt_client.subscribe("ttpu/edacs/lab4");
        mqtt_client.publish("ttpu/edacs/msg", "hello");
      }
      else {
        Serial.print("mqtt Not connected, trying: ");
        Serial.print(mres);
        delay(3000);
      }

  }

  mqtt_client.loop();

  static int count;
  
  static int prev_btn = 0;
  
  int btns = digitalRead(btn);
  //detect button press 
  if  (btns == 1 && prev_btn == 0){
    count++;
    Serial.println(count);
    // led turn off
    digitalWrite(red, 0);
    digitalWrite(green, 0);
    digitalWrite(yellow, 0);
    digitalWrite(blue, 0); 
           
    if (count == 1){
      digitalWrite(red, 1);
    }
    if (count == 2){
      digitalWrite(green, 1);
    }
    if (count == 3){
      digitalWrite(yellow, 1);
    }
    if (count == 4){
      digitalWrite(blue, 1);
    }
    if (count == 5){
      count = 0;
    }

  }
  prev_btn = btns;
  delay(100);


}
void my_callback (char* topic, byte* payload,  unsigned int len){
  Serial.println("Msg recieved");
}
