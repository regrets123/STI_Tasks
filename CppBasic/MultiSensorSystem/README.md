# IoT Datainsamlare – MultiSensorSystem

## 📘 Beskrivning
Programmet samlar in, analyserar och presenterar datumstämplade sensorvärden i olika format, både temperatur och luftfuktighet.  
Det innehåller funktioner för att beräkna statistik, spara/ladda data, samt simulera sensormätningar.

---

## 📂 Projektstruktur (exempel)

```text
CppBasic.cpp              # Startpunkt för koden via main(), samt initialisering av klasserna.
Measurement.h             # Definitionen för Measurement struct, samt statistic struct.
Sensor.cpp                # Kod file för sensorerna.
Sensor.h                  # Header fil för Senor klassen.
Storage.cpp               # Koden för förvaring och analysering av data..
Storage.h                 # Header fil för förvaring och analysering av data.
UserInterface.cpp         # Kod fil för UserInterface, hanterar input och output
UserInterface.h           # Header fil för UserInterface, hanterar input och output.
Utils.cpp                 # Koden för för Utilitetsfunktioner.
Utils.h                   # Header filen för Utilitetsfunktioner.
README.md                 # Denna fil
```


## ⚙️ Installation och körning

### Klona repository:
```bash
git https://github.com/regrets123/STI_Tasks/tree/main/CppBasic
cd MultiSensorSystem/
Programmet main är i CppBasic.cpp i root.
```


## 🧭 Användning (exempel)

Programmet visar en meny i terminalen:

```
========================================
       SENSOR MANAGEMENT SYSTEM
========================================
1. Read new measurements from all sensors
2. Show statistics per sensor
3. Show all measurements
4. Save all measurements to file
5. Load measurements from file
6. Exit program
========================================
Choose an option (1-6):

```
🧱 Tekniska val och motivering

Jag delade upp programmet i Storage, Sensor och UserInterface samt structs för measurement och statistics. Lite extra funktionalitet ligger även i utils.h.
Jag separerar Sensortyperna via enum som översätts i Utils till strängar eller ints. Storage hanterar datahantering och mattematik samt save och load.
UserInterface hanterar lättare logik och print(cout). CppBasic är 

## 📊 Funktionalitet

| Funktion |
|----------|
Samtliga metoder är självförklarande i sina namn i förhållande till kontext som i vilken metod de används i eller i vilken klass de ligger i.
Har ni flera frågor kring funktion är ni välkomna att maila mig på lotus.saxe@gmail.com

🔬 Testning
Kort beskriv hur du testat programmet:

Jag har iterativt testat samtliga funktioner i programmet vid implementerings tid och vid förändringar.
Jag har testat att läsa, spara, ladda och ladda igen. Starta om och ladda gammal data. 

💡 Utmaningar och lärdomar
Största utmaningen var att det blev för mycket matte och logik i user interface klassen så fick refakturera den mer.
Skulle vilja vara mer strikt i framtiden så UserInterface bara tar emot structs eller strängar och printar dem. 
