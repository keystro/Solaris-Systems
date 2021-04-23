#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>



const char * ssid = "Marc";
const char * password = "8c6c54bee1661a6e";




void setup(void){

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Connecting to ... ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() !=WL_CONNECTED){

    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 is: ");
  Serial.print(WiFi.localIP());
  
}

void loop(){

  if (WiFi.status() == WL_CONNECTED) {

    DynamicJsonDocument doc(2048);

    doc["Battery %"] = "60%";
    doc["Battery Temperature"] = "23.7";
    doc["Cooling Fan"] = "On/Off";
    doc["Internal Device Temperature"] = "36.8";
    doc["Mode"] = "Primary/Secondary/Auxillary";
    doc["Rate of battery charging/discharing"] = "200KW/hr";
    doc["Watts consumed/Hr"] = "600KW";
    doc["Watts produced/Hr"] = "1000kW/0KW";

    
    String json;
    serializeJson(doc, json);

    HTTPClient http;

    http.begin("http://192.168.1.104:8090/esp_mount");
   
    int httpCode = http.GET();
    
  
    if (httpCode > 0) {
       String payload = http.getString();
       Serial.print("HTTP response code for GET REQUEST: ");
       Serial.println(httpCode);

       Serial.println(payload);
    }

    http.begin("http://192.168.1.104:8090/home");
    int httpCode1 =  http.POST(json);
   

    if (httpCode1 > 0) {
      String payload1 = http.getString();
      Serial.print("Http response code for POST REQUEST: ");
      Serial.println(httpCode1);

      Serial.println(json);
    }

    http.end();
  }

  delay(6000);
 
}
