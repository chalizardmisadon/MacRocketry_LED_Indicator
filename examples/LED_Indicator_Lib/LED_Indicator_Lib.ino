//start of header file ====================================================================================================
#ifndef MacRocketry_LED_Indicator_h
#define MacRocketry_LED_Indicator_h

#include <Arduino.h>  //include Arduino library

#define redPin 9
#define greenPin 6
#define bluePin 5

class MacRocketry_LED_Indicator {
  public:
    MacRocketry_LED_Indicator(void); //constructor

    bool setStatusBMP(bool stats);  //check BMP error
    bool setStatusGPS(int fix);     //check GPS error
    bool setStatusSD(bool stats);   //check SD error
    
    void setRGB(char r, char g, char b);
    void displayLED(void);
    
  private:
    bool BMP_Status;
    bool GPS_Status;
    bool SD_Status;
    char error;

};

#endif
//end of header file ====================================================================================================
//start of source file ====================================================================================================
#include <Arduino.h>  //include Arduino library
//#include <MacRocketry_LED_Indicator.h>

MacRocketry_LED_Indicator::MacRocketry_LED_Indicator(){   //constructor
  Serial.begin(115200); //begin serial communication to PC for debugging
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  BMP_Status = false;
  GPS_Status = false;
  SD_Status = false;

  error = 0b000; //0b means number is binary
  //bit set means working, bit clear means error

}

bool MacRocketry_LED_Indicator::setStatusBMP(bool stats){
  BMP_Status = stats;
  if (BMP_Status) error |= 0b100; //set bit
  else error &= 0b011; //clear bit
  displayLED();
  return BMP_Status;
}

bool MacRocketry_LED_Indicator::setStatusGPS(int fix){
  GPS_Status = 0 < fix;
  if (GPS_Status) error |= 0b010; //set bit
  else error &= 0b101; //clear bit
  displayLED();
  return GPS_Status;
}

bool MacRocketry_LED_Indicator::setStatusSD(bool stats){
  SD_Status = stats;
  if (SD_Status) error |= 0b001; //set bit
  else error &= 0b110; //clear bit
  displayLED();
  return SD_Status;
}

void MacRocketry_LED_Indicator::setRGB(char r, char g, char b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void MacRocketry_LED_Indicator::displayLED(){
  switch (error){
    case 0b000: //white --> BMP and GPS and SD errors
      analogWrite(redPin, 255);
      analogWrite(bluePin, 255);
      analogWrite(greenPin, 255);
    case 0b001: //red -> BMP and GPS errors
      analogWrite(redPin, 255);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
      break;
    case 0b010: //cyan -> BMP + SD error
      analogWrite(redPin, 0);
      analogWrite(bluePin, 255);
      analogWrite(greenPin, 255);
      break;
    case 0b011: //purple -> BMP error
      analogWrite(redPin, 255);
      analogWrite(bluePin, 255);
      analogWrite(greenPin, 0);
      break;    
    case 0b100: //cyan -> GPS + SD error
      analogWrite(redPin, 0);
      analogWrite(bluePin, 255);
      analogWrite(greenPin, 255);
      break;
    case 0b101: //yellow -> GPS error
      analogWrite(redPin, 255);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 255);
      break;
    case 0b110: //blue -> SD error
      analogWrite(redPin, 0);
      analogWrite(bluePin, 255);
      analogWrite(greenPin, 0);
      break;
    case 0b111: //green -> no errors
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 255);
      break;
    default: //off -> used if the input message matches none of the above for some reason
      analogWrite(redPin, 127);
      analogWrite(bluePin, 64);
      analogWrite(greenPin, 64);
      break;
  }
}
//end of source file ====================================================================================================




void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
