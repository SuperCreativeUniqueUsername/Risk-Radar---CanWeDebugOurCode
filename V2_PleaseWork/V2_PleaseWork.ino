#include <LiquidCrystal.h>
#include <dht.h>
#define dht_pin A0

dht DHT;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Digital_Input_mic1 = 8;
bool mic1;
bool mic1_array[1000];
int mic1_index = 0;

bool get_microphone_1_boolean() {
  bool mic1 = digitalRead(Digital_Input_mic1);
  return mic1;
}


int Count_array(bool array[]) {
  int count = 0;
  for (int i = 0; i < 1000; i++) {
    if (array[i] == 1) {
      count++;
      }  
    }
    if (count >= 10){
        return 1;}
    else {
      return 0;
    }
}
void DisplayTemp(){
  // This function reads the temp
  // and displays on the LCD
  lcd.setCursor(0, 1);
  lcd.print((int)DHT.temperature); 
  lcd.print(" C");
  if ((int)DHT.temperature > 26){
    lcd.print(" High Risk");
  }
  else {
    lcd.print(" Low Risk");
  }
}

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
  lcd.print("RiskRadar");
  lcd.setCursor(0, 1);
  lcd.print("HackED 2023");
  delay(5000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  mic1 = get_microphone_1_boolean();
  mic1_array[mic1_index] = mic1;
  mic1_index++;
  if (mic1_index > 1000) {
    mic1_index = 0;
    if (Count_array(mic1_array)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("High Noise Risk");
      DisplayTemp();
      delay(4000);
      }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Noise Risk");
      DisplayTemp();
      delay(2000);
    }
    }
  }
