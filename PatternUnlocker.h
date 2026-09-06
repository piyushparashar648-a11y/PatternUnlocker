#ifndef PATTERNUNLOCKER_H
#define PATTERNUNLOCKER_H

#include <Arduino.h>
#include "USB.h"
#include "USBHIDMouse.h"

// Android 3x3 Grid Coordinates mapping (1000x1000 normalized absolute range)
// Grid layout:
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
struct Point {
    int16_t x;
    int16_t y;
};

class PatternUnlocker {
private:
    USBHIDMouse mouse;
    const Point* gridCoordinates;
    const int* pattern;
    size_t patternLength;
    size_t gridSize;

public:
    // Constructor
    PatternUnlocker(const Point* grid, size_t gridSize, const int* pat, size_t patLen);
    
    // Initialize USB and Mouse controller
    void begin();
    
    // Execute the pattern unlock gesture
    void executePatternUnlock();
    
    // Smooth interpolated movement between two points
    void smoothMove(Point from, Point to, int steps = 20, int delayMs = 10);
    
    // Get a grid point by index
    Point getGridPoint(int index);
    
    // Print pattern to serial (debugging)
    void printPattern();
};

#endif