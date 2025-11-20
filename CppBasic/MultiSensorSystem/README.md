# IoT Datainsamlare – MultiSensorSystem med Larmsystem

## 📘 Beskrivning
Ett omfattande IoT-övervakningssystem som samlar in, analyserar och presenterar datumstämplade sensorvärden från tre typer av sensorer: temperatur, luftfuktighet och hastighet/rörelse. Systemet innehåller ett intelligent larmsystem som övervakar tröskelvärden, periodisk datainsamling i bakgrundstråd, samt funktioner för statistisk analys och datahantering (spara/ladda CSV).

---

## 📂 Projektstruktur

```text
main.cpp                      # Startpunkt - initialiserar sensorer och startar systemet
├── InitiateSensors()         # Skapar 12 sensorer med larmtrösklar

Sensors/
├── Sensor.h/.cpp             # Abstrakt basklass för alla sensorer
├── TemperatureSensor.h/.cpp  # Temperatursensor (-25°C till 60°C)
├── HumiditySensor.h/.cpp     # Luftfuktighetssensor (1% till 99%)
├── VelocitySensor.h/.cpp     # Hastighetssensor med 3D-positionering
└── Threshold.h/.cpp          # Larmhantering och tröskelövervakning

Storage.h/.cpp                # Central datahantering och analysmotor
├── Mätdatalagring
├── Periodisk läsning (bakgrundstråd)
├── Statistiska beräkningar
└── CSV-persistence (spara/ladda)

UserInterface.h/.cpp          # Menydriven användarinteraktion
├── 8 huvudfunktioner
├── Visualisering av data och larm
└── Filhantering

Measurement.h                 # Datastrukturer (Measurement, Statistics)
Point3D.h                     # 3D-koordinatsystem för hastighetsensorer
Utils.h/.cpp                  # Verktygsfunktioner (slumpgenerering, validering, konvertering)

README.md                     # Denna fil
```

---

## 🎯 Nyckelfunktioner

### 🔔 Larmsystem
- **Aktiva larm**: 6 av 12 sensorer har aktiv larmövervakning
- **Tröskeltyper**:
    - Temperatur/Luftfuktighet: Larm vid värde ÖVER tröskel
    - Hastighet: Larm vid värde UNDER tröskel (övervakar nedbromsning)
- **Larmhistorik**: Alla utlösta larm sparas med tidsstämpel och värde

### 📊 Tre Sensortyper

| Sensor | Antal | Namn | Mätområde | Tröskel | Aktiva Larm |
|--------|-------|------|-----------|---------|-------------|
| **Temperatur** | 4 | Thermostat 0-3 | -25°C till 60°C | 30-55°C (slumpmässig) | Index 0, 2 |
| **Luftfuktighet** | 4 | MoistSensor 0-3 | 1% till 99% | 10-75% (slumpmässig) | Index 4, 6 |
| **Hastighet** | 4 | Accelerometer 0-3 | 0.5-5.0 m/s | 10k-50k m (slumpmässig) | Index 8, 10 |

### ⚡ Periodisk Datainsamling
- Bakgrundstråd läser alla sensorer var 5:e sekund
- Automatisk larmkontroll vid varje avläsning
- Trådsäker datahantering

### 📈 Statistisk Analys
- Medelvärde, min/max-värden
- Standardavvikelse
- Filtrering per sensortyp
- Antal mätningar per typ

---

## ⚙️ Installation och körning

### Förutsättningar
- C++17 eller senare
- Kompilator som stödjer threads (g++/clang++)

### Klona repository:
```bash
git clone https://github.com/regrets123/STI_Tasks/tree/main/CppBasic
cd MultiSensorSystem/
```

### Kompilera:
```bash
g++ -std=c++17 -pthread main.cpp Storage.cpp UserInterface.cpp Utils.cpp \
    Sensors/Sensor.cpp Sensors/TemperatureSensor.cpp \
    Sensors/HumiditySensor.cpp Sensors/VelocitySensor.cpp \
    Sensors/Threshold.cpp -o sensor_system
```
---

## 🧭 Användning

### Huvudmeny
Programmet visar en interaktiv meny i terminalen:

```
========================================
       SENSOR MANAGEMENT SYSTEM
========================================
1. Read new measurements from all sensors
2. Show statistics per sensor
3. Show all measurements
4. Save all measurements to file
5. Load measurements from file
6. Show all Active Alarms
7. Show all Triggered Alarms
8. Exit program
========================================
Choose an option (1-8):
```

### Menyalternativ

**1. Läs nya mätningar**
- Läser omedelbart från alla 12 sensorer
- Visar värden med tidsstämpel
- För hastighetsensorer visas även 3D-position

**2. Visa statistik per sensortyp**
- Välj mellan Temperatur (1) eller Luftfuktighet (2)
- Visar: antal, medelvärde, min, max, standardavvikelse

**3. Visa alla mätningar**
- Tabellarisk vy av all insamlad data
- Sorterad med tidsstämpel
- Visar totalt antal mätningar

**4. Spara mätningar till fil**
- Exporterar data till CSV-format
- Bevarar all metadata inklusive positionsdata
- Filformat: `Time,Type,Value,MoreData,Name`

**5. Ladda mätningar från fil**
- Importerar tidigare sparad CSV-data
- Validerar och parsear automatiskt
- Hoppar över ogiltiga rader

**6. Visa aktiva larm**
- Listar alla sensorer med aktiverad larmövervakning
- Visar tröskelvärdena för varje larm

**7. Visa utlösta larm**
- Historik över alla larmutlösningar
- Tidsstämpel, sensornamn, värde och tröskel
- Indikerar om värdet var över eller under tröskeln

**8. Avsluta programmet**
- Stoppar bakgrundstråden säkert
- Stänger ner systemet korrekt

---

## 🧱 Tekniska val och arkitektur

### Designmönster

**1. Strategy Pattern**
- Abstrakt `Sensor`-basklass med `read()` virtuell metod
- Tre konkreta implementationer med olika läslogik
- Polymorfism för enhetlig behandling av olika sensortyper

**2. Repository Pattern**
- `Storage` fungerar som central datarepositorium
- Hanterar all CRUD-logik och persistence
- Kapslar in dataåtkomst från resten av systemet

**3. Observer Pattern**
- `Threshold`-objekt övervakar sensorvärden
- Sensorer notifierar `Storage` vid larmutlösning
- Löst kopplad kommunikation mellan komponenter

### Minneshantering

```cpp
// Sensorer: unique_ptr (exklusivt ägande)
std::vector<std::unique_ptr<Sensor>> sensors;

// Trösklar: shared_ptr (delat mellan sensor och storage)
std::vector<std::shared_ptr<Threshold>> thresholds;

// Mätdata: raw vectors via pekare till Storage
std::vector<Measurement> data;
```

### Trådhantering

**Bakgrundstråd för periodisk läsning:**
```cpp
storage.startPeriodicReading(std::chrono::seconds(5));
// ... användarinteraktion ...
storage.stopPeriodicReading();  // Säker avslutning
```

- Använder `std::thread` och `std::atomic<bool>` för trådkontroll
- `std::this_thread::sleep_for()` för icke-blockerande paus
- `.join()` säkerställer ren avslutning

### Separation of Concerns

| Komponent | Ansvar |
|-----------|--------|
| **main.cpp** | Initialisering, orkestrera systemstart/stopp |
| **Sensor** | Generera/läsa sensordata, larmkontroll |
| **Threshold** | Tröskellogik, larmaktivering |
| **Storage** | Datalagring, statistik, persistence, trådhållen läsning |
| **UserInterface** | Presentation, användarinput, navigation |
| **Utils** | Hjälpfunktioner (generisk funktionalitet) |

### Dataflöde

```
Sensorer → read() → Measurement objekt → Storage → CSV/Minne
                ↓
              Threshold → Check → Triggered Alarm → Storage
                                                        ↓
                                            UserInterface → Visa
```

---

## 📊 Detaljerad Funktionalitet

### Sensorklass-hierarki

**Sensor (abstrakt basklass)**
```cpp
virtual double read() const = 0;  // Måste implementeras
virtual Point3D getMoreData() const;  // Optionell extra data
```

**TemperatureSensor**
- Genererar slumpmässigt värde inom intervall
- Kontrollerar om värde > tröskel
- Rapporterar larm vid överskridning

**HumiditySensor**
- Samma logik som TemperatureSensor
- Annat mätintervall och enhet

**VelocitySensor**
- Beräknar tillryggalagd sträcka över tid
- Uppdaterar 3D-position baserat på riktningsvektor
- Larm vid värde < tröskel (övervakar stillastående/nedbromsning)
- Returnerar position via `getMoreData()`

### Storage-funktioner

**Statistikberäkning**
```cpp
Statistics calculateStatistics(const std::vector<Measurement>* data);
// Returnerar: size, average, minValue, maxValue, stdDev
```

**CSV-format**
```csv
Time,Type,Value,MoreData,Name
2025-01-15 14:30,Temperature,45.3,,Thermostat 0
2025-01-15 14:30,Velocity,1250.5, x:12.5; y:8.3; z:15.2,Accelerometer 0
```

### Threshold-logik

**Över-tröskel (Temperature/Humidity)**
```cpp
Threshold(celsius, "Thermostat 0", 45.0, false);
// Larm utlöses när: value > 45.0
```

**Under-tröskel (Velocity)**
```cpp
Threshold(velocity, "Accelerometer 0", 10000.0, true);
// Larm utlöses när: value < 10000.0
```

---

## 🔬 Testning

### Manuell testning genomförd:

✅ **Sensor-avläsning**
- Alla tre sensortyper genererar korrekta värden inom intervall
- Tidsstämplar sätts korrekt
- Hastighetsensorer uppdaterar position över tid

✅ **Larmfunktionalitet**
- Aktiva larm (index 0,2,4,6,8,10) övervakare värden
- Inaktiva larm (index 1,3,5,7,9,11) ignorerar trösklar
- Utlösta larm sparas med korrekt tidsstämpel

✅ **Periodisk läsning**
- Bakgrundstråd läser var 5:e sekund
- Ingen konflikt med användarinteraktion
- Säker avslutning vid programavslut

✅ **Datahantering**
- Spara till CSV → Ladda → Spara igen (dataintegrity bevarat)
- Felhantering vid ogiltig fil
- Korrekt parsing av alla fält inklusive 3D-positioner

✅ **Statistik**
- Korrekta beräkningar för medelvärde och standardavvikelse
- Filtrering per sensortyp fungerar
- Tom data hanteras säkert (returnerar nollvärden)

✅ **Användarinteraktion**
- Input-validering förhindrar ogiltiga val
- Tydliga felmeddelanden
- Menynavigation flyter smidigt

### Testscenario (exempel)

```bash
1. Starta program
2. Läs nya mätningar (alt 1) → Verifiera 12 sensorer läses
3. Visa aktiva larm (alt 6) → Verifiera 6 aktiva larm visas
4. Vänta 10+ sekunder → Bakgrundstråd samlar data
5. Visa alla mätningar (alt 3) → Verifiera periodisk data finns
6. Visa utlösta larm (alt 7) → Kontrollera om något larm utlösts
7. Spara till fil "test.csv" (alt 4)
8. Starta om program
9. Ladda "test.csv" (alt 5)
10. Visa alla mätningar (alt 3) → Verifiera data återställd
11. Avsluta (alt 8) → Kontrollera ren avslutning utan krasch
```

---

## 💡 Utmaningar och lärdomar

### Största utmaningar:

**1. Trådsynkronisering**
- **Problem**: Risk för race conditions när bakgrundstråd och UI-tråd åtkomst samma data
- **Lösning**: Använder `std::atomic<bool>` för running-flagga, minimal delad data under korta tidsperioder
- **Lärdom**: Behöver överväga `std::mutex` för framtida vidareutveckling med mer komplex tråddelning

**2. Minneshantering med shared_ptr**
- **Problem**: Trösklar måste delas mellan sensorer och Storage
- **Lösning**: `shared_ptr` för trösklar, `unique_ptr` för sensorer
- **Lärdom**: Viktigt att tänka på ägandeskap tidigt i designfasen

**3. Polymorfism med getMoreData()**
- **Problem**: Endast VelocitySensor har extra data (position), andra sensorer inte
- **Lösning**: Virtuell metod med default-implementation som returnerar (0,0,0)
- **Lärdom**: Ibland är optional-mönster bättre än att tvinga alla subklasser implementera något

### Framtida förbättringar:

**Kod-kvalitet:**
- [ ] Lägg till `std::mutex` för thread-safe åtkomst till mätdata
- [ ] Extrahera magic numbers till konstanter/config-fil

**Funktionalitet:**
- [ ] Konfigurerbar läsfrekvens (inte hårdkodad 5 sekunder)
- [ ] Möjlighet att aktivera/deaktivera larm under körning
- [ ] Grafisk visualisering av 3d vektorerna

**Arkitektur:**
- [ ] Dependency injection för lättare testning
- [ ] Event-system för larmnotifikationer


---

## 👤 Kontakt

**Utvecklare**: Lotus Saxe  
**E-post**: lotus.saxe@gmail.com  
**GitHub**: [regrets123](https://github.com/regrets123)

---

