    /* 
 ML8511 UV Sensor Read Example
 By: Nathan Seidle
 SparkFun Electronics
 Date: January 15th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 The ML8511 UV Sensor outputs an analog signal in relation to the amount of UV light it detects.

 Connect the following ML8511 breakout board to Arduino:
 3.3V = 3.3V
 OUT = A0
 GND = GND
 EN = 3.3V

 These last two connections are a little different. Connect the EN pin on the breakout to 3.3V on the breakout.
 This will enable the output. Also connect the 3.3V pin of the breakout to Arduino pin 1.


 Test your sensor by shining daylight or a UV LED: https://www.sparkfun.com/products/8662

 This sensor detects 280-390nm light most effectively. This is categorized as part of the UVB (burning rays)
 spectrum and most of the UVA (tanning rays) spectrum.

 There's lots of good UV radiation reading out there:
 http://www.ccohs.ca/oshanswers/phys_agents/ultravioletradiation.html
 https://www.iuva.org/uv-faqs

*/
   //////////////////////////////////////////////
  //            Arduino UV Meter              //
 //            without NOKIA 5110 LCD        //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

//Hardware pin definitions
int UVOUT = A1; // UV-Sensor ML8511
int UVBOUT = A2; // UV-Sensor UVM-30B
int BATT = A3; // Spannungsteiler
String UVIndex;

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(UVOUT, INPUT);
  pinMode(UVBOUT, INPUT);
  pinMode(BATT, INPUT);

  Serial.println("UV example");
}

void loop()
{
  int uvLevel = averageAnalogRead(UVOUT);
  int uvbLevel = averageAnalogRead(UVBOUT);
  int battLevel = averageAnalogRead(BATT);

  float outputVoltage = 3.36 / 1024 * uvLevel; // VCC hardcoded
  float outputbVoltage = 3.36 / 1024 * uvbLevel * 1000;
  float battVoltage = 3.36 / 1024 * battLevel * 2;
 

  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the outputbVoltage to a UV intensity level

    if(outputbVoltage<50)
  {
    UVIndex = "0";
  }else if (outputbVoltage>50 && outputbVoltage<=227)
  {
    UVIndex = "0";
  }else if (outputbVoltage>227 && outputbVoltage<=318)
  {
    UVIndex = "1";
  }
  else if (outputbVoltage>318 && outputbVoltage<=408)
  {
    UVIndex = "2";
  }else if (outputbVoltage>408 && outputbVoltage<=503)
  {
    UVIndex = "3";
  }
  else if (outputbVoltage>503 && outputbVoltage<=606)
  {
    UVIndex = "4";
  }else if (outputbVoltage>606 && outputbVoltage<=696)
  {
    UVIndex = "5";
  }else if (outputbVoltage>696 && outputbVoltage<=795)
  {
    UVIndex = "6";
  }else if (outputbVoltage>795 && outputbVoltage<=881)
  {
    UVIndex = "7";
  }
  else if (outputbVoltage>881 && outputbVoltage<=976)
  {
    UVIndex = "8";
  }
  else if (outputbVoltage>976 && outputbVoltage<=1079)
  {
    UVIndex = "9";
  }
  else if (outputbVoltage>1079 && outputbVoltage<=1170)
  {
    UVIndex = "10";
  }else if (outputbVoltage>1170)
  {
    UVIndex = "11";
  }


  display.clearDisplay();
  // set text color / Textfarbe setzen
  display.setTextColor(WHITE);
    // set text size / Textgroesse setzen
  display.setTextSize(1);
  // set text cursor position / Textstartposition einstellen
  display.setCursor(1,0);
  // show text / Text anzeigen
  display.println("UV-Index mW/cm2");
  display.setTextSize(2);
  display.setCursor(60,10);
  display.println(uvIntensity);

  display.setTextSize(1);
  // set text cursor position / Textstartposition einstellen
  display.setCursor(1,32);
  // show text / Text anzeigen
  display.println("UV-Index 0-11");
  
  display.setTextSize(2);
  display.setCursor(60,42);
  display.println(UVIndex);

  display.setTextSize(1);
  display.setCursor(90,32);
  display.println(battVoltage);

    
  display.display();
  delay(1000);
  display.clearDisplay();


}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}



//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
