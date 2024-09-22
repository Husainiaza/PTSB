//-----Seksyen 1 - Senarai Libari yang diperlukan---------------------- ----
//--------------------------------------------------------------------------
#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// wifi & MQTT ------
#include <WiFi.h>
#include <PubSubClient.h>

//-----Seksyen 1 - TAMAT ---------------------------------------------- ----


//-----Seksyen 2 - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer 25
#define SensorSuhu  15 // pin sambungan ke DS18B20 (ONEWIRE)
//---Analog Sensor  pin connection---
#define sensorLDR 34
#define sensorIRanalog 32
#define sensorIRdigital 33
//---Tentukan nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//-----Seksyen 2 - TAMAT ---------------------------------------------------


//-----Seksyen 3 - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------
// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Istihar Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature DS18B20(&oneWire);

//---------- MQTT and WifI connection ---------------------------
const char* ssid = "Alias FredoX_2.4GHz@unifi";  
const char* password = "0135335045";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;                                                                          
PubSubClient client(espClient); //MQTT


//-----Seksyen 3 - TAMAT ---------------------------------------------- ----


//-----Seksyen 4 - ISTIHAR Pemboleh ubah dengan jenis Data yang digunaka ---
//--------------------------------------------------------------------------
float tempC; // suhu dalam Celsius
float tempF; // suhu  Fahrenheit
int dataLDR;
int datasensorIRdigital;
int datasensorIRanalog;

char varPotString[8];
long lastMsg = 0;
char msg[50];
//-----Seksyen 4 - TAMAT ---------------------------------------------- ----


void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(sensorIRdigital,INPUT);

  Serial.begin(115200); // initialize serial

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  DS18B20.begin();    // initialize the DS18B20 sensor
  
//------- WiFI & MQTT Setup ------------
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(100);  
//--------------------------------------

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("  Politeknik Tuanku  ");
   display.setCursor(0,10);
  display.println("  Sultanah Bahiyah  ");
  display.setCursor(10,20);
  display.println("Kursus IoT MQTT");
  display.display();
  delay(5000);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();

  if (now - lastMsg > 2000) {  
    lastMsg = now;
  //------------ Letakan Kod anda disini ----------
  fungsisensorSuhu();
  fungsiSensorLDR();
  fungsiPaparanOled();

  //-----------------------------------------------

  }
}
