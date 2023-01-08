#include <LiquidCrystal.h>
#include <dht.h>

// example array
int array[1000];

#define dht_pin A0

dht DHT;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Digital_Input_mic1 = 7;
int Digital_Input_mic2 = 8;
int loop_counter = 0;
int mic1_array[100000];
int last_millis = millis();

void DisplayTemp(){
  // This function reads the temp and humidity data
  // and displays on the LCD
  DHT.read11(dht_pin);
  lcd.setCursor(0, 0);
  lcd.print("Hum = ");
  lcd.print((int)DHT.humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
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

void loop() {
  if (millis() - last_millis >= 100) {
    last_millis -= 1000;
    main();
  }
}

void main() // runs every 100 milliseconds exactly
{
  loop_counter += 1;
  if (loop_counter == 20) {
    loop_counter = 0;
    DisplayTemp();
  }
  //loop a few times getting mic data each time
}
