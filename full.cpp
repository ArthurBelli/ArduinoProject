#include <Arduino.h>
#include <LiquidCrystal.h>

short doorPort = 9;
short relayPort = 8;
short stdMinutes = 15;
short stdSeconds = 0;
short backlight = 13;
short minutes, seconds;
short walk = 0;
bool primeiraVez, touch;
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() {
  pinMode(doorPort, INPUT);
  pinMode(relayPort, OUTPUT);
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  digitalWrite(relayPort, LOW);
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  primeiraVez = true; //wether the display message should appear (only on the first time)
  touch = false;
  minutes = stdMinutes;
  seconds = stdSeconds;
}

void PrintTime() {
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print("Resta(m) ");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds);
  if(!seconds) {
    seconds = 59;
    minutes--;
  } else {
    seconds--;
  }
}

void PrintWait() {
  delay(200);
  walk++;
  if(!touch) lcd.scrollDisplayRight();
  else lcd.scrollDisplayLeft();
  if(walk == 3) {
    touch = !touch;
    walk = 0;
  }
  lcd.setCursor(0,0);
  lcd.print("Feche a porta");
  lcd.setCursor(0,1);           
  lcd.print("para iniciar");
}

void PrintTimer() {
  for (int i = 5; i; i--) {
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print(0);
	  lcd.print(i);
    delay(1000);
  }
}

void PrintGoodbye() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Limpeza");
  lcd.setCursor(0,1);
  lcd.print("Concluida");
}

void loop() {
  while(!digitalRead(doorPort)) { //wether the door is open
    digitalWrite(relayPort, LOW); //turns off the relay bc the door if the door is open
    PrintWait(); //display message while the user doesnt close the door
  }
  if (minutes + seconds) {
    if (primeiraVez) {
      primeiraVez = false;
      PrintTimer();
      digitalWrite(relayPort, HIGH); //liga os relés
    }
    PrintTime();
    digitalWrite(relayPort, HIGH);
  } else {
    digitalWrite(relayPort, LOW); //turns off the the relays bc the time ran off
    PrintGoodbye();
    delay(4000);
  }
  delay(1000);
}

