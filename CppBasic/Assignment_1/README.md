# IoT Datainsamlare – Inlämningsuppgift 1

## 📘 Beskrivning
Programmet samlar in, analyserar och presenterar datumstämplade temperatur värden från saturnus is måne Dione.  
Det innehåller funktioner för att beräkna statistik, spara/ladda data, samt simulera sensormätningar.

---

## 📂 Projektstruktur (exempel)

```text
CppBasic.cpp            # Initialisering och startpunkt.
Controller.h            # Headerfil för Klassen som styr övergripande menyval och logik.
Controller.cpp          # Koden till Controller klassen.
DataCollector.h         # Header fil för insamling av data.
DataCollector.cpp       # Koden till ovan headerfil.
DataAnalyser.h          # Header fil för DataAnalyserings, koden kör matte på datan.
DataAnalyser.cpp        # Koden för dataanalysering.
README.md               # Denna fil
```


## ⚙️ Installation och körning

### Klona repositoryt:
```bash
git https://github.com/regrets123/STI_Tasks/tree/main/CppBasic
cd Assignment_1/
Programmet main är i CppBasic.cpp i root.
```


## 🧭 Användning (exempel)

Programmet visar en meny i terminalen:

```
Welcome to Saturn's moons Dione's Deep Ice Thermostat module.
Please input the corresponding option:
Input: 1 to calculate and display the current data.
Input: 2 to input new Data to the system.
Input: 3 to generate mock data.
Input: 4 to check for a specific temperature.
Input: 5 to check the data at a specific date.
Input: 6 to sort the data.
Input: 7 to Save the readings.
Input: 8 to Load previous readings.
Input: 9 to exit the module.

```
🧱 Tekniska val och motivering

Jag delade upp programmet i en överordnande kontroller för att hantera flödet av logiken.
En DataCollector klass för att hantera inmatning och en DataAnalyser klass för att analysera datan.

Jag använde Std:Map då datan ska sorteras, och den alltså sorteras automatiskt vid inmatning.
Map är fylld med std::pairs av std::time_t och float, där time_t representerar tidpunkten när mätningen gjordes och float representerar temperaturen i Celsius.
För att kunna sortera datan inte bara via KEY utan även value har jag en std::vektor buffer som jag återanvänder.
Jag använder time_t för att map själv ska kunna sortera den då den är en long long, och konverterar till annat format för att printa ut datumet i en mer läsbar form.
Vid data-analysering använder jag en Results struct då det blir för många variabler att skicka mellan funktioner.
Många metoder ska bara läsa datan och inte skriva in ny data, tex via dataanalyserings scriptet, då är de const.

Jag kontrollerar att inmatningen bara är siffror via Static GetValidNumber() och har ytterligare verifiering via GetValidYear() GetValidMonth() och GetValidDay().
Där kontrolleras med instruktioner att det är före 1970, innan nuvarande datum, och tar hänsyn för skottår kring februari för antal dagar i månaden.
Har lagt till Spara och Inläsning från csv fil som en provisorisk databas. Ursprungligen gjorde jag det som binär fil men det var inte inkluderat i uppgiftsbeskrivningen så skrev om det.
Jag hanterar inte tomma listor eller filfel, men har inte fått några errors när jag testat med tom lista.
Försökt använda pointers så mycket som möjligt för att koden ska vara så snabb som möjligt.

## 📊 Funktionalitet

| Funktion |
|----------|
Samtliga metoder är självförklarande i sina namn i förhållande till kontext som i vilken metod de används i eller i vilken klass de ligger i.
Har ni flera frågor kring funktion är ni välkomna att maila mig på lotus.saxe@gmail.com

🔬 Testning
Kort beskriv hur du testat programmet:

Jag har iterativt testat samtliga funktioner i programmet vid implementerings tid och vid förändringar.
Jag har testat upp till 100 genererade inmatningar och över 10 manuella utan problem, både med automatisk tidsgenerering och manuell tidsgenering.

💡 Utmaningar och lärdomar
Lärt mig om const och mutable, samt lite mer om templates och konstruktorer. I övrigt kunde jag det mesta sedan tidigare.
