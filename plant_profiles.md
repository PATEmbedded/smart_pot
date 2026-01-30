# Plant Care Profiles

This file contains pre-configured care profiles for different types of plants. 
Copy the appropriate configuration into your smart_pot.ino file.

## Succulent / Cactus
```cpp
PlantCareConfig config = {
  600,              // Soil moisture threshold (very dry)
  400,              // Optimal light minimum (high light)
  900,              // Optimal light maximum
  15.0,             // Optimal temp minimum (°C)
  30.0,             // Optimal temp maximum (°C)
  1000,             // Watering duration (1 second - less water)
  120000,           // Check interval (2 minutes)
  7200000           // Min watering interval (2 hours)
};
```

## Tropical Plants (Pothos, Monstera, Philodendron)
```cpp
PlantCareConfig config = {
  400,              // Soil moisture threshold (moderately moist)
  150,              // Optimal light minimum (low to medium light)
  600,              // Optimal light maximum
  18.0,             // Optimal temp minimum (°C)
  28.0,             // Optimal temp maximum (°C)
  2500,             // Watering duration (2.5 seconds)
  60000,            // Check interval (1 minute)
  3600000           // Min watering interval (1 hour)
};
```

## Herbs (Basil, Mint, Parsley)
```cpp
PlantCareConfig config = {
  250,              // Soil moisture threshold (keep moist)
  300,              // Optimal light minimum (high light)
  800,              // Optimal light maximum
  16.0,             // Optimal temp minimum (°C)
  24.0,             // Optimal temp maximum (°C)
  2000,             // Watering duration (2 seconds)
  45000,            // Check interval (45 seconds)
  1800000           // Min watering interval (30 minutes)
};
```

## Ferns
```cpp
PlantCareConfig config = {
  200,              // Soil moisture threshold (very moist)
  100,              // Optimal light minimum (low light)
  500,              // Optimal light maximum
  15.0,             // Optimal temp minimum (°C)
  24.0,             // Optimal temp maximum (°C)
  3000,             // Watering duration (3 seconds - more water)
  60000,            // Check interval (1 minute)
  2700000           // Min watering interval (45 minutes)
};
```

## Flowering Plants (Orchids, African Violets)
```cpp
PlantCareConfig config = {
  350,              // Soil moisture threshold (moderately moist)
  200,              // Optimal light minimum (medium light)
  700,              // Optimal light maximum
  18.0,             // Optimal temp minimum (°C)
  27.0,             // Optimal temp maximum (°C)
  2000,             // Watering duration (2 seconds)
  60000,            // Check interval (1 minute)
  3600000           // Min watering interval (1 hour)
};
```

## Default Houseplants (Spider Plant, Snake Plant)
```cpp
PlantCareConfig config = {
  300,              // Soil moisture threshold (moderate)
  200,              // Optimal light minimum
  700,              // Optimal light maximum
  18.0,             // Optimal temp minimum (°C)
  26.0,             // Optimal temp maximum (°C)
  2000,             // Watering duration (2 seconds)
  60000,            // Check interval (1 minute)
  3600000           // Min watering interval (1 hour)
};
```

## Parameter Guide

### Soil Moisture Threshold
- **Range**: 0-1023 (analog reading)
- **Lower values**: More moisture required (wetter soil)
- **Higher values**: Less moisture required (drier soil)
- **Typical ranges**:
  - 150-250: Very moist (ferns, tropical plants)
  - 250-350: Moderately moist (most houseplants)
  - 400-600: Dry (succulents, cacti)

### Light Level
- **Range**: 0-1023 (analog reading)
- **Lower values**: Darker conditions
- **Higher values**: Brighter conditions
- **Typical ranges**:
  - 100-500: Low light (shade-loving plants)
  - 200-700: Medium light (most houseplants)
  - 400-900: High light (sun-loving plants)

### Temperature Range
- **Unit**: Celsius (°C)
- **Typical ranges**:
  - 15-24°C: Cool-loving plants
  - 18-26°C: Most houseplants
  - 20-30°C: Heat-loving tropical plants

### Watering Duration
- **Unit**: Milliseconds
- **Typical ranges**:
  - 1000-1500ms: Light watering (succulents)
  - 2000-2500ms: Normal watering (houseplants)
  - 3000-4000ms: Heavy watering (water-loving plants)

### Check Interval
- **Unit**: Milliseconds
- How often the system reads sensors
- **Typical values**:
  - 45000ms (45 seconds): Frequent monitoring
  - 60000ms (1 minute): Normal monitoring
  - 120000ms (2 minutes): Infrequent monitoring

### Minimum Watering Interval
- **Unit**: Milliseconds
- Prevents over-watering by setting cooldown period
- **Typical values**:
  - 1800000ms (30 minutes): Frequent watering (herbs)
  - 3600000ms (1 hour): Normal watering (houseplants)
  - 7200000ms (2 hours): Infrequent watering (succulents)
