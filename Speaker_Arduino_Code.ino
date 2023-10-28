#include <SD.h> //Lib to read SD card
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h> //Lib to play auido
#include <SPI.h> //SPI lib for SD 

#define SD_ChipSelectPin 10
TMRpcm music; //Lib object is named "music"

//Sounds
char Pond1[] = "Pond1.wav";
char Pond2[] = "Pond2.wav";
char Pond3[] = "Pond3.wav";
char Pond4[] = "Pond4.wav";
char Pond5[] = "Pond5.wav";
char Pond6[] = "Pond6.wav";
char Pond7[] = "Pond7.wav";
char Home1[] = "Home1.wav";
char Home2[] = "Home2.wav";
char Home3[] = "Home3.wav";
char Home4[] = "Home4.wav";
char Grif[] = "Grif.wav";
char Sly[] = "Sly.wav";
char Rav[] = "Rav.wav";
char Huf[] = "Huf.wav";

//Sonar sensor
int trigPin = 7;
int echoPin = 8;
float duration;
float distance; //in cm

//Other variables
int MOSFET_Switch = 2;
int pondNum;
int homeNum;
int lastPondNum = 0;

void setup() {
  
  Serial.begin(9600);

  //Inter-Arduino Communication
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  //this is the reset state for the outputs
  digitalWrite(A0, LOW); 
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);

  //Sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //SD card initializing
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  else {
    Serial.println("SD card works!");
  }

  //speaker settings
  music.setVolume(5);    //   0 to 7. Set volume level
  music.quality(0);        //  Set 1 for 2x oversampling Set 0 for normal
  music.speakerPin = 9;

  //noise cancelling MOSFET
  pinMode(MOSFET_Switch, OUTPUT);
  digitalWrite(MOSFET_Switch, HIGH);

  //Random numbers
  randomSeed(analogRead(5)); //A5 is the random noise seed, leave unconnected!
}

float detectDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.0343)/2; 
  delay(100);
  Serial.println(distance);
  return distance;
}

void resetMotor(){
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
}

void loop() {
  digitalWrite(MOSFET_Switch, LOW);
  resetMotor();
  if(detectDistance() < 5){
    delay(2000);
    digitalWrite(MOSFET_Switch, HIGH);
    
    //pick pondering line 1-7
    pondNum = random(1,8); //selects value from 1-7 NOT 1-8
    if(lastPondNum == 0){
      //do nothing since it's the first loop through
    }
    else if(lastPondNum == pondNum){
      while(lastPondNum == pondNum){
        pondNum = random(1,8);
      }
    }
  
    lastPondNum == pondNum;
    
    if(pondNum == 1){
       digitalWrite(A0, HIGH); 
       digitalWrite(A1, LOW);
       digitalWrite(A2, LOW);
       if(!music.isPlaying()){
        music.play(Pond1);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else if(pondNum == 2){
       digitalWrite(A0, LOW); 
       digitalWrite(A1, HIGH);
       digitalWrite(A2, LOW);
       if(!music.isPlaying()){
        music.play(Pond2);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else if(pondNum == 3){
       digitalWrite(A0, HIGH); 
       digitalWrite(A1, HIGH);
       digitalWrite(A2, LOW);
       if(!music.isPlaying()){
        music.play(Pond3);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else if(pondNum == 4){
       digitalWrite(A0, LOW); 
       digitalWrite(A1, LOW);
       digitalWrite(A2, HIGH);
       if(!music.isPlaying()){
        music.play(Pond4);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else if(pondNum == 5){
       digitalWrite(A0, HIGH); 
       digitalWrite(A1, LOW);
       digitalWrite(A2, HIGH);
       if(!music.isPlaying()){
        music.play(Pond5);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else if(pondNum == 6){
       digitalWrite(A0, LOW); 
       digitalWrite(A1, HIGH);
       digitalWrite(A2, HIGH);
       if(!music.isPlaying()){
        music.play(Pond6);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
    else{
       digitalWrite(A0, HIGH); 
       digitalWrite(A1, HIGH);
       digitalWrite(A2, HIGH);
      if(!music.isPlaying()){
        music.play(Pond7);
        while(music.isPlaying()){
          //let music play
        }
      }
    }
  
    //Pick house selection
    homeNum = random(1,5); //number between 1-4
    if(homeNum == 1){
      digitalWrite(A3, LOW);
      digitalWrite(A4, LOW);
      if(!music.isPlaying()){
        music.play(Home1);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
      delay(500);
      if(!music.isPlaying()){
        music.play(Grif);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
    }
    else if(homeNum == 2){
      digitalWrite(A3, HIGH);
      digitalWrite(A4, LOW);
      if(!music.isPlaying()){
        music.play(Home2);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
      delay(500);
      if(!music.isPlaying()){
        music.play(Sly);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
    }
    else if(homeNum == 3){
      digitalWrite(A3, LOW);
      digitalWrite(A4, HIGH);
      if(!music.isPlaying()){
        music.play(Home3);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
      delay(500);
      if(!music.isPlaying()){
        music.play(Huf);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
    }
    else {
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      if(!music.isPlaying()){
        music.play(Home4);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
      delay(500);
      if(!music.isPlaying()){
        music.play(Rav);
        while(music.isPlaying()){
          //wait for sound to stop
        }
      }
    }
  }
}
