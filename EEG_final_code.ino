#define sclk 2
#define mosi 3
#define cs   4
#define dc   5

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Brain.h>


LiquidCrystal lcd(12, 11, cs, dc, mosi, sclk);

Brain brain(Serial);

void setup(void) {

  lcd.begin(16, 2);

  lcd.clear();

 }

void loop() {
  
  lcd.setCursor(0,0);

  if (brain.update()) {
     if (brain.readSignalQuality() > 100) {
     lcd.print("signal quality low"); 

}

else{
  lcd.setCursor(0,0);
  lcd.print("Attention:");
  lcd.setCursor(11, 0);
  lcd.print(brain.readAttention());
  lcd.setCursor(0,1);
  lcd.print("Meditation:");
  lcd.setCursor(11, 1);
  lcd.print(brain.readMeditation());

}}

}
