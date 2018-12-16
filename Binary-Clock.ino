/*
An open-source binary clock for Arduino. 
Based on the code from by Rob Faludi (http://www.faludi.com)
Futher modified from code under (cc) by Daniel Spillere Andrade, www.danielandrade.net
http://creativecommons.org/license/cc-gpl
*/

int second=0, minute=0, hour=0; //start the time on 00:00:00
int munit,hunit,valm=0,valh=0,i;
bool ledsOn = true;

void setup() { //set outputs and inputs
pinMode(1, OUTPUT);pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);
pinMode(6, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(9, OUTPUT);pinMode(10, OUTPUT);
pinMode(11, OUTPUT);pinMode(12, OUTPUT);pinMode(13, OUTPUT);

for(i=1;i<=13;i++){
  digitalWrite(i, LOW);}

pinMode(0, INPUT);
}

void loop() {

static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second

// move forward one second every 1000 milliseconds

// Not 1000 because the arduino takes a while to so things.
// After first 12 hr run, mathed [seconds lost] / [seconds elapsed] and
// came up with an adjustment.  YMMV
if (millis() - lastTick >= 999) {
  lastTick = millis();
  second++;

}

// move forward one minute every 60 seconds
  if (second >= 60) {
  minute++;
  second = 0; // reset seconds to zero
}

// move forward one hour every 60 minutes
if (minute >=60) {
  hour++;
  minute = 0; // reset minutes to zero
}

if (hour >=24) {
  hour=0;
  minute = 0; // reset minutes to zero
}

  munit = minute%10; //sets the variable munit and hunit for the unit digits
  hunit = hour%10;


  if (!ledsOn) {
   
  for(i=1;i<=13;i++){
  digitalWrite(i, LOW);}
  
  } else  {

  //minutes units
  if(munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) {  digitalWrite(1, HIGH);} else {  digitalWrite(1,LOW);}
  if(munit == 2 || munit == 3 || munit == 6 || munit == 7) {digitalWrite(2, HIGH);} else {digitalWrite(2,LOW);}
  if(munit == 4 || munit == 5 || munit == 6 || munit == 7) {digitalWrite(3, HIGH);} else {digitalWrite(3,LOW);}
  if(munit == 8 || munit == 9) {digitalWrite(4, HIGH);} else {digitalWrite(4,LOW);}

  //minutes 
  if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {digitalWrite(5, HIGH);} else {digitalWrite(5,LOW);}
  if(minute >= 20 && minute < 40)  {digitalWrite(6, HIGH);} else {digitalWrite(6,LOW);}
  if(minute >= 40 && minute < 60) {digitalWrite(7, HIGH);} else {digitalWrite(7,LOW);}

  //hour units
  if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {digitalWrite(8, HIGH);} else {digitalWrite(8,LOW);}
  if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {digitalWrite(9, HIGH);} else {digitalWrite(9,LOW);}
  if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {digitalWrite(10, HIGH);} else {digitalWrite(10,LOW);}
  if(hunit == 8 || hunit == 9) {digitalWrite(11, HIGH);} else {digitalWrite(11,LOW);}

  //hour
  if(hour >= 10 && hour < 20)  {digitalWrite(12, HIGH);} else {digitalWrite(12,LOW);}
  if(hour >= 20 && hour < 24)  {digitalWrite(13, HIGH);} else {digitalWrite(13,LOW);}

  }

  valm = analogRead(0);    // add one minute when pressed
   if(valm<50) {
   minute++;
   second=0;
   delay(250);
  }
  
  valh = analogRead(5);    // add one hour when pressed
   if(valh<50) {
   hour++;
   second=0;
   delay(250);
  }

  if (analogRead(2) < 50) {   // Button to turn LEDs on or off
    ledsOn = !ledsOn;
    delay(250);
  }
}
