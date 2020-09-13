# Spill_IUG
Pingpong-spill laget for IUG. Ment for bruk som markedsføring på stand

Laget av Astrid Moum, 2019 | astridmo@nmbu.no

Hardware medfølger

HVORDAN SPILLET FUNGERER:
-
- Vi har et langt gjennomsiktig plastrør med en pingpollball inni. 
- En LED-pære langs plastrøret starter å lyse, og målet er å få ballen hit.
- En vifte under røret er koblet til en generator og en dynamo (?). 
- Man genererer strøm ved å sveive på et håndtak som er festet til generatoren.
- Viften får generert strøm, og det må sveives i en hastighet slik at ballen kommer til LED-pæren
- Kommer ballen til LED-lampen iløpet av 7 sekunder får man et poeng, og en ny lampe starter å lyse
- Klarer man ikke å komme til LED-lampen på tiden taper man spillet
- Spillet startes på nytt ved å trykke på startknappen

HVORDAN FORANDRE VANSKELIGHETSGRAD:
-
Det er 2 ulike måter å forandre vanskelighetsgraden på spillet
1. #define MaxGameTime 7000
   - Denne definisjonen sier hvor lang tid man har på å få ett poeng.
   - Lettere spill: Velg en høyere verdi for MaxGameTime
   - Vanskeligere spill: Velg en lavere verdi for MaxGameTime
2. #define TimesBySensor 25
   - Denne definisjonen sier hvor mange ganger arduino-brettet må detektere ballen foran sensoren for at man skal få poeng. 
   - Lettere spill: Velg en lavere verdi enn 25
   - Vanskeligere spill: Velg en høyere verdi enn 25

UTSTYR:
- 
- Sensorer: GP2Y0A21YK0F Sharp IR Analog Distance Sensor Distance 10-80CM Cable For Arduin
- LED-lys: (fra intro Arduino sett)
- Knapp: Momentary button (fra intro Arduino-sett)
- Høyttaler: piezo buzzer (fra intro Arduino-sett)
- LCD-skjerm: I2C (fra intro Arduino-sett)

OPPKOBLING:
- 
- Sensorer: A0, A1, A2, A3, A4
- LED-lys: 2, 3, 4, 5, 6
- Knapp: 8
- Høyttaler: 9
- LCD-skjerm: GND->GND, VCC->5V, SDA->20, SCL->21


Takk for bidrag:
- 
Kode: Martin Sanderøy, Morten Sæther, Monty Hatfield, Silje Dale
