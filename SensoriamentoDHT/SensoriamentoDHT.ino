
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

#define FIREBASE_HOST "sensoriamento-9455e-default-rtdb.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "zFrZfEkK5XxwRqMK7ZdqjWuIoqp7dEcWEhKjv74x"            // the secret key generated from firebase
#define WIFI_SSID "FAMILIA LUIZA 2G"
#define WIFI_PASSWORD "setrop21"

#define DHTPIN D3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object

void setup() 
 {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado em: ");
  Serial.println(WIFI_SSID);
  Serial.println("Endereço IP : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
 getData();
}

void getData() {
   float u = dht.readHumidity();
  float t = dht.readTemperature();
  delay(1000);
  if (isnan(u) || isnan(t)) {
    Serial.println(F("Falha ao ler o sensor DHT!"));
    return;
  }

  Serial.print("Umidade: "); 
  Serial.print(u);
  String fireUmid = String(u) + String("%");
  
  Serial.print("% Temperatura: "); 
  Serial.print(t); 
  Serial.println(" *C ");
  String fireTemp = String(t) + String("*C");

 // Firebase.pushString("/DHT11/Temperatura", fireTemp);
 // Firebase.pushString("/DHT11/Umidade", fireUmid);
  Firebase.setFloat("Umidade", u);
  Firebase.setFloat("Temperatura", t);
  
    if  (Firebase.failed())
    {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());
      return;
    }
}
