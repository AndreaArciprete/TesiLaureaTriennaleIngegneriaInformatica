//MASTER
#include <Servo.h>
#include "IRremote.h"
#include <Wire.h>


char v0[5] =  {};
int d;
int i;
int olddelta = 0;
int newdelta;
Servo myservo;
const int trigPin = 10;
const int echoPin = 11; 
// Variables for the duration and the distance
long duration;
int distance;
int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 5
char scelta;
char ritardo[2] = {};
int ritardo_int;


/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

 
void setup() {
    Wire.begin();
    Serial.begin(115200);
    #if FASTADC
    // set prescale to 8 
    cbi(ADCSRA, ADPS2);
    sbi(ADCSRA, ADPS1); 
    sbi(ADCSRA, ADPS0); 
    #endif
    //myservo.attach(9);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    irrecv.enableIRIn(); // Start the receiver
}

/*-----( Function )-----*/
char translateIR() // takes action based on IR code received
{
  switch(results.value)
  {
  case 0xFF6897: return '0'; break;
  case 0xFF30CF: return '1'; break;
  }// End Case
  delay(500);
}
 
void loop() {
  if (scelta != '0' && scelta != '1'){
if (irrecv.decode(&results)) // have we received an IR signal?
  {
    scelta = translateIR(); 
    irrecv.resume(); // receive the next value
  }
  }
 while(scelta == '0'){ //modalità localizzazione sonora
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
while (v0[2] == 'd'){
  myservo.detach();
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    scelta = translateIR(); 
    irrecv.resume(); // receive the next value
    if (scelta == '1') {
      scelta = '1'; 
      break;
    }
    else {
      scelta = '0';
    }
  }
  Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
}
if (scelta == '1') break;
myservo.attach(9);
//primo if
if (v0[0] == 's' && v0[2] == 'c'){ //if (v1 < v0)
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
ritardo[0]= v0[3];
ritardo[1] = v0[4];
ritardo[2] = '\0';
ritardo_int = atoi(ritardo);
//Serial.println(ritardo_int);
for (i = olddelta; i < 180; i+=1){
  //Serial.println(ritardo_int);
delay(ritardo_int);
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
ritardo[0]= v0[3];
ritardo[1] = v0[4];
ritardo[2] = '\0';
ritardo_int = atoi(ritardo);
while (v0[2] == 'd'){
  myservo.detach();
  Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
}
    //delay(40);
    myservo.write(i);
    Serial.println(i);
    if( v0[1] == 'a' && v0[2] == 'c'){
      while(v0[1] == 'a' && v0[2] == 'c'){
        //nuovo codice
        while(v0[1] == 'a' && v0[2] == 'c'){
        myservo.detach();
          Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
        }
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
   // Serial.println(i);
    //myservo.write(i);
    if( v0[1] == 'b' && v0[2] == 'c' ){
      break;
    }
        } //fine while
        break;
    }
    if (v0[0] == 'n' && v0[2] == 'c')  break;
   }//fine for
   olddelta = i;
   } //fine if
   else { //v1 > v0
    Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
ritardo[0]= v0[3];
ritardo[1] = v0[4];
ritardo[2] = '\0';
ritardo_int = atoi(ritardo);
//Serial.println(ritardo_int);
    for (i = olddelta; i > 0; i-=1){
      //Serial.println(ritardo_int);
    delay(ritardo_int);
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
} 
ritardo[0]= v0[3];
ritardo[1] = v0[4];
ritardo[2] = '\0';
ritardo_int = atoi(ritardo);
while (v0[2] == 'd'){
  myservo.detach();
  Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
}
    //delay(40);
    myservo.write(i);
    Serial.println(i);
    if( v0[1] == 'a' && v0[2] == 'c'){
      while(v0[1] == 'a' && v0[2] == 'c'){
        //nuovo codice
        while(v0[1] == 'a' && v0[2] == 'c'){
        myservo.detach();
          Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
}
        }
Wire.requestFrom(3,5);
while(Wire.available()){
  v0[d] = Wire.read();
  //Serial.println(v0[d]);
  d++;
  if (d>=5){d=0;}  
} 
    //Serial.println(i);
    //myservo.write(i);
    if( v0[1] == 'b' && v0[2] == 'c' ){
      break;
    }
        } //fine while
      break;
    }
    if (v0[0] == 's' && v0[2] == 'c') break;
    }//fine for
   olddelta = i;
   }//fine else
    //delay(1);  //Repeat the process every second OR:
    //while(1);       //Run code once
 } //fine scelta 0
if (scelta == '1'){ //modalità sonar
  myservo.attach(9);
while (scelta == '1'){
   if (irrecv.decode(&results)) // have we received an IR signal?
  {
    scelta = translateIR(); 
    irrecv.resume(); // receive the next value
    if (scelta == '0') {
      scelta = '0'; 
      break;
    }
  }  
// rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++){ 

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    scelta = translateIR(); 
    irrecv.resume(); // receive the next value
    if (scelta == '0') {
      scelta = '0'; 
      break;
    }
  }  
  delay(5);
  myservo.write(i);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
if (scelta == '0') {
  scelta = '0';
  break;
  }
  // Repeats the previous lines from 180 to 0 degrees
  for(int i=180;i>0;i--){ 
     if (irrecv.decode(&results)) // have we received an IR signal?
  {
    scelta = translateIR(); 
    irrecv.resume(); // receive the next value
    if (scelta == '0') {
      scelta = '0';
      break;
    }
  }   
  delay(5);
  myservo.write(i);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}//fine scelta 1 while
}//fine scelta 1
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
