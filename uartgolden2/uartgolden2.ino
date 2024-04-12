#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
uint8_t trame[10];
uint8_t senddata[4] = {0x66, 0x42, 0x00, 0xA8};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  

}

void loop() {
  // Send Read Parameter command
  readParameter(0x42);
     delay(100);

  // Wait for the response
      int i=0;

  if (mySerial.available() > 0) { // Minimum expected response length
    // Read and process the response
    for(i=0;i<10;i++){
    trame[i]=mySerial.read();
     Serial.println(trame[i]);
     delay(100);
    }
  

    
    }
  }



void readParameter(byte parameter) {
byte start = 0x66;  
byte length = 0x00;
  uint16_t crc = 0xa8;
  
int i=0;
for(i=0;i<4;i++){
mySerial.write(senddata[i]);

}
  /*mySerial.write(parameter);
  mySerial.write(length);
  mySerial.write(crc);
   mySerial.write(crc1); 
   mySerial.write(crc2);
   mySerial.write(crc3); 
   mySerial.write(crc4);
    mySerial.write(crc5);
     mySerial.write(crc6);
          mySerial.write(crc7);*/

}
