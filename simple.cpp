#include <Arduino.h>

short doorPort = 9;
short relayPort = 8;
short stdMinutes = 15;
short stdSeconds = 0;
short minutes, seconds;
bool primeiraVez;

void setup() {
  pinMode(doorPort, INPUT);
  pinMode(relayPort, OUTPUT);
  digitalWrite(relayPort, LOW);
  Serial.begin(9600);
  primeiraVez = true; //wether the display message should appear (only on the first time)
  minutes = stdMinutes;
  seconds = stdSeconds;
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
    digitalWrite(relayPort, LOW); //turns off the relay bc the door if the door is open
    Serial.println("Por favor feche a porta");
  }
  if (minutes + seconds) {
    if (primeiraVez) {
      primeiraVez = false;
      PrintTimer();
      digitalWrite(relayPort, HIGH); //turns on the relays
    }
    PrintTime();
    digitalWrite(relayPort, HIGH);
  } else {
    digitalWrite(relayPort, LOW); //turns off the the relays bc the time ran off
    Serial.println("Limpeza concluida. Tenha um bom dia");
    delay(4000);
  }
  delay(1000);
}

