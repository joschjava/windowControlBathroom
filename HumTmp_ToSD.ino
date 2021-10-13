/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include <DHT.h>

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

File myFile;

const long interval = 2000;          
unsigned long previousMillis = 0;        // will store last time LED was updated



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  dht.begin();

}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        unsigned long currentMillis = millis();
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        //Read data and store it to variables hum and temp
        hum = dht.readHumidity();
        temp= dht.readTemperature();
    
        // if the file opened okay, write to it:
      if (myFile) {
        myFile.print(hum);
        myFile.print(";");
        myFile.print(temp);
        myFile.print("\n");
        myFile.flush();
    
        
        // close the file:
       // myFile.close();
        Serial.print(hum);
        Serial.print(";");
        Serial.print(temp);
        Serial.print("\n");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
    }
}
