
#include "heltec.h"
#include "Arduino.h"

//rotate only for GEOMETRY_128_64
 SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED, RST_OLED);

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}
void setup() {

  VextON();
  delay(100);

  display.init();
  display.clear();
  display.display();
  
  display.setContrast(255);
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.clear();
  display.display();

  display.screenRotate(ANGLE_0_DEGREE);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 0, "Iniciando");

  display.display();
  delay(5000);
  
}

void loop() { 
  display.clear();
  display.display();
  for(int pos1 = 0 ; pos1 < 128; pos1++){
    for(int pos2 = 0; pos2 <64; pos2++){


      display.drawString(pos1, pos2, "|");
      display.display();
    }
  }
}