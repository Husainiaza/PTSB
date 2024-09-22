//----Seksyen 1 - Senarai HEADER (Library) yang diperlukan------------- ----
//--------------------------------------------------------------------------
#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

//-----Seksyen 3 - TAMAT ---------------------------------------------- ----


//-----Seksyen 4 - ISTIHAR Pemboleh ubah dengan jenis Data yang digunaka ---
//--------------------------------------------------------------------------
float tempC; // suhu dalam Celsius
float tempF; // suhu  Fahrenheit
int dataLDR;
//-----Seksyen 4 - TAMAT ---------------------------------------------- ----


void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

 DS18B20.begin();    // initialize the DS18B20 sensor
  
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

//------sensor suhu -------------------------------------------------------
  DS18B20.requestTemperatures();       // arahan baca suhu
  tempC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
  tempF = tempC * 9 / 5 + 32;          // Nilai suhu di ubah kepada unit F

  Serial.print("Temperature: ");
  Serial.print(tempC);    
  Serial.print("°C");
  Serial.print("  ~  ");  
  Serial.print(tempF);    
  Serial.println("°F");

//------sensor LDR -------------------------------------------------------
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);   

//------Kawalan relay -------------------------------------------------------  
  digitalWrite(relay02,HIGH);
  digitalWrite(relay01,LOW);
  delay (300);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,HIGH);
  delay (300);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,LOW);
  delay (300);
  digitalWrite(relay02,HIGH);
  digitalWrite(relay01,HIGH);
  delay (300);
  digitalWrite(buzzer,HIGH);
  delay (500);
  digitalWrite(buzzer,LOW);
  delay (100);

//------Paparan di OLED Display--------------------------------------------------  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("  Politeknik Tuanku  ");
  display.setCursor(0,10);
  display.println("  Sultanah Bahiyah  ");
  display.setCursor(10,20);
  display.println("Kursus IoT MQTT");
  display.setCursor(0,30);
  display.print("BACAAN SUHU :");
  display.print(tempC,1);
  display.setCursor(0,40);
  display.print("BACAAN LDR  :");
  display.print(dataLDR);
  display.setCursor(0, 60);
  display.display();  
}
