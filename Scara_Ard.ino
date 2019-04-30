#define pi 3.14159265
#define encoderA1 2
#define encoderA2 3
#define encoderB1 20
#define encoderB2 21

int number;

//Motor A
const int enA = 6;
const int inA1 = 4;
const int inA2 = 5;
int thetaA = 0;
int thetaA_enc = 0;
//Motor B
const int enB = 7;
const int inB1 = 14;
const int inB2 = 15;
double thetaB = 0;
double thetaB_enc = 0;

//General
double input_endpos;
double actual_endpos;
const int lsA = 16;
const int lsB = 17;
const int solenoid = 18;
volatile bool lsAstat = false;
volatile bool lsBstat = false;
int counterA = 0;
int counterB = 0;

void encoder1() {
  
  if(digitalRead(encoderA1) == HIGH)
  {     // look for a low-to-high on channel A
  if (digitalRead(encoderA1) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoderA2) == LOW) {
      thetaA_enc++;         // CW
    }
    else {
      thetaA_enc--;         // CCW
    }
  }
  }
  
 
 }
void encoder2() {
  
  // look for a low-to-high on channel B
  if (digitalRead(encoderB2) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoderB1) == HIGH) {
      thetaB_enc++;         // CW
    }
    else {
      thetaB_enc--;         // CCW
    }
  }

  // Look for a high-to-low on channel B
  
                           //limiting thetaB to 1 rotation


}

//================================SETUP================================

void setup() {
  // put your setup code here, to run once:
pinMode(inA1,OUTPUT);
pinMode(inA2,OUTPUT);
pinMode(inB1,OUTPUT);
pinMode(inB2,OUTPUT);
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(encoderA1,INPUT);
pinMode(encoderA2,INPUT);
pinMode(encoderB1,INPUT);
pinMode(encoderB2,INPUT);
attachInterrupt(0,encoder1,CHANGE);
attachInterrupt(3,encoder2,CHANGE);
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //======================Serial protocol==========================
   if (Serial.available()){
    char axis_specifier = Serial.read();
    double axis_value = Serial.parseFloat();
    write_value_axis(axis_specifier, axis_value);
   }
    //=========================motor control============================

 //===========================motor A ==================================
  if(thetaA_enc > thetaA+10 || thetaA_enc < thetaA-10) //when the degree is still not right
  {
    
   if(thetaA_enc < thetaA - 28) {
    digitalWrite(inA1, LOW);           //CCW
    digitalWrite(inA2, HIGH);
    analogWrite(enA,105);
    Serial.print("CCW MOTOR1");
    //Searching for the right angle
  } else if(thetaA_enc > thetaA + 28){                                // for motor A
    digitalWrite(inA1, HIGH);           //CW
    digitalWrite(inA2, LOW);
    analogWrite(enA,105);
    Serial.print("CW MOTOR1");
  } 
  else{
    digitalWrite(inA1,LOW);
    digitalWrite(inA2,LOW);
    analogWrite(enA,0);
    Serial.print("STOP MOTOR1");
  }
  
  }
  Serial.print("counterA=");
  delay(200);
Serial.println(thetaA_enc);
if(thetaA_enc>256 || thetaA_enc<-256)       //limiting to one rotation
{
  thetaA_enc=0;
}

 
 
//============================motor B control=======================
 if(thetaB_enc > thetaB+10 || thetaB_enc < thetaB-10) // when the degree is still not right
  {
    
   if(thetaB_enc < thetaB - 20) {
    digitalWrite(inB1, LOW);           //CCW
    digitalWrite(inB2, HIGH);
    analogWrite(enB,255);
    Serial.print("CCW MOTOR2");
    //Searching for the right angle
  } else if(thetaB_enc > thetaB + 20){                                // for motor A
    digitalWrite(inB1, HIGH);           //CW
    digitalWrite(inB2, LOW);
    analogWrite(enB,255);
    Serial.print("CW MOTOR2");
  } 
  else{
    digitalWrite(inB1,LOW);
    digitalWrite(inB2,LOW);
    analogWrite(enB,0);
    Serial.print("STOP MOTOR2");      //STOP
  }
  
  }
  Serial.print("counterB=");
  delay(200);
Serial.println(thetaB_enc);
if(thetaB_enc>256 || thetaB_enc<-256)
{
  thetaB_enc=0;
}

}


void write_value_axis(char axis, double value)
{
  if (axis == 'A' )
    {
    thetaA = value;
    value=0;
    Serial.print("ThetaA=");
    Serial.println(thetaA);
    
    
   }
  else if (axis == 'B' )
   {
    thetaB = value;
    value = 0;
    
    Serial.print("ThetaB=");
    Serial.println(thetaB);
    
   }

   
}

