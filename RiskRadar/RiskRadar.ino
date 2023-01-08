
/* 
   DHT11 Temperature and Humidity Sensor With Arduino
   For more details, visit: https://techzeero.com/arduino-tutorials/dht11-with-arduino/
*/

// Declaration and initialization of input pins for microphone 1
int Analog_In = A1; // Analog output of the sensor
// microphone 2
int Analog_In2 = A2;
int Digital_Input_mic1 = 7; // Digital output of the sensor
int Digital_Input_mic2 = 8;
// button
int Digital_Input3 = 2;

// stuff for humidity and temp sensor
#include <dht.h>
#include <vector>

#define dht_pin A0     // Analog Pin A0 of Arduino is connected to DHT11 out pin
 
dht DHT;
 
void setup()
{
  // temp/hum sensor
  Serial.begin(9600);
  delay(500);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);

  // microphone 1
  pinMode(Digital_Input_mic1, INPUT);
  //microphone 2
  pinMode(Digital_Input_mic2, INPUT);
  // button
  pinMode(Digital_Input3, INPUT);
}
 
void loop()
{
  // temp/hum sensor
  DHT.read11(dht_pin);
    
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%    ");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println(" C");
    
  //delay(5000); //Reduce Time for Quick Reply 

  // microphone 1
  float Analog;
  int Digital;
  // microphone 2
  float Analog2;
  int Digital2;
  // button
  int Digital3;
    
  //Current values are read out, converted to the voltage value...
  Analog =  analogRead(Analog_In);
  Digital = digitalRead(Digital_Input);
  Analog2 = analogRead(Analog_In2);
  Digital2 = digitalRead(Digital_Input2);
  Digital3 = digitalRead(Digital_Input3);
  
  Serial.print("button pressed:"); Serial.println(Digital3);
  //...  and issued at this point
  Serial.print("Analog voltage value 1:");  Serial.print(Analog,  4) ;   Serial.print(", ");
  Serial.print("Limit value 1:") ;
  
  if (Digital==1) 
  {
    Serial.println("reached");
  }
  else
  {
    Serial.println(" not yet reached");
  }

  Serial.print("Analog voltage value 2:"); Serial.print(Analog2, 4); Serial.print(",  ");
  Serial.print("Limit value 2:");
  if (Digital2==1) 
  {
    Serial.println("reached");
  }
  else
  {
    Serial.println(" not yet reached");
  }

  Serial.println("----------------------------------------------------------------") ;
  delay(100) ;
}

bool get_microphone_1_boolean() {
  bool mic1
  mic1 = (bool)digitalRead(Digital_Input_mic1)
  return mic1
}

bool get_microphone_2_boolean() {
  bool mic2
  mic2 = (bool)digitalRead(Digital_Input_mic2)
  return mic2
}
