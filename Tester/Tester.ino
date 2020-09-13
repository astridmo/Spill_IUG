/* Laget av: Astrid Moum | astridmo@nmbu.no
 * 
 * Dette er en oversikt over noe som kan gjøres for å gjøre koden mer effektiv: 
 * Understreker at dette ikke er testet i koden, og må testes før det implementeres i master
 * 
*/



void setup() {

  // 1. Linjen under fungerer kanskje for å slå av alle pærene samtidig i stedet for å bruke en for-løkke
  pinMode(LEDArr[],OUTPUT);      
}

void loop() {
  // 2. Når man starter en ny runde, så lyser fortsatt den siste pæren fra forrige spill/runde. Koden under fungerer dermed kanskje for å slå av alle
  // lyspærene samtidig når en ny runde starter:
  digitalWrite(LEDArr[], LOW);     

  // 3. Fikse å skrive ut 0 i poeng etter du har fått highscore.

  // 4. Kan gjøre om sound()-funksjonen til å ha input i stedet for global variabel win.

  // 5. Evt lage en tidsbegrensning for spillet dersom spillet er for lett (Tidsbegrensning som at man har max 3 minutter å spille på).
}
