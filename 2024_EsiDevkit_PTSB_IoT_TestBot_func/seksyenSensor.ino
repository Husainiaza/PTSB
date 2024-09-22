//------sensor suhu -------------------------------------------------------
void fungsisensorSuhu(){
  DS18B20.requestTemperatures();       // arahan baca suhu
  tempC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
  tempF = tempC * 9 / 5 + 32;          // Nilai suhu di ubah kepada unit F

  Serial.print("Temperature: ");
  Serial.print(tempC);    
  Serial.print("°C");
  Serial.print("  ~  ");  
  Serial.print(tempF);    
  Serial.println("°F");

}

//------sensor LDR -------------------------------------------------------
void fungsiSensorLDR(){
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);   
}

void fungsiSensorIR(){
  //------sensor IR -------------------------------------------------------
  datasensorIRdigital = digitalRead(sensorIRdigital);
  Serial.print("IR Digital : ");
  Serial.println(datasensorIRdigital);   

  datasensorIRanalog = analogRead(sensorIRanalog);
  Serial.print("IR Analog : ");
  Serial.println(datasensorIRanalog);  
}

void fungsiKawalRelay(){
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
}

void fungsiKawalBuzzer() {
  delay (300);
  digitalWrite(buzzer,HIGH);
  delay (500);
  digitalWrite(buzzer,LOW);
  delay (100);
}

//------Paparan di OLED Display--------------------------------------------------  
void fungsiPaparanOled(){
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
  display.println(dataLDR);
  display.setCursor(0,50);
  display.print("BACAAN IR:");
  display.print(datasensorIRdigital);
  display.setCursor(70,50);
   display.print(datasensorIRanalog);
  display.display();  
}