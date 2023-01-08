#include <LiquidCrystal.h>
#include <dht.h>

#define dht_pin A0

dht DHT;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Digital_Input_mic1 = 7;
int Digital_Input_mic2 = 8;
int loop_counter = 0;
bool mic1_array[600]; // 6 seconds
int mic1_index = 0;
bool mic2_array[1000]; // 10 seconds
int mic2_index = 0;
int last_millis = millis();
bool mic1;
bool mic2;
int current_display = 0; // 0: intro, 1: temp/humid, 2: microphone
const int current_display_max = 2;
const int display_millis = 10000;
int current_display_millis = millis();

void DisplayIntro(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Risk Radar!");
  lcd.setCursor(0, 1);
  lcd.print("Workplace safety");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Made By Aiden,");
  lcd.setCursor(0, 1);
  lcd.print("Cedric and Griffin");
  delay(1500);
  lcd.scrollDisplayRight();
  delay(500);
  lcd.scrollDisplayRight();
  delay(1500);
}

void DisplaySound(bool mic1, bool mic2)
{
  lcd.clear();
  if (mic1 == 1) {
  lcd.setCursor(0, 0);
  lcd.print("Immidiate noise");
  lcd.setCursor(0, 1);
  lcd.print("risk!");
} else if (mic2 == 1) {
  lcd.setCursor(0, 0);
  lcd.print("Long-term noise");
  lcd.setCursor(0, 1);
  lcd.print("risk!");
} else {
  lcd.setCursor(0, 0);
  lcd.print("No noise risk");
}
}

void DisplayTemp(){
  // This function reads the temp and humidity data
  // and displays on the LCD
  lcd.clear();
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
}

bool get_microphone_1_boolean() {
  bool mic1 = digitalRead(Digital_Input_mic1);
  return mic1;
}

bool get_microphone_2_boolean() {
  bool mic2 = digitalRead(Digital_Input_mic2);
  return mic2;
}

int count_in_array(bool array[], bool item) {
  // counts item in array
  int count = 0;
  for (int i = 0; i < sizeof(array); i += 1) {
    if (array[i] == item) {
      count += 1;
    }
  }
  return count;
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
    main1();
  }
}
//----------------------------------------------Main Function-------------------------------------
void main1() // runs every 100 milliseconds exactly
{
  loop_counter += 1; // unused?
  if (millis() - current_display_millis >= display_millis) {
    current_display_millis += display_millis;
    current_display += 1;
    if (current_display > current_display_max) {
      current_display = 1; // skip intro screen
    }
    if (current_display == 0) {
      DisplayIntro();
    }
    else if (current_display == 1) {
      DisplayTemp();
    }
    else if (current_display == 2) {
      DisplaySound(mic1, mic2);
    }
  }
  mic1 = get_microphone_1_boolean();
  mic2 = get_microphone_2_boolean();
  mic1_array[mic1_index] = mic1;
  mic2_array[mic2_index] = mic2;
  if (count_in_array(mic1_array, 1) >= 2) { // high dB warning after 2 polls
    DisplaySound(mic1, mic2);
    current_display_millis += display_millis;
  }
  if (count_in_array(mic2_array, 1) >= 300) { // lower dB warning after 1/3 of the time of 5 minutes polls
    DisplaySound(mic1, mic2);
    current_display_millis += display_millis;
  }
}
