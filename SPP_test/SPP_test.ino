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
int incomingbyte0;
int incomingbyte1;
int incomingbyte2;
int incomingbyte3;
int incomingbyte4;
int counter;

Servo servo1;
Servo servo2;

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
  pinMode(8, OUTPUT);
  servo2.attach(8);
  int counter=0;
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
      incomingbyte0=(Serial.read());
      //SerialBT.write(Serial.read());
     
      servo1.write(incomingbyte0);
      
      
      
      
    }
    if(SerialBT.available()){
      Serial.println("check2");
      incomingbyte0=(SerialBT.read());
      incomingbyte1=(SerialBT.read());
      incomingbyte2=(SerialBT.read());
      incomingbyte3=(SerialBT.read());
      incomingbyte4=(SerialBT.read());
      
      incomingbyte1=incomingbyte1*10;
      incomingbyte2=incomingbyte2*10;
      incomingbyte3=incomingbyte3;
      incomingbyte4=incomingbyte4*10;
      
     
      Serial.print("ASCII");
      Serial.write(incomingbyte0);
      Serial.print("/n");
      Serial.write(incomingbyte1);
      Serial.print("/n");
      Serial.write(incomingbyte2);
      Serial.print("/n");
      Serial.write(incomingbyte3);
      Serial.print("/n");
      Serial.write(incomingbyte4);
      
      Serial.print("DEC, HEX");
      Serial.println(incomingbyte0, DEC);
      Serial.println(incomingbyte0, HEX);
      Serial.println(incomingbyte1, DEC);
      Serial.println(incomingbyte1, HEX);
      Serial.println(incomingbyte2, DEC);
      Serial.println(incomingbyte2, HEX);
      Serial.println(incomingbyte3, DEC);
      Serial.println(incomingbyte3, HEX);
      Serial.println(incomingbyte4, DEC);
      Serial.println(incomingbyte4, HEX);
      
      
      servo1.write(incomingbyte4);
      servo2.write(incomingbyte1);
      
      
      
    }
  } 
  else 
    firstMessage = true;
/*
  if(SerialBT.available()) {
    Serial.println("goes into write bracket");
    Serial.write(incomingbyte);
    if(counter==4){
    counter=0;
    }
    else{
    counter++;
    }
    //servo1.write(incomingbyte-166);
    //servo1.write(SerialBT.read());
   // servo2.write(map(PS3.getAnalogHat(LeftHatY), 0, 255, 180, 0));
  }
  
  
  else 
   {
     //Serial.println("check5");
    //servo1.write(90);
    //servo2.write(90);
   }
   
  */ 
    
//    if(PS3.getButtonClick(PS)) {
//      PS3.disconnect();
//   }
    
    
}
