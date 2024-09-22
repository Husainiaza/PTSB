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

//------ Publish data ke MQTT broker
  dtostrf(tempC, 1, 2, varPotString);
  client.publish("kursusiot/suhu", varPotString);

}

//------sensor LDR -------------------------------------------------------
void fungsiSensorLDR(){
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);   

  //------ Publish data ke MQTT broker
  dtostrf(dataLDR, 1, 2, varPotString);
  client.publish("kursusiot/ldr", varPotString);
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