#include <LiquidCrystal.h>
#include <dht.h>

// example array
int array[] = {
  1, 2, 3, 4, 5
};

#define dht_pin A0

dht DHT;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Digital_Input_mic1 = 7;
int Digital_Input_mic2 = 8;

int loop_counter = 0;




void DisplayTemp(){
  
  DHT.read11(dht_pin);
  lcd.setCursor(0, 0);
  lcd.print("Hum = ");
  lcd.print((int)DHT.humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Temp = ");
  lcd.print((int)DHT.temperature); 
  lcd.print(" C");
  delay(5000);
  lcd.clear();
}

bool get_microphone_1_boolean() {
  bool mic1 = digitalRead(Digital_Input_mic1);
  return mic1;
}

bool get_microphone_2_boolean() {
  bool mic2 = digitalRead(Digital_Input_mic2);
  return mic2;
}

void setup() 
{
  // microphone 1
  pinMode(Digital_Input_mic1, INPUT);
  
  //microphone 2
  pinMode(Digital_Input_mic2, INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
}

void loop() 
{
  //loop a few times getting mic data each time
  DisplayTemp();
}
