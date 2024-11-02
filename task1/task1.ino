#include <Arduino.h>

#define btn 33
#define red 4
#define green 5
#define yellow 19
#define blue 22 

void setup() {
  //defining button input
  pinMode(btn, INPUT);
  //serial begin
  Serial.begin(115200);
  
  //led configureation
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  
  static int count;
  
  static int prev_btn = 0;
  
  int btns = digitalRead(btn);
  //detect button press 
  if  (btns == 1 && prev_btn == 0){
    count++;
    Serial.println(count);
    // led turn off
    digitalWrite(red, 0);
    digitalWrite(green, 0);
    digitalWrite(yellow, 0);
    digitalWrite(blue, 0); 
           
    if (count == 1){
      digitalWrite(red, 1);
    }
    if (count == 2){
      digitalWrite(green, 1);
    }
    if (count == 3){
      digitalWrite(yellow, 1);
    }
    if (count == 4){
      digitalWrite(blue, 1);
    }
    if (count == 5){
      count = 0;
    }

  }
  prev_btn = btns;
  delay(100);


}
