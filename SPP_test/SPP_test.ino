/*
 Example sketch for the RFCOMM/SPP Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <SPP.h>
#include <usbhub.h>
#include <Servo.h>

USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "1234"
//SPP SerialBT(&Btd, "Lauszus's Arduino","0000"); // You can also set the name and pin like so
int incomingbyte;
Servo servo1;

boolean firstMessage = true;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nSPP Bluetooth Library Started"));
  pinMode(9, OUTPUT);
  servo1.attach(9);
  
}
void loop() {
  Usb.Task(); // The SPP data is actually not send until this is called, one could call SerialBT.send() directly as well
  
  if(SerialBT.connected) {
    if(firstMessage) {
      Serial.println("check3");
      firstMessage = false;
      SerialBT.println(F("Hello from Arduino")); // Send welcome message
      //servo1.write(map(Serial.read(), 0, 255, 0, 180));
      //servo1.write(Serial.read());
    }
    if(Serial.available()){
      Serial.println("check1");
      incomingbyte=(Serial.read());
      //SerialBT.write(Serial.read());
      servo1.write(incomingbyte);
    }
    if(SerialBT.available()){
      Serial.println("check2");
      //Serial.write(Serial.write((SerialBT.read())));  //write to the monitor
      incomingbyte=(SerialBT.read());
      servo1.write(incomingbyte);
    }
  } 
  else 
    firstMessage = true;

  if(SerialBT.available()) {
    Serial.println("goes into write bracket");
    //servo1.write(SerialBT.read());
   // servo2.write(map(PS3.getAnalogHat(LeftHatY), 0, 255, 180, 0));
  }
  else 
   {
     //Serial.println("check5");
    //servo1.write(90);
    //servo2.write(90);
   }
    
//    if(PS3.getButtonClick(PS)) {
//      PS3.disconnect();
//   }
    
    
}
