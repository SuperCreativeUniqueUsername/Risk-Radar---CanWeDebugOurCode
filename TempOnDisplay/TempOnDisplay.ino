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
int mic1_array[6000]; // 60 seconds
int mic1_index = 0;
int mic2_array[30000]; // 300 seconds
int mic2_index = 0;
int last_millis = millis();
int mic1;
int mic2;

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

int count_in_array(array, item) {
  // counts item in array
  int count = 0;
  for (int i = 0; i < sizeof(array); i += 1;) {
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

void main1() // runs every 100 milliseconds exactly
{
  loop_counter += 1;
  if (loop_counter == 100) {
    loop_counter = 0;
    DisplayTemp();
  }
  mic1 = get_microphone_1_boolean();
  mic2 = get_microphone_2_boolean();
  mic1_array[mic1_index] = mic1;
  mic2_array[mic2_index] = mic2;
  if (count_in_array(mic1_array, 1) >= 2) {
    // output warning
    
  }
  if (count_in_array(mic2_array, 1) >= 2) {
    // output more warning
  }

  //loop a few times getting mic data each time
}
