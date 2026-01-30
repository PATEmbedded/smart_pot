# Smart Pot 🌱

The Smart Pot is a compact, intelligent planter that maintains and waters your plants automatically according to a personalized care schedule. With smart sensors monitoring soil moisture, light, and temperature, your plants will always thrive!

## Features

- **🌡️ Temperature Monitoring**: Real-time temperature tracking with DHT11/DHT22 sensor
- **💧 Soil Moisture Sensing**: Automatic detection of soil dryness
- **☀️ Light Level Monitoring**: Tracks ambient light conditions
- **🚰 Automatic Watering**: Waters plants when soil moisture drops below threshold
- **⚙️ Personalized Care Schedules**: Configurable settings for different plant types
- **📊 Real-time Monitoring**: Serial output for all sensor readings
- **🔔 Smart Alerts**: Status LED and warnings for suboptimal conditions
- **⏱️ Watering Cooldown**: Prevents over-watering with configurable intervals

## Hardware Requirements

### Components Needed:
- Arduino Uno/Nano or ESP32 (1x)
- Capacitive Soil Moisture Sensor (1x)
- Photoresistor/LDR with 10kΩ resistor (1x)
- DHT11 or DHT22 Temperature & Humidity Sensor (1x)
- 5V Relay Module (1x)
- 5V Water Pump - submersible mini pump (1x)
- LED with 220Ω resistor for status indicator (1x)
- Jumper wires
- Breadboard (optional for prototyping)
- Water container/reservoir
- Tubing for water pump
- USB cable for programming
- 5V 2A power supply

See [circuit_diagram.md](circuit_diagram.md) for detailed wiring instructions.

## Software Requirements

### Arduino IDE Setup:
1. Download and install [Arduino IDE](https://www.arduino.cc/en/software) (v1.8.0 or later)
2. Install required libraries via Library Manager:
   - DHT sensor library by Adafruit
   - Adafruit Unified Sensor

See [libraries.md](libraries.md) for detailed installation instructions.

## Quick Start Guide

### 1. Hardware Assembly
1. Follow the circuit diagram in [circuit_diagram.md](circuit_diagram.md)
2. Connect all sensors to the Arduino:
   - Soil moisture sensor → A0
   - Light sensor (LDR) → A1
   - DHT sensor → D2
   - Relay module → D3
   - Status LED → D4
3. Connect the water pump to the relay module
4. Ensure proper power supply connections

### 2. Software Installation
1. Clone or download this repository
2. Open `smart_pot.ino` in Arduino IDE
3. Install required libraries (see [libraries.md](libraries.md))
4. Select your Arduino board: `Tools` → `Board` → `Arduino Uno` (or your board)
5. Select the correct COM port: `Tools` → `Port`
6. Click the Upload button (→)

### 3. Configuration
1. Choose a plant profile from [plant_profiles.md](plant_profiles.md)
2. Copy the configuration values into `smart_pot.ino`
3. Re-upload the sketch to Arduino
4. Open Serial Monitor (`Tools` → `Serial Monitor`) at 9600 baud

### 4. Calibration
1. Test the soil moisture sensor:
   - In air: Should read ~1000+
   - In water: Should read ~200-300
2. Adjust `soilMoistureThreshold` based on your readings
3. Test the water pump with a small watering duration first
4. Monitor the system for 24 hours and adjust as needed

## Plant Care Profiles

Pre-configured profiles are available for:
- 🌵 Succulents & Cacti
- 🌿 Tropical Plants (Pothos, Monstera)
- 🌾 Herbs (Basil, Mint, Parsley)
- 🍃 Ferns
- 🌺 Flowering Plants (Orchids)
- 🪴 Default Houseplants

See [plant_profiles.md](plant_profiles.md) for complete configuration details.

## Usage

### Monitoring Your Plant

Once running, the Smart Pot will:
1. Check sensors every minute (configurable)
2. Display readings via Serial Monitor:
   ```
   === Sensor Readings ===
   Soil Moisture: 65% (350)
   Light Level: 45% (460)
   Temperature: 22.5 °C
   Humidity: 55 %
   =====================
   ```
3. Alert you if conditions are suboptimal
4. Automatically water when soil is too dry

### Status LED Indicators
- **Steady On**: Plant needs attention (low moisture, low/high light, high/low temp)
- **Off**: All conditions are optimal
- **On During Watering**: Water pump is active (LED turns on during watering)
- **3 Blinks at Startup**: System initialized successfully

### Serial Commands

Send commands via Serial Monitor (9600 baud):

```
MOISTURE:400     - Set moisture threshold to 400
LIGHT_MIN:200    - Set minimum light level to 200
LIGHT_MAX:700    - Set maximum light level to 700
TEMP_MIN:18.0    - Set minimum temperature to 18°C
TEMP_MAX:26.0    - Set maximum temperature to 26°C
STATUS           - Display current configuration
```

## Understanding Sensor Readings

### Soil Moisture
- **0-300**: Very wet (may cause root rot)
- **300-500**: Moist (ideal for most plants)
- **500-700**: Slightly dry
- **700-1023**: Very dry (needs watering)

### Light Level
- **0-200**: Low light (shade)
- **200-600**: Medium light (indirect sunlight)
- **600-1023**: High light (direct sunlight)

### Temperature
- Displayed in Celsius
- Most houseplants prefer 18-26°C
- Alerts trigger if outside optimal range

## Troubleshooting

### Water Pump Not Running
- Check relay connections
- Verify pump power supply
- Check if watering cooldown is active
- Test relay independently

### Sensor Readings Seem Wrong
- **Soil Moisture**: Calibrate in air vs. water
- **Light Sensor**: Check LDR voltage divider circuit
- **Temperature**: Verify DHT sensor connections and pull-up resistor

### System Keeps Watering
- Increase `minWateringInterval`
- Check if soil moisture sensor is working
- Verify sensor is properly inserted in soil

### DHT Sensor Returns NaN
- Check wiring (VCC, GND, DATA)
- Verify 10kΩ pull-up resistor
- Try power cycling the system

See [circuit_diagram.md](circuit_diagram.md) for more troubleshooting tips.

## Customization

### Adjusting for Your Plant
1. Research your plant's specific needs
2. Modify the `PlantCareConfig` struct in the code:
   ```cpp
   PlantCareConfig config = {
     300,        // Soil moisture threshold
     200,        // Optimal light minimum
     700,        // Optimal light maximum
     18.0,       // Optimal temp minimum (°C)
     26.0,       // Optimal temp maximum (°C)
     2000,       // Watering duration (ms)
     60000,      // Check interval (ms)
     3600000     // Min watering interval (ms)
   };
   ```
3. Upload and test

### Adding Features
The modular code makes it easy to add:
- LCD display for readings
- WiFi connectivity (with ESP32)
- Mobile app integration
- Data logging to SD card
- Multiple plant support
- Email/SMS notifications

## Safety and Maintenance

### Safety Tips
- Keep electronics in waterproof enclosure
- Never run water pump without water
- Use proper wire gauge for power
- Add fuse protection
- Regularly check for water leaks

### Maintenance
- Clean soil moisture sensor monthly
- Check water reservoir level
- Inspect tubing for clogs
- Verify all connections quarterly
- Update calibration if sensor readings drift

## Project Structure

```
smart_pot/
├── smart_pot.ino           # Main Arduino sketch
├── plant_profiles.md       # Pre-configured plant care settings
├── circuit_diagram.md      # Hardware wiring guide
├── libraries.md            # Library installation guide
├── README.md               # This file
└── LICENSE                 # Project license
```

## Technical Specifications

- **Operating Voltage**: 5V DC
- **Power Consumption**: ~300mA (idle), ~800mA (pump active)
- **Sensor Update Rate**: Configurable (default: 60 seconds)
- **Watering Precision**: ±100ms
- **Temperature Range**: 0-50°C (DHT11) or -40-80°C (DHT22)
- **Humidity Range**: 20-90% RH
- **Soil Moisture Range**: 0-100% (calibrated)

## Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest features
- Submit pull requests
- Share your plant care profiles

## License

This project is open source. See [LICENSE](LICENSE) file for details.

## Support

For questions or issues:
- Open an issue on GitHub
- Check the troubleshooting section
- Review the documentation files

## Acknowledgments

Built with:
- Arduino platform
- Adafruit DHT sensor library
- Open-source community contributions

---

**Happy Growing! 🌱** Keep your plants healthy with Smart Pot automation!
