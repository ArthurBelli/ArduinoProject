#include <Arduino.h>

short doorPort = 9;
short relayPort = 8;
short startPort = 7;
short stdMinutes = 15;
short stdSeconds = 0;
short minutes, seconds;
bool firstTime, letsStart; //wether show greeting or not

void setup() {
  pinMode(doorPort, INPUT);
  pinMode(relayPort, OUTPUT);
  digitalWrite(relayPort, LOW);
  Serial.begin(9600);
  firstTime = true; 
  minutes = stdMinutes;
  seconds = stdSeconds;
  letsStart = false;
}

void PrintTime() {
  Serial.print("Resta(m) ");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  if(!seconds) {
    seconds = 59;
    minutes--;
  } else {
    seconds--;
  }
}

void PrintTimer() {
  for (int i = 5; i; i--) {
    Serial.print("Vamos comecar em ");
    Serial.println(i);
    delay(1000);
  }
}

void loop() {
  while(!digitalRead(doorPort)) { //wether the door is open
    digitalWrite(relayPort, LOW); //turns off the relay because the door is open
    Serial.println("Por favor feche a porta");
    firstTime = true;
    minutes = stdMinutes;
    seconds = stdSeconds;
    letsStart = false;
  }
  if (digitalRead(startPort)) letsStart = true;
  if (letsStart) {
    if (minutes + seconds) {
      if (firstTime) {
        firstTime = false;
        PrintTimer();
        digitalWrite(relayPort, HIGH); //turns on the relays for the first time
      }
      PrintTime();
      digitalWrite(relayPort, HIGH); // 
    } else {
      digitalWrite(relayPort, LOW); //turns off the relays because the time ran off
      Serial.println("Limpeza concluida. Tenha um bom dia");
      delay(4000);
    }
  }
  delay(1000);
}

