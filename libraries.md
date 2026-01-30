# Required Libraries

This document lists all the libraries required for the Smart Pot project and how to install them.

## Installation Methods

### Method 1: Arduino IDE Library Manager (Recommended)
1. Open Arduino IDE
2. Go to `Sketch` → `Include Library` → `Manage Libraries...`
3. Search for the library name
4. Click "Install"

### Method 2: Manual Installation
1. Download the library ZIP file from GitHub
2. Go to `Sketch` → `Include Library` → `Add .ZIP Library...`
3. Select the downloaded ZIP file

## Required Libraries

### 1. DHT Sensor Library
**Purpose**: Read temperature and humidity from DHT11/DHT22 sensors

**Library Name**: `DHT sensor library` by Adafruit

**Version**: Latest stable version (1.4.4 or later)

**Installation via Library Manager**:
- Search: "DHT sensor library"
- Author: Adafruit
- Click Install

**Manual Installation**:
- GitHub: https://github.com/adafruit/DHT-sensor-library
- Download ZIP and add via Arduino IDE

**Dependencies**: This library requires the Adafruit Unified Sensor library (see below)

### 2. Adafruit Unified Sensor
**Purpose**: Dependency for DHT sensor library

**Library Name**: `Adafruit Unified Sensor`

**Version**: Latest stable version (1.1.9 or later)

**Installation via Library Manager**:
- Search: "Adafruit Unified Sensor"
- Author: Adafruit
- Click Install

**Manual Installation**:
- GitHub: https://github.com/adafruit/Adafruit_Sensor
- Download ZIP and add via Arduino IDE

## Optional Libraries

### 1. EEPROM (Built-in)
**Purpose**: Save plant care configuration permanently

**Note**: Built-in library, no installation required

**Usage**: To persist configuration across reboots
```cpp
#include <EEPROM.h>
```

### 2. Wire (Built-in)
**Purpose**: I2C communication for additional sensors (LCD display, etc.)

**Note**: Built-in library, no installation required

### 3. LiquidCrystal_I2C
**Purpose**: Display sensor readings on LCD screen (optional enhancement)

**Library Name**: `LiquidCrystal I2C`

**Installation via Library Manager**:
- Search: "LiquidCrystal I2C"
- Author: Frank de Brabander
- Click Install (optional)

## Library Verification

After installing the libraries, verify the installation:

1. Open Arduino IDE
2. Go to `File` → `Examples` → `DHT sensor library` → `DHTtester`
3. If you see the example, libraries are installed correctly

## Installation Step-by-Step Guide

### Complete Installation Process:

1. **Open Arduino IDE**
   - Launch the Arduino IDE application
   - Ensure you have version 1.8.0 or later

2. **Open Library Manager**
   - Click `Sketch` in the menu bar
   - Select `Include Library`
   - Click `Manage Libraries...`
   - Wait for the library index to update

3. **Install Adafruit Unified Sensor**
   - Type "Adafruit Unified Sensor" in the search box
   - Find the library by Adafruit
   - Click the Install button
   - Wait for installation to complete

4. **Install DHT Sensor Library**
   - Type "DHT sensor library" in the search box
   - Find "DHT sensor library by Adafruit"
   - Click the Install button
   - If prompted to install dependencies, click "Install all"
   - Wait for installation to complete

5. **Verify Installation**
   - Go to `Sketch` → `Include Library`
   - Scroll down and verify you see:
     - DHT sensor library
     - Adafruit Unified Sensor
   
6. **Close Library Manager**
   - Click the Close button
   - You're ready to compile the Smart Pot code!

## Board Selection

Ensure you have the correct board selected:

### For Arduino Uno:
- `Tools` → `Board` → `Arduino AVR Boards` → `Arduino Uno`

### For Arduino Nano:
- `Tools` → `Board` → `Arduino AVR Boards` → `Arduino Nano`
- `Tools` → `Processor` → Select your processor (ATmega328P or ATmega328P Old Bootloader)

### For ESP32:
- Install ESP32 board support first:
  - `File` → `Preferences`
  - Add to "Additional Board Manager URLs": 
    `https://dl.espressif.com/dl/package_esp32_index.json`
  - `Tools` → `Board` → `Boards Manager`
  - Search "ESP32" and install
- Select: `Tools` → `Board` → `ESP32 Arduino` → Your ESP32 board model

## Common Library Issues

### Issue: "DHT.h: No such file or directory"
**Solution**: DHT library not installed correctly
- Reinstall DHT sensor library via Library Manager
- Ensure Adafruit Unified Sensor is also installed
- Restart Arduino IDE

### Issue: "Adafruit_Sensor.h: No such file or directory"
**Solution**: Missing dependency
- Install Adafruit Unified Sensor library
- Restart Arduino IDE

### Issue: Library version conflicts
**Solution**: Update to latest versions
- Open Library Manager
- Update all Adafruit libraries to latest versions

### Issue: Compilation errors with ESP32
**Solution**: Check ESP32 board support
- Ensure ESP32 boards are installed via Boards Manager
- Update ESP32 board support to latest version
- Some pin definitions might need adjustment for ESP32

## Library Documentation

### DHT Sensor Library Documentation
- Official Guide: https://learn.adafruit.com/dht
- API Reference: Available in library examples
- Sensor Datasheet: DHT11 and DHT22 datasheets available online

### Key Functions:
```cpp
dht.begin();                    // Initialize sensor
float temp = dht.readTemperature();  // Read temperature in °C
float temp_f = dht.readTemperature(true); // Read temperature in °F
float humidity = dht.readHumidity();      // Read humidity %
```

## Version Compatibility

The Smart Pot code is compatible with:
- Arduino IDE 1.8.0 or later (including 2.x versions)
- DHT sensor library (latest stable version recommended)
- Adafruit Unified Sensor (latest stable version recommended)

Tested on:
- Arduino Uno (ATmega328P)
- Arduino Nano (ATmega328P)
- ESP32 DevKit V1 (with pin adjustments)

## Updates and Maintenance

Check for library updates periodically:
1. Open Library Manager
2. Look for libraries with "Update" button
3. Click Update to get latest versions

Keep libraries updated for bug fixes and new features.
