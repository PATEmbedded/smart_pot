# Smart Pot Circuit Diagram

## Components Required

### Main Controller
- Arduino Uno/Nano or ESP32 (1x)
- USB cable for programming
- Power supply (5V, 2A recommended)

### Sensors
- Capacitive Soil Moisture Sensor (1x)
  - Analog output
  - Operating voltage: 3.3-5V
- Photoresistor/LDR (Light Dependent Resistor) (1x)
  - 10kΩ resistor for voltage divider
- DHT11 or DHT22 Temperature & Humidity Sensor (1x)
  - 10kΩ pull-up resistor (usually included)

### Actuators
- 5V Water Pump (submersible mini pump) (1x)
  - Operating voltage: 3-6V DC
  - Flow rate: 80-120 L/H
- 5V Relay Module (1x)
  - Single channel relay
  - Optocoupler isolation
  - Control voltage: 5V

### Additional Components
- LED (5mm) with 220Ω resistor (1x) - Status indicator
- Jumper wires (male-to-male, male-to-female)
- Breadboard (optional, for prototyping)
- Water container/reservoir
- Tubing for water pump

## Pin Connections

### Arduino Uno/Nano

```
Arduino Pin  →  Component
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
A0           →  Soil Moisture Sensor (AOUT)
A1           →  LDR (through voltage divider)
D2           →  DHT Sensor (DATA)
D3           →  Relay Module (IN)
D4           →  LED (anode, through 220Ω resistor)

5V           →  Soil Moisture Sensor (VCC)
5V           →  DHT Sensor (VCC)
5V           →  LDR voltage divider (top)
5V           →  Relay Module (VCC)

GND          →  Soil Moisture Sensor (GND)
GND          →  DHT Sensor (GND)
GND          →  LDR voltage divider (bottom)
GND          →  Relay Module (GND)
GND          →  LED (cathode)
```

### LDR Voltage Divider Circuit

```
5V
 |
[LDR]
 |
 +---→ A1 (Arduino)
 |
[10kΩ]
 |
GND
```

### Relay and Water Pump Connection

```
Arduino D3 → Relay IN
5V         → Relay VCC
GND        → Relay GND

Relay COM  → Pump (+)
Relay NO   → 5V Power Supply (+)
GND        → Pump (-)
```

## Complete Circuit Diagram

```
                            ┌─────────────────────┐
                            │   Arduino Uno       │
                            │                     │
┌─────────────┐            │                     │         ┌─────────────┐
│ Soil        │            │ A0                  │         │   Status    │
│ Moisture    │────AOUT───→│                     │    D4───│   LED       │
│ Sensor      │            │ A1                  │         │   (220Ω)    │
└─────────────┘            │                     │         └─────────────┘
     │  │                  │                     │
    VCC GND                │ D2              D3  │         ┌─────────────┐
     │  │                  │  │               │  │         │   Relay     │
     │  │         ┌────────┴──┘               └──┴────────→│   Module    │
     │  │         │                                │        └──────┬──────┘
     │  │    ┌────┴────┐                          │               │
     │  │    │  DHT11/ │                          │               │ NO
     │  │    │  DHT22  │                          │               ▼
     │  │    └─────────┘                          │          ┌─────────┐
     │  │         │                                │          │  Water  │
     │  │        VCC                               │          │  Pump   │
     │  │         │                                │          └─────────┘
     │  │         │                                │               │
┌────┴──┴─────────┴────────────────────────────────┴───────────────┴────┐
│                          Common 5V Power Rail                          │
└────────────────────────────────────────────────────────────────────────┘
     │
┌────┴────────────────────────────────────────────────────────────────────┐
│                          Common Ground (GND)                             │
└──────────────────────────────────────────────────────────────────────────┘
```

## Assembly Instructions

### Step 1: Prepare the Breadboard (Optional)
If using a breadboard for prototyping:
1. Place Arduino on one side of breadboard
2. Reserve power rails for 5V and GND connections

### Step 2: Connect the Sensors

**Soil Moisture Sensor:**
1. Connect VCC to Arduino 5V
2. Connect GND to Arduino GND
3. Connect AOUT to Arduino A0

**Light Sensor (LDR):**
1. Connect one leg of LDR to Arduino 5V
2. Connect other leg to:
   - Arduino A1 (signal)
   - One leg of 10kΩ resistor
3. Connect other leg of 10kΩ resistor to Arduino GND

**Temperature Sensor (DHT11/DHT22):**
1. Connect VCC (pin 1) to Arduino 5V
2. Connect DATA (pin 2) to Arduino D2
3. Connect GND (pin 4) to Arduino GND
4. Add 10kΩ pull-up resistor between VCC and DATA (if not included on module)

### Step 3: Connect the Relay Module
1. Connect VCC to Arduino 5V
2. Connect GND to Arduino GND
3. Connect IN to Arduino D3

### Step 4: Connect the Water Pump
1. Connect pump positive wire to Relay COM
2. Connect external 5V power supply positive to Relay NO (Normally Open)
3. Connect pump negative wire to power supply GND
4. Ensure Arduino GND and power supply GND are connected

### Step 5: Add Status LED
1. Connect LED anode (longer leg) to 220Ω resistor
2. Connect resistor to Arduino D4
3. Connect LED cathode (shorter leg) to Arduino GND

### Step 6: Power Supply
- For prototyping: Power Arduino via USB
- For deployment: Use 5V 2A wall adapter with barrel jack
- Note: Water pump may require separate power supply if total current exceeds USB limit (500mA)

## Safety Considerations

1. **Water Protection**: Keep electronics away from water
   - Use waterproof enclosure for Arduino
   - Mount sensors above water level
   - Seal cable entry points

2. **Power Safety**: 
   - Never exceed voltage ratings
   - Use proper polarity
   - Add fuse protection on power supply

3. **Pump Safety**:
   - Ensure pump is submersible if used underwater
   - Never run pump dry (without water)
   - Check for water leaks regularly

4. **Electrical Isolation**:
   - Use relay to isolate Arduino from pump
   - Don't power pump directly from Arduino pins

## Testing Before Assembly

1. **Test each sensor individually**:
   - Soil moisture: Read values in air vs. water
   - Light sensor: Cover and expose to light
   - DHT sensor: Check temperature reading

2. **Test relay**:
   - Upload test sketch to toggle relay
   - Verify clicking sound
   - Use multimeter to check NO/NC switching

3. **Test pump**:
   - Power separately before connecting to system
   - Check for proper water flow
   - Verify polarity if pump has direction

## Troubleshooting

**Soil moisture sensor always reads max:**
- Check if sensor is in correct orientation
- Verify analog pin connection
- Try different analog pin

**DHT sensor returns NaN:**
- Check pull-up resistor
- Verify pin connection
- Try power cycling

**Relay not clicking:**
- Check 5V power supply
- Verify control pin connection
- Test with multimeter

**Pump not running:**
- Check relay NO connection
- Verify pump power supply
- Test pump independently

**System resets when pump activates:**
- Power supply insufficient
- Use separate power supply for pump
- Add capacitor (100µF) across power rails
