// Motor
#include <ZumoMotors.h>

#define LED_PIN 13

ZumoMotors motors;


// Infrared

#include <IRSendRev.h>

#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6

const int ir_freq = 38;                 // 38k

unsigned char dtaSend[20];


// Bluetooth

#include <SoftwareSerial.h>

#define RxD 6  // Plug the Bluetooth on the D6 pin
#define TxD 7

SoftwareSerial blueToothSerial(RxD,TxD);


// Functions

void dtaInit() {
    dtaSend[BIT_LEN]        = 11;      // all data that needs to be sent
    dtaSend[BIT_START_H]    = 179;      // the logic high duration of "Start"
    dtaSend[BIT_START_L]    = 90;     // the logic low duration of "Start"
    dtaSend[BIT_DATA_H]     = 11;     // the logic "long" duration in the communication
    dtaSend[BIT_DATA_L]     = 33;     // the logic "short" duration in the communication
    
    dtaSend[BIT_DATA_LEN]   = 1;      // Number of data which will sent. If the number is other, you should increase or reduce dtaSend[BIT_DATA+x].
    
    dtaSend[BIT_DATA+0]     = 128;      // data that will sent
}




void setup() {
  // Infrared
  Serial.begin(38400);
  dtaInit();

  // Init Servo

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  
  // Bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);  
  setupBlueToothConnection(); 
}

void loop() {

  char recvChar;

  while(1) {

    // Bluetooth
    if (blueToothSerial.available()) {
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);

        if(recvChar == '8') {
           Serial.println("Move forward");
           for (int speed = 0; speed <= 100; speed++){
             motors.setLeftSpeed(speed);
             motors.setRightSpeed(speed);
             delay(2);
           } 
        }


        if(recvChar == '2') {
           Serial.println("Move backward");
           for (int speed = 0; speed >= -100; speed--)
           {
             motors.setLeftSpeed(speed);
             motors.setRightSpeed(speed);
             delay(2);
           }
     
        }


        if(recvChar == '7') {
           Serial.println("Move backward right");
                         for (int speed = 0; speed <= 100; speed++){
                 motors.setLeftSpeed(speed);

                 delay(2);
               }
          
        }


        if(recvChar == '9') {
           Serial.println("Move backward left");
                         for (int speed = 0; speed <= 100; speed++){
                 motors.setRightSpeed(speed);
                 delay(2);
               }
          
        }


        if(recvChar == '1') {
           Serial.println("Move forward left");
                       for (int speed = 0; speed >= -100; speed--)
               {
                 motors.setLeftSpeed(speed);

                 delay(2);
               }  
        }


        if(recvChar == '3') {
           Serial.println("Move forward right");
                         for (int speed = 0; speed >= -100; speed--)
               {

                 motors.setRightSpeed(speed);
                 delay(2);
               }
        }


        if(recvChar == '5') {
           Serial.println("Move Stop");
                        
                 motors.setLeftSpeed(0);
                 motors.setRightSpeed(0);
                 delay(2);
               
        }



      
        // Claw
        if(recvChar == 'z') {
          dtaSend[BIT_DATA] = 1;
          IR.Send(dtaSend, 38);          
          Serial.println("Claw open");
        }

        if(recvChar == 's') {
          dtaSend[BIT_DATA] = 2;
          IR.Send(dtaSend, 38);
          Serial.println("Claw open");
        }

        // Tail 1
        if(recvChar == 'e') {
          dtaSend[BIT_DATA] = 3;
          IR.Send(dtaSend, 38);          
          Serial.println("3: Tail 1 +");
        }

        if(recvChar == 'd') {
          dtaSend[BIT_DATA] = 4;
          IR.Send(dtaSend, 38);
          Serial.println("4: Tail 1 -");
        }

        // Tail 2
        if(recvChar == 'r') {
          dtaSend[BIT_DATA] = 5;
          IR.Send(dtaSend, 38);          
          Serial.println("5: Tail 2 +");
        }

        if(recvChar == 'f') {
          dtaSend[BIT_DATA] = 6;
          IR.Send(dtaSend, 38);
          Serial.println("6: Tail 2 -");
        }

        // Tail 3
        if(recvChar == 't') {
          dtaSend[BIT_DATA] = 7;
          IR.Send(dtaSend, 38);          
          Serial.println("7: Tail 3 +");
        }

        if(recvChar == 'g') {
          dtaSend[BIT_DATA] = 8;
          IR.Send(dtaSend, 38);
          Serial.println("8: Tail 3 -");
        }

        
      }
    
  }
  delay(500);
  /*
      dtaSend[BIT_DATA] = 1;
      IR.Send(dtaSend, 38);
      
      delay(2000);
  
      dtaSend[BIT_DATA] = 2;
      IR.Send(dtaSend, 38);
          
      delay(2000);
  
      dtaSend[BIT_DATA] = 3;
      IR.Send(dtaSend, 38);
      
      delay(2000);
  
      dtaSend[BIT_DATA] = 4;
      IR.Send(dtaSend, 38);
      
      delay(2000);
  
      dtaSend[BIT_DATA] = 5;
      IR.Send(dtaSend, 38);
          
      delay(2000);
  
      dtaSend[BIT_DATA] = 6;
      IR.Send(dtaSend, 38);
      
      delay(2000);
  
      dtaSend[BIT_DATA] = 7;
      IR.Send(dtaSend, 38);
          
      delay(2000);
  
      dtaSend[BIT_DATA] = 8;
      IR.Send(dtaSend, 38);
  
     delay(2000);
  */
}


void setupBlueToothConnection() {
  Serial.println("setupBlueToothConnection");
  blueToothSerial.begin(38400);
  blueToothSerial.print("\r\n+STWMOD=0\r\n");
  blueToothSerial.print("\r\n+STNA=Batcar\r\n");
  blueToothSerial.print("\r\n+STPIN=6666\r\n");
  blueToothSerial.print("\r\n+STOAUT=1\r\n");
  blueToothSerial.print("\r\n+STAUTO=0\r\n");
  delay(2000);
  blueToothSerial.print("\r\n+INQ=1\r\n");
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000);
  blueToothSerial.flush();
} 
