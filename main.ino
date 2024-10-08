/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b8c38c3cab144d2fbc74ab57f686b8df";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo1714";
char pass[] = "sudeesh97";

#define DHTPIN D1          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V2, t);
}

BLYNK_WRITE(V0)
{
  digitalWrite(D2,param.asInt());       //BULB
  Serial.print("D2=");
  Serial.println(param.asInt());

  digitalWrite(D3,param.asInt());       //FAN
  Serial.print("D3=");
  Serial.println(param.asInt());
  
  digitalWrite(D6,param.asInt());       //KITCHEN
  Serial.print("D6=");
  Serial.println(param.asInt());

  digitalWrite(D7,param.asInt());      //AC
  Serial.print("D7=");
  Serial.println(param.asInt());

  digitalWrite(D4,param.asInt());      //TV - R
  Serial.print("D4=");
  Serial.println(param.asInt());

}
BLYNK_WRITE(V1)
{
  digitalWrite(D3,param.asInt());                                 //FAN  LIVING ROOM  
}
BLYNK_WRITE(V4)                                                   //KITCHEN
{
  analogWrite(D6,param.asInt());
}
BLYNK_WRITE(V5)                                                   //AC BEDROOM
{
  analogWrite(D7,param.asInt());
}

BLYNK_WRITE(V6)                                                   //TV -- R  LIVING ROOM
{
  analogWrite(D4,param.asInt());
}

BLYNK_WRITE(V8)                                                   //BULB
{
  analogWrite(D2,param.asInt());
}



void setup()
{
  pinMode(D2,OUTPUT);  //BULB
  pinMode(D3,OUTPUT); //FAN
  pinMode(D6,OUTPUT); //KITCHEN
  pinMode(D7,OUTPUT); //AC
  pinMode(D4,OUTPUT); //TV --R
  
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D4,LOW);
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  dht.begin();
  

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
