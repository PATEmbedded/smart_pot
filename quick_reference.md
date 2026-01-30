# Smart Pot Quick Reference

## Quick Start (5 Minutes)

1. **Wire the components** (see circuit_diagram.md)
2. **Install libraries**: DHT sensor library + Adafruit Unified Sensor
3. **Upload smart_pot.ino** to Arduino
4. **Open Serial Monitor** at 9600 baud
5. **Watch your plant thrive!** 🌱

## Pin Connections

| Arduino Pin | Component |
|------------|-----------|
| A0 | Soil Moisture Sensor |
| A1 | Light Sensor (LDR) |
| D2 | DHT Temperature Sensor |
| D3 | Water Pump Relay |
| D4 | Status LED |

## Serial Commands

Send these via Serial Monitor (9600 baud):

```
MOISTURE:400      - Set soil moisture threshold
LIGHT_MIN:200     - Set minimum light level
LIGHT_MAX:700     - Set maximum light level  
TEMP_MIN:18.0     - Set minimum temperature (°C)
TEMP_MAX:26.0     - Set maximum temperature (°C)
STATUS            - Show current configuration
```

## LED Indicators

| Pattern | Meaning |
|---------|---------|
| 3 quick blinks | System started successfully |
| Steady ON | Plant needs attention |
| OFF | All conditions optimal |
| ON during activity | Watering in progress |

## Common Plant Profiles

### Succulents 🌵
```cpp
PlantCareConfig config = {
  600,    // Very dry soil preferred
  400,    // High light needed
  900,    // Maximum light
  15.0,   // Min temp
  30.0,   // Max temp
  1000,   // Short watering (1 sec)
  120000, // Check every 2 min
  7200000 // Water every 2 hours max
};
```

### Tropical Plants 🌿
```cpp
PlantCareConfig config = {
  400,    // Moderately moist
  150,    // Low-medium light
  600,    // Max light
  18.0,   // Min temp
  28.0,   // Max temp
  2500,   // Normal watering (2.5 sec)
  60000,  // Check every 1 min
  3600000 // Water every 1 hour max
};
```

### Herbs 🌾
```cpp
PlantCareConfig config = {
  250,    // Keep moist
  300,    // High light
  800,    // Max light
  16.0,   // Min temp
  24.0,   // Max temp
  2000,   // Normal watering (2 sec)
  45000,  // Check every 45 sec
  1800000 // Water every 30 min max
};
```

### Ferns 🍃
```cpp
PlantCareConfig config = {
  200,    // Very moist
  100,    // Low light
  500,    // Max light
  15.0,   // Min temp
  24.0,   // Max temp
  3000,   // Longer watering (3 sec)
  60000,  // Check every 1 min
  2700000 // Water every 45 min max
};
```

## Understanding Sensor Values

### Soil Moisture (0-1023)
- **0-300**: Very wet 💦
- **300-500**: Moist (ideal) ✅
- **500-700**: Slightly dry
- **700-1023**: Very dry (needs water) 🚰

### Light Level (0-1023)
- **0-200**: Low light (shade) 🌙
- **200-600**: Medium light ☁️
- **600-1023**: High light (sunny) ☀️

### Temperature
- Displayed in Celsius (°C)
- Most houseplants: 18-26°C
- Alerts if outside optimal range

## Troubleshooting Quick Fixes

| Problem | Quick Fix |
|---------|-----------|
| Pump won't run | Check relay wiring, verify power supply |
| DHT reads NaN | Check pull-up resistor, verify connections |
| Over-watering | Increase minWateringInterval |
| Under-watering | Decrease soilMoistureThreshold |
| False alerts | Calibrate sensor thresholds for your environment |

## Configuration Parameters Explained

| Parameter | What It Does | Typical Value |
|-----------|--------------|---------------|
| soilMoistureThreshold | Trigger for watering | 300 (moderate) |
| optimalLightMin | Minimum good light | 200 |
| optimalLightMax | Maximum good light | 700 |
| optimalTempMin | Minimum good temp | 18.0°C |
| optimalTempMax | Maximum good temp | 26.0°C |
| wateringDuration | Pump run time | 2000ms (2 sec) |
| checkInterval | Sensor read frequency | 60000ms (1 min) |
| minWateringInterval | Watering cooldown | 3600000ms (1 hr) |

## Safety Checklist

- [ ] Electronics in waterproof enclosure
- [ ] Pump never runs dry (always submerged)
- [ ] Power supply rated for total current (2A minimum)
- [ ] All connections secure and insulated
- [ ] Water reservoir has adequate capacity
- [ ] Regular inspection for leaks

## Example Serial Output

```
Smart Pot Initializing...
Smart Pot Ready!
Monitoring: Soil Moisture | Light | Temperature
----------------------------------------------

=== Sensor Readings ===
Soil Moisture: 65% (raw: 350)
Light Level: 45% (raw: 460)
Temperature: 22.5 °C
Humidity: 55 %
=====================

💧 Starting automatic watering...
💧 Watering complete!
Next watering available in: 60 minutes
```

## Calibration Steps

1. **Soil Moisture**:
   - Read value in air (should be ~1000)
   - Read value in water (should be ~200-300)
   - Set threshold between these values

2. **Light Sensor**:
   - Read in darkness (should be ~0-50)
   - Read in bright light (should be ~800-1023)
   - Set min/max based on plant needs

3. **Watering Duration**:
   - Start with 1000ms (1 second)
   - Measure water delivered
   - Adjust duration to deliver desired amount

## Power Requirements

| Component | Current Draw |
|-----------|--------------|
| Arduino Uno | ~50mA |
| Sensors (all) | ~50mA |
| Relay Module | ~20mA |
| Water Pump | ~400-600mA |
| Status LED | ~20mA |
| **Total Peak** | **~800mA** |

**Recommended**: 5V 2A power supply

## Timing Reference

| Duration | Milliseconds | Usage |
|----------|--------------|-------|
| 1 second | 1000 | Pump duration |
| 1 minute | 60000 | Check interval |
| 30 minutes | 1800000 | Watering cooldown |
| 1 hour | 3600000 | Watering cooldown |
| 2 hours | 7200000 | Watering cooldown |

## Resources

- **Full Documentation**: README.md
- **Wiring Guide**: circuit_diagram.md
- **Plant Profiles**: plant_profiles.md
- **Library Setup**: libraries.md
- **System Design**: architecture.md

## Emergency Stop

If something goes wrong:
1. Unplug power immediately
2. Disconnect water pump
3. Check all connections
4. Review circuit_diagram.md
5. Test components individually

## Support

- Check README.md troubleshooting section
- Review circuit connections
- Verify sensor calibration
- Test components individually
- Open GitHub issue if needed

---

**Remember**: Start with conservative settings and adjust based on your plant's response!
