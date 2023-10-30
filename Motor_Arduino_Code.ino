#include <Servo.h>

Servo myservo;

int pos = 0;
int pin2;
int pin3;
int pin4;
int pin5;
int pin6;

int max_limit = 30;
int delay_time = 15;
int toggle = 0; //changes whether info is for pondering or house speech. 0 is pondering and 1 is house 

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  runServo(0);
}

void runServo(int servo_direction){

  if(servo_direction == 1){ //roughly 0.5s
   for(pos = 0; pos <= max_limit; pos += 1){
    myservo.write(pos);
    delay(delay_time);
   }
  }

  if(servo_direction == 0){ //roughly 0.5s
    for(pos = max_limit; pos >= 0; pos -= 1){
      myservo.write(pos);
      delay(delay_time);
    }
  }
}

void readPins(){
  pin2 = digitalRead(2);
  pin3 = digitalRead(3);
  pin4 = digitalRead(4);
  pin5 = digitalRead(5);
  pin6 = digitalRead(6);
  Serial.println(pin2);
  Serial.println(pin3);
  Serial.println(pin4);
  Serial.println(pin5);
  Serial.println(pin6);
  Serial.println(" ");
}

void voiceLoop(int numTimes){
  int count = 0;
  while(count < numTimes*2){
    if(count%2 == 0){//if even number, then open mouth
      runServo(1);
    }
    else{
      runServo(0);
    }
    count = count + 1;
  }
}

void loop() {
  delay(1000);
  readPins();

  while(pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 0){ //neutral state
    readPins();
  }

  //pondering decisions
  if(pin2 == 1 && pin3 == 0 && pin4 == 0){ //pondNum1, 6 seconds
    voiceLoop(6);
  }
  else if(pin2 == 0 && pin3 == 1 && pin4 == 0){ //, 10 seconds
    voiceLoop(10);
  }
  else if(pin2 == 1 && pin3 == 1 && pin4 == 0){ //pondNum3, 13 seconds
    voiceLoop(13);  
  }
  else if(pin2 == 0 && pin3 == 0 && pin4 == 1){ //pondNum4, 11 seconds 
    voiceLoop(11);
  }
  else if(pin2 == 1 && pin3 == 0 && pin4 == 1){ //pondNum5, 13 seconds
    voiceLoop(13);
  }
  else if(pin2 == 0 && pin3 == 1 && pin4 == 1){ //pondNum6, 15 seconds
     voiceLoop(15);
  }
  else if(pin2 == 1 && pin3 == 1 && pin4 == 1){ //pondNum7, 13 seconds 
    voiceLoop(13);
  }

  runServo(0);
  delay(500);
  readPins();

  //house decisions
  if(pin5 == 0 && pin6 == 0){ //houseNum1, 13 seconds
    voiceLoop(13);
  }
  else if(pin5 == 1 && pin6 == 0){ //houseNum2, 9 seconds
    voiceLoop(9);
  }
  else if(pin5 == 0 && pin6 == 1){ //houseNum3, 13 seconds
     voiceLoop(13);
  }
  else if(pin5 == 1 && pin6 == 1){ //houseNum4, 8 seconds
     voiceLoop(8);
  }
  runServo(0);
}
