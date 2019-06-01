// Servo

#include <Servo.h>

Servo servoClaw;  
Servo servoTail1;
Servo servoTail2;
Servo servoTail3;

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
            servoClaw.write(90);
        }

        if(irdata == 2) {
            Serial.println("2: Claw open");
            servoClaw.write(150);
        }    


        if(irdata == 3) {
            Serial.println("3: Tail 1 +");
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

void turnServo(Servo servoMotor,int value){
    servoMotor.write(value);
}
