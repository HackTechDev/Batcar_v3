// Servo

#include <Servo.h>

Servo servoClaw;  
Servo servoTail1;
Servo servoTail2;
Servo servoTail3;

#include "TM1637.h"
#define CLK 10 //pins definitions for TM1637 and can be changed to other ports
#define DIO 11
TM1637 tm1637(CLK,DIO);


// Infrared

#include <IRSendRev.h>

#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6

const int pinRecv = 2;              // ir receiver connect to D2

void setup() {
    Serial.begin(115200);


  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  display4LED(4, 3, 2, 1);

    // Servo
    Serial.println("Init Servo"); 

    servoClaw.attach(7);
    servoTail1.attach(8);
    servoTail2.attach(9);
    servoTail3.attach(10);


    servoClaw.write(40);
    delay(1000);
    servoClaw.write(140);
    delay(1000);
    servoClaw.write(40);


    turnServo(servoTail1, 90);
    turnServo(servoTail2, 90);
    turnServo(servoTail3, 90);

    // Infrared
    Serial.println("Init Infrared");
    IR.Init(pinRecv);

}

unsigned char dta[20];
int irdata;

void loop() {
    // get IR data
    if( IR.IsDta() ) {
        // receive data to dta
        IR.Recv(dta);               
        irdata = dta[BIT_DATA];

        if(irdata == 1) {
            Serial.println("1: Claw close");
            display4LED(0, 0, 0, 1);

            servoClaw.write(90);
        }

        if(irdata == 2) {
            Serial.println("2: Claw open");
            display4LED(0, 0, 0, 2);
 
            servoClaw.write(150);
        }    


        if(irdata == 3) {
            Serial.println("3: Tail 1 +");
            display4LED(0, 0, 0, 3);
            
            int angle = servoTail1.read();
            if ( angle == 10) {
                turnServo(servoTail1, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail1, 170);
            }            
        }

        if(irdata == 4) {
            Serial.println("4: Tail 1 -");
            display4LED(0, 0, 0, 4);
            
            int angle = servoTail1.read();
            if ( angle == 170) {
                turnServo(servoTail1, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail1, 10);
            }
        }   

        if(irdata == 5) {
            Serial.println("5: Tail 2 +");
            display4LED(0, 0, 0, 5);
            
            int angle = servoTail2.read();
            if ( angle == 10) {
                turnServo(servoTail2, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail2, 120);
            }            
        }

        if(irdata == 6) {
            Serial.println("6: Tail 2 -");
            display4LED(0, 0, 0, 6);
            
            int angle = servoTail2.read();
            if ( angle == 120) {
                turnServo(servoTail2, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail2, 10);
            }           
        }   


        if(irdata == 7) {
            Serial.println("7: Tail 3 +");
            display4LED(0, 0, 0, 7);
            
            int angle = servoTail3.read();
            if ( angle == 20) {
                turnServo(servoTail3, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail3, 160);
            }          
        }

        if(irdata == 8) {
            Serial.println("8: Tail 3 -");
            display4LED(0, 0, 0, 8);
            
            int angle = servoTail3.read();
            if ( angle == 160) {
                turnServo(servoTail3, 90);
            }
            if ( angle == 90) {
                turnServo(servoTail3, 20);
            }           
        }   

    }
}


void display4LED(int led0, int led1, int led2, int led3) {
  tm1637.display(0, led0);
  tm1637.display(1, led1);
  tm1637.display(2, led2);
  tm1637.display(3, led3);
}

void turnServo(Servo servoMotor,int value){
    servoMotor.write(value);
}
