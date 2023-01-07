// include the library code:
//Test code to get things working copied from https://lastminuteengineers.com/arduino-1602-character-lcd-tutorial/
#include <LiquidCrystal.h>
#include <dht.h>
dht DHT;

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Analog Pin A0 of Arduino is connected to DHT11 out pin
#define dht_pin A0

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Humidity");
  //lcd.autoscroll();
  lcd.setCursor(0, 1);
  lcd.print("& temp Sensor");
  delay(8000);
  lcd.clear();
}

void loop() 
{
  // Print a message to the LCD.
  DHT.read11(dht_pin);
  lcd.setCursor(0, 0);
  lcd.print("Hum = ");
  lcd.print((int)DHT.humidity);
  lcd.print("%");

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Temp = ");
  lcd.print((int)DHT.temperature); 
  lcd.print(" C");
  delay(5000);
  lcd.clear();
  
}
