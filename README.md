# PatternUnlocker

An Arduino library for ESP32 to emulate Android pattern lock gestures via USB HID mouse commands.

## Description

PatternUnlocker is a specialized library designed for ESP32 microcontrollers to simulate Android pattern lock unlock sequences. It communicates with Android devices via USB OTG (On-The-Go) cable by emulating HID mouse movements and clicks.

The library supports the standard Android 3x3 grid pattern lock with smooth interpolated movements between grid points for realistic gesture simulation.

## Features

- **USB HID Mouse Emulation**: Communicate with Android devices via USB OTG
- **3x3 Grid Support**: Full support for Android's standard 9-point grid
- **Smooth Interpolation**: Linear interpolation between pattern points for natural movements
- **Configurable Patterns**: Easy pattern definition and execution
- **Debug Output**: Serial print functions for pattern verification

## Hardware Requirements

- ESP32 microcontroller with USB support
- USB OTG cable
- Android device with pattern lock enabled

## Installation

1. Download the library as a ZIP file
2. In Arduino IDE: Sketch → Include Library → Add .ZIP Library
3. Select the PatternUnlocker.zip file

## Quick Start

```cpp
#include "PatternUnlocker.h"

// Define grid coordinates
const Point GRID_COORDINATES[9] = {
    {250, 250}, {500, 250}, {750, 250}, // Top row
    {250, 500}, {500, 500}, {750, 500}, // Middle row
    {250, 750}, {500, 750}, {750, 750}  // Bottom row
};

// Define pattern (0-8 representing grid positions)
const int pattern[] = {0, 4, 8, 1, 3, 5, 7, 2, 6};
const size_t patternLength = sizeof(pattern) / sizeof(pattern[0]);

// Create unlocker instance
PatternUnlocker unlocker(GRID_COORDINATES, 9, pattern, patternLength);

void setup() {
    unlocker.begin();
    delay(3000);
    unlocker.executePatternUnlock();
}

void loop() {
    delay(1000);
}
```

## API Reference

### Constructor
```cpp
PatternUnlocker(const Point* grid, size_t gridSize, const int* pat, size_t patLen)
```

### Methods

- `void begin()` - Initialize USB and Mouse controller
- `void executePatternUnlock()` - Execute the pattern unlock gesture
- `void smoothMove(Point from, Point to, int steps, int delayMs)` - Smooth movement between points
- `Point getGridPoint(int index)` - Get grid point by index
- `void printPattern()` - Print pattern to serial (debugging)

## Grid Layout

```
0 | 1 | 2
---------
3 | 4 | 5
---------
6 | 7 | 8
```

Each position uses coordinates in the 0-1000 range:
- Top-left (0): (250, 250)
- Center (4): (500, 500)
- Bottom-right (8): (750, 750)

## License

MIT License

## Author

Piyush Parashar