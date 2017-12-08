#include <Wire.h>
#include <Adafruit_DRV2605.h>

int soundSensorPIN = A0; 
Adafruit_DRV2605 drv;

//until when should we incrememt?? temp 
int freqInterval = 50;
unsigned long prevFreq;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  drv.begin();

  drv.selectLibrary(1);

  drv.setMode(DRV2605_MODE_INTTRIG);

}

void loop() {
  // put your main code here, to run repeatedly:

   //variable for current sensor value
   unsigned long currentFreq = analogRead(soundSensorPIN);
   //calculate change in sensor value
   calculateChange(currentFreq); 
}

void calculateChange(unsigned long thisFreq) { //
  if(thisFreq - prevFreq >= freqInterval)
  {
    //change waveform of virbration
    drv.setWaveform(0,3);  //play
    drv.setWaveform(1,0); //end waveform
    drv.go();  //play effect
  }
  else
  {
    //keep vibrating normally
    drv.setWaveform(0,14); //play effect 
    drv.setWaveform(1,0); //end waveform 
    drv.go(); //play waveform 
  }
 prevFreq = thisFreq;

  delay(500); 
}

