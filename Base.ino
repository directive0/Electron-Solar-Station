// This #include statement was automatically added by the Particle IDE.
#include "ThingSpeak/ThingSpeak.h"


int led = D0;               // This is where the LED is plugged in. The other side goes to a resistor connected to GND.
    
int photoresistor = A0;     // This is where the photoresistor is plugged in. The other side goes to the "power" pin (below).
int curtime;

int power = A5;             // This is the other end of your photoresistor. The other side is plugged into the "photoresistor" pin (above).
                            // The reason we have plugged one side into an analog pin instead of to "power" is because we want a very steady voltage to be sent to the photoresistor.
                            // That way, when we read the value from the other side of the photoresistor, we can accurately calculate a voltage drop.

float fuelvalue;            // Here we are declaring the float variable fuelvalue, which will be used to store the value of the battery level.
float lightvalue;           // Here we are declaring the float variable analogvalue, which will be used to store the value of the photoresistor.


TCPClient client;
unsigned long myChannelNumber = 98243;
const char * myWriteAPIKey = "SO91Y8RD3W5SHR5W";

// Next we go into the setup function.

void setup() {                                  // Since deep sleeps starts the whole program from setup EVERY time it wakes up, it just makes sense
                                                // to avoid using the loop function and keep everything in setup
    
ThingSpeak.begin(client);                       //activates the thingspeak library
    
    curtime=Time.hour();                        //Electron function to grab current time from the cloud
        
    FuelGauge fuel;                             //electron function to grab current battery value
    fuelvalue = fuel.getSoC();                  //parses the battery value as a percentage
    
    pinMode(photoresistor,INPUT);               // Our photoresistor pin is input (reading the photoresistor)
    pinMode(power,OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)

    // Next, write the power of the photoresistor to be the maximum possible, so that we can use this to measure the resistance of our photocell.
    digitalWrite(power,HIGH);
    
    lightvalue = analogRead(photoresistor);     // read voltage at the photocell. As light increases resistance drops, so it will appear more positive the brighter it gets.

    // Update the 2 ThingSpeak fields with the new data
    ThingSpeak.setField(1, (float)fuelvalue);                           //update field one as the battery value
    ThingSpeak.setField(2, (float)lightvalue);                          // update field two as the raw photocell reading
    ThingSpeak.setField(3, (float)(lightvalue/4095)*100);               //update field three as the percentage light value
    

    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);             // write to the api all at once.
    
    
    
    
    System.sleep(SLEEP_MODE_DEEP, 30 * 60);                             // go to sleep for 30 * 60 seconds.


}


void loop() {

}




