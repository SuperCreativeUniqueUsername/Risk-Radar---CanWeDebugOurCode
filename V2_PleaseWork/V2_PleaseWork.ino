#include <LiquidCrystal.h>
#include <dht.h>
#define dht_pin A0

dht DHT;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Digital_Input_mic1 = 8;
bool mic1;
bool mic1_array[1000]; // 5 seconds
int mic1_index = 0;

bool get_microphone_1_boolean() {
  bool mic1 = digitalRead(Digital_Input_mic1);
  return mic1;
}
//counter insmt working

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // microphone 1
  pinMode(Digital_Input_mic1, INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Code Starts!");
  delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  mic1 = get_microphone_1_boolean();
  mic1_array[mic1_index] = mic1;
  mic1_index++;
  Serial.print((Count_array(mic1_array)));
  Serial.println((mic1));
  if (Count_array(mic1_array)) {
    Serial.print("-----GoodJob-----");
    delay(1000);
  }
  if (mic1_index > 1000) {
    mic1_index = 0;
    if (Count_array(mic1_array)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Danger!");
      delay(1000);
      }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Good!");
    }
    }
  }
