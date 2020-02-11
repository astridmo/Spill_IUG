/* PINGPONG-SPILL FOR INGENIØRER UTEN GRENSER
 * 2019
*/

// For å laste opp kode: Ctrl+Shift+P 

// Bibliotek for LCD-skjerm:
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Bibliotek for lydsensor:
#include "pitches.h"

#define LIMIT 380                       // Grense for å si om ballen er foran sensor eller ikke
#define TimesBySensor 25                // Antall ganger du må være ved sensoren hver runde for å få poeng. Mink tallet for lettere spill. Øk tallet for vanskeligere spill.
#define Difficulty 7000                 // Vanskelighetsgrad på spillet. Øk tallet for lettere spill. Mink tallet for vanskeligere spill


const int SensorArr [5] = {A0, A1, A2, A3, A4};  // Array for utgangene til SensorNumber 1-5
int ValArr [5] = {0};
int LEDArr [5] = {2,3,4,5,6};           // Array for LED-pærene

uint8_t buttonPin = 8;                 // Setter knappen til inngang 8
uint8_t soundPin = 9;                  // Setter lydsensor til utgang 9

uint8_t SensorNumber = 0;              // Variabel for hvilken sensor ballen skal til
uint8_t points = 0;                    // Variabel for å telle poeng
uint8_t count = 0;                     // Variabel for antall ganger du har vært ved sensor pr runde
unsigned long int gameTime = 0;        // Variabel for hvor lang tid spiller bruker på 1 runde                                       
uint8_t int valPoints = 0;                     
uint8_t int highscore = 0;                    // Variabel for highscore 
boolean win;


// Konfigurer LCD skjerm til 0x27, 16 chars og 2 line display:
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Oppkobling av LCD-skjerm:
 *  GND -> GND
 *  VCC -> 5V
 *  SDA -> A4
 *  SCL -> A5
 *  
 *  Dette er en I2C skjerm, søk evt opp dette for mer info
 */

// LYDSENSOR:
// Vinnerlyd for når du får poeng
int melWin[] = {
    NOTE_G3, NOTE_A3, NOTE_C4
};

// Taperlyd
int melLoose[] = {
  NOTE_G3, NOTE_E3, NOTE_C3
};

// Varighet lyder:  
int noteDurations[] = {
  4, 4, 8
};

int melTick = NOTE_E6;
int tickDuration = 3;



void setup()
{

    for (int i = 0; i <=4; i++) {
    pinMode(LEDArr[i], OUTPUT);
  }
  
  pinMode(buttonPin, INPUT); // Erklærer buttonPin til input
  
  Serial.begin(9600);               // Starter seriell overvåker
  
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Points:  ");             // Skriver "Points" på LCD-skjerm
  lcd.setCursor(0,1);                 // Flytter koordinater (Det første tallet er x-koordinater, det andre er y-koordinater)
  lcd.print("Highscore:  ");          // Skriver "Highscore" på LCD-skjerm
  lcd.setCursor(11,1);                // Flytter koordinater
  lcd.print(highscore);               // Skriver ut highscore
  lcd.setCursor(8,0);                 // Flytter koordinater
  lcd.print(points);                  // Skriver ut poengsum
//
//  Serial.println("Void loop");        // --> Fjernes etter debugging
  newRound();
}


void loop()
{
valPoints = points;
gameTime = millis();

// --> Evt. legge inn en tidsbegrensning for hele spillet på 1 min her!

//Serial.println("Loop før whileløkke");  // --> Fjernes etter debugging
//Serial.print("valPoints:  ");           // --> Fjernes etter debugging
//Serial.println(valPoints);              // --> Fjernes etter debugging
//Serial.print("points:  ");              // --> Fjernes etter debugging
//Serial.println(points);                 // --> Fjernes etter debugging
//Serial.print("millis() - gameTime:  "); // --> Fjernes etter debugging
//Serial.println(millis()-gameTime);     // --> Fjernes etter debugging

while (millis()-gameTime < Difficulty && valPoints==points)
{

//  Serial.println("Loop før avlesing");  // --> Fjernes etter debugging
  
  ValArr[0] = analogRead(SensorArr[0]);       // Leser av verdien fra sensor nr 1
  ValArr[1] = analogRead(SensorArr[1]);       // Leser av verdien fra sensor nr 2
  ValArr[2] = analogRead(SensorArr[2]);       // Leser av verdien fra sensor nr 3
  ValArr[3] = analogRead(SensorArr[3]);       // Leser av verdien fra sensor nr 4
  ValArr[4] = analogRead(SensorArr[4]);       // Leser av verdien fra sensor nr 5

  IsBallBySensor(ValArr[SensorNumber]);
//
//  Serial.println("Loop etter funksjon");

// Starter tikkelyd dersom man har brukt mer enn 4 sek på å få poeng
if (millis()-gameTime > 4000){
  tikking();
  }

}

// Sjekker om man har fått poeng
if (points > valPoints){
  youWin();
  newRound();
 }
else {
  youLoose();
  newRound();
  }


}

// Funksjon for å skjekke om du er ved riktig sensor
void IsBallBySensor(int Val)
{
  Serial.print("Verdien ved sensoren er:  ");
  Serial.println(Val);

  while (Val < LIMIT) {
    count = count + 1;
    if (count > TimesBySensor){
      points = points + 1;
      count = 0;
      break;
     }
  Val = analogRead(SensorArr[SensorNumber]); 
  }
};


// Funksjon for å lage ny runde:
void newRound(){
//  Serial.println("newRound 1");                       // --> Fjernes etter debugging
  for (int i=0; i<=4; i++){
    digitalWrite(LEDArr[i],LOW);                 // Slår av alle pinnene
  }

  int NewNumber = random(0,5);                   // Velger et random tall mellom 0 og 4
  

  
  while (NewNumber == SensorNumber){            // Sjekker om det nye tallet er lik det forrige vi valgte
   NewNumber = random(0,5);                     // Velger evt nytt tall
  }
  SensorNumber = NewNumber;

  Serial.print("LED nr ");                              // --> Fjernes etter debuging
  Serial.print(SensorNumber);                              // --> Fjernes etter debuging
  Serial.println("  skal lyse");                        // --> Fjernes etter debuging

  digitalWrite(LEDArr[SensorNumber],HIGH);             // Setter på valgt LED-pære

} 


// Funksjon hvis du får poeng
void youWin(){
  win = 1;
  sounds();                           // Lager poenglyd
  lcd.setCursor(8,0);                 // Flytter koordinater
  lcd.print(points);                  // Skriver ut poengsum
}

// --> Evt en funksjon for når tidsbegrensningen på 1 min er over

// Funksjon hvis du taper spillet
void youLoose(){
  
  // Sjekker om vi har ny highscore:
  if (points > highscore) {           
    highscore = points;
    lcd.setCursor(11,1);                // Flytter koordinater til "highscore"
    lcd.print(highscore);               // Skriver ut highscore

    // Ved ny highscore lages points-lyd 3 ganger
    for (int i = 1; i <= 3; i++){
     sounds();
      }
    }
  // Hvis ikke highscore => Taperlyd
  else {
  win = 0;
  for (int i = 1; i <= 6; i++){
    sounds();
    }
  }

  // While-løkke for å vente med å starte nytt spill helt til spiller trykker på knappen
  int buttonState = 0;
  while(buttonState==0){
    buttonState = digitalRead(buttonPin); // Serien vil være åpen (gi ut verdi 0) helt til knapp trykkes ned
    }

  
  lcd.setCursor(8,0);                    // Flytter koordinater tilbake til "points" 
  points = 0;
  lcd.print(points);                     // Setter poengsum tilbake til 0 
}

// Funksjon for å spille av vinner/taper-melodi
void sounds() {
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    int noteDuration = 1000/noteDurations[thisNote];
    
    // Lyd for dersom man har fått poeng:
    if (win == true) {
    tone(soundPin, melWin[thisNote], noteDuration);
    }
    // Lyd dersom man har tapt spillet:
    else {
      tone(soundPin, melLoose[thisNote], noteDuration);
    }

    // Pause mellom notene for å klare å skille de:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

// Funksjon for tikke-lyd
void tikking() {
  tone(soundPin, melTick, tickDuration);
  int pauseBetweenTicks = tickDuration*20;
  delay(pauseBetweenTicks);
}
