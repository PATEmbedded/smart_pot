# Smart Pot System Architecture

## System Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                      SMART POT SYSTEM                           │
│                                                                  │
│  ┌────────────────┐         ┌──────────────────┐              │
│  │   SENSORS      │         │   CONTROLLER     │               │
│  │                │         │                  │               │
│  │ • Soil Moisture│────────▶│   Arduino Uno    │               │
│  │ • Light (LDR)  │────────▶│      or          │               │
│  │ • Temperature  │────────▶│     ESP32        │               │
│  │ • Humidity     │────────▶│                  │               │
│  └────────────────┘         └─────────┬────────┘               │
│                                        │                        │
│                                        │ Control Signal         │
│                                        ▼                        │
│                             ┌──────────────────┐               │
│                             │  RELAY MODULE    │               │
│                             └────────┬─────────┘               │
│                                      │                         │
│                                      │ Power                   │
│                                      ▼                         │
│                             ┌──────────────────┐               │
│                             │   WATER PUMP     │               │
│                             │   (Watering)     │               │
│                             └──────────────────┘               │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

## Data Flow

```
  1. Sensors Read          2. Data Processing       3. Decision Making
┌──────────────┐         ┌──────────────┐         ┌──────────────┐
│ Soil: 350    │────────▶│ Compare to   │────────▶│ Too Dry?     │
│ Light: 460   │         │ Thresholds   │         │ Yes/No       │
│ Temp: 22.5°C │         │              │         │              │
└──────────────┘         └──────────────┘         └──────┬───────┘
                                                          │
                                                          ▼
                                                   4. Action
                                              ┌──────────────┐
                                              │ Activate     │
                                              │ Water Pump   │
                                              │ for 2 sec    │
                                              └──────────────┘
```

## Control Loop

```
┌─────────────────────────────────────────────────────────────┐
│                    Main Control Loop                        │
│                   (Every 60 seconds)                        │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
          ┌─────────────────────────┐
          │  Read All Sensors       │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Display Readings       │
          │  (Serial Monitor)       │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Check Conditions       │
          │  • Moisture Level       │
          │  • Light Range          │
          │  • Temperature Range    │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Needs Attention?       │
          │  • LED Indicator ON     │
          │  • Alert Messages       │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Needs Watering?        │
          │  • Check Soil Level     │
          │  • Check Cooldown       │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Water if Needed        │
          │  • Activate Pump        │
          │  • Update Last Water    │
          └────────┬────────────────┘
                   │
                   ▼
          ┌─────────────────────────┐
          │  Wait for Next Cycle    │
          └─────────────────────────┘
```

## Configuration System

```
┌────────────────────────────────────────────────────────────┐
│               PlantCareConfig Structure                    │
├────────────────────────────────────────────────────────────┤
│                                                            │
│  soilMoistureThreshold    ─── Trigger point for watering  │
│  optimalLightMin          ─── Minimum acceptable light    │
│  optimalLightMax          ─── Maximum acceptable light    │
│  optimalTempMin           ─── Minimum acceptable temp     │
│  optimalTempMax           ─── Maximum acceptable temp     │
│  wateringDuration         ─── How long to run pump (ms)   │
│  checkInterval            ─── Sensor reading frequency    │
│  minWateringInterval      ─── Cooldown between waterings  │
│                                                            │
└────────────────────────────────────────────────────────────┘
           │                                   │
           ▼                                   ▼
   ┌──────────────┐                   ┌──────────────┐
   │  Default     │                   │  Customized  │
   │  Houseplant  │                   │  Per Plant   │
   │  Profile     │                   │  Type        │
   └──────────────┘                   └──────────────┘
```

## Communication Interface

```
┌─────────────────────────────────────────────────────────┐
│              Serial Communication (9600 baud)           │
└────────────────────┬────────────────────────────────────┘
                     │
        ┌────────────┼────────────┐
        │            │            │
        ▼            ▼            ▼
   ┌────────┐   ┌────────┐   ┌────────┐
   │ Status │   │ Config │   │ Alerts │
   │ Output │   │Commands│   │ & Logs │
   └────────┘   └────────┘   └────────┘
        │            │            │
        ▼            ▼            ▼
   Sensor       Update         Condition
   Readings     Settings       Warnings
```

## Power Management

```
┌────────────────────────────────────────┐
│      5V Power Supply (2A)              │
└──────────┬─────────────────────────────┘
           │
    ┌──────┴──────┐
    │             │
    ▼             ▼
┌────────┐   ┌──────────┐
│Arduino │   │  Water   │
│ + All  │   │  Pump    │
│Sensors │   │(via Relay)│
└────────┘   └──────────┘
 (~300mA)      (~500mA)

Total: ~800mA peak
Recommended: 2A supply
```

## Safety Features

```
┌─────────────────────────────────────────────────────────┐
│                   Safety Mechanisms                     │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  1. Watering Cooldown      ─── Prevents over-watering  │
│     • Minimum 1 hour between waterings                  │
│     • Configurable interval                             │
│                                                         │
│  2. Relay Isolation        ─── Protects Arduino        │
│     • Optocoupler isolated                              │
│     • Separate power for pump                           │
│                                                         │
│  3. Sensor Validation      ─── Handles failures        │
│     • Checks for NaN values                             │
│     • Warning messages                                  │
│                                                         │
│  4. Status LED             ─── Visual feedback         │
│     • Indicates attention needed                        │
│     • Watering in progress                              │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

## Plant Care Profiles

```
┌──────────────┬──────────────┬──────────────┬──────────────┐
│  Succulents  │   Tropical   │    Herbs     │    Ferns     │
├──────────────┼──────────────┼──────────────┼──────────────┤
│ Very Dry     │ Moderately   │ Keep Moist   │ Very Moist   │
│ High Light   │ Low-Med Light│ High Light   │ Low Light    │
│ 15-30°C      │ 18-28°C      │ 16-24°C      │ 15-24°C      │
│ Water: 1 sec │ Water: 2.5sec│ Water: 2 sec │ Water: 3 sec │
│ Every 2hr    │ Every 1hr    │ Every 30min  │ Every 45min  │
└──────────────┴──────────────┴──────────────┴──────────────┘
```

## Pin Mapping Summary

```
Arduino          Component              Function
───────────────────────────────────────────────────────
A0               Soil Moisture          Analog Read
A1               LDR (Light)            Analog Read
D2               DHT Sensor             Digital I/O
D3               Relay                  Digital Out
D4               Status LED             Digital Out
5V               All Components         Power Supply
GND              All Components         Ground
```

## Expandability

The system can be extended with:

```
┌─────────────────────────────────────────────────────────┐
│              Optional Enhancements                      │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  • LCD Display (I2C)       ─── Show readings on screen │
│  • WiFi Module (ESP32)     ─── Remote monitoring       │
│  • SD Card Logger          ─── Data logging            │
│  • Multiple Pumps          ─── Multiple plants         │
│  • pH Sensor               ─── Soil chemistry          │
│  • Nutrient Dispenser      ─── Automatic feeding       │
│  • Mobile App              ─── Smartphone control      │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

## File Organization

```
smart_pot/
│
├── smart_pot.ino           # Main Arduino sketch (297 lines)
│   ├── Sensor reading functions
│   ├── Watering control logic
│   ├── Serial communication
│   └── Configuration management
│
├── README.md               # User guide (266 lines)
│   ├── Quick start
│   ├── Usage instructions
│   └── Troubleshooting
│
├── circuit_diagram.md      # Hardware setup (230 lines)
│   ├── Component list
│   ├── Wiring diagrams
│   └── Assembly instructions
│
├── plant_profiles.md       # Care configs (138 lines)
│   ├── Pre-configured profiles
│   └── Parameter guidelines
│
├── libraries.md            # Dependencies (204 lines)
│   ├── Installation guide
│   └── Version compatibility
│
└── architecture.md         # This file
    └── System overview
```
