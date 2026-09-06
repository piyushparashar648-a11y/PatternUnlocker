#include "PatternUnlocker.h"

PatternUnlocker::PatternUnlocker(const Point* grid, size_t gridSize, const int* pat, size_t patLen)
    : gridCoordinates(grid), gridSize(gridSize), pattern(pat), patternLength(patLen) {
}

void PatternUnlocker::begin() {
    Serial.begin(115200);
    
    // Initialize USB Host functionality
    mouse.begin();
    USB.begin();

    Serial.println("PatternUnlocker Initialized");
    Serial.println("Grid Size: " + String(gridSize));
    Serial.println("Pattern Length: " + String(patternLength));
}

Point PatternUnlocker::getGridPoint(int index) {
    if (index >= 0 && index < (int)gridSize) {
        return gridCoordinates[index];
    }
    return {0, 0};
}

void PatternUnlocker::smoothMove(Point from, Point to, int steps, int delayMs) {
    for (int step = 1; step <= steps; step++) {
        int16_t dx = from.x + ((to.x - from.x) * step) / steps;
        int16_t dy = from.y + ((to.y - from.y) * step) / steps;
        mouse.move(dx, dy);
        delay(delayMs);
    }
}

void PatternUnlocker::executePatternUnlock() {
    if (patternLength == 0) {
        Serial.println("Error: Pattern length is 0");
        return;
    }

    Serial.println("Executing pattern unlock gesture...");

    // Move to the initial pattern point
    Point start = getGridPoint(pattern[0]);
    mouse.move(start.x, start.y);
    delay(100);

    // Press down mouse button to start pattern drag
    mouse.press(MOUSE_LEFT);
    delay(150);

    // Swipe through each node in the pattern array
    for (size_t i = 1; i < patternLength; i++) {
        Point current = getGridPoint(pattern[i - 1]);
        Point target = getGridPoint(pattern[i]);
        
        // Smooth linear interpolation movement between points
        smoothMove(current, target, 20, 10);
        
        delay(100); // Pause at node point
    }

    // Release mouse button to register the pattern submission
    mouse.release(MOUSE_LEFT);
    Serial.println("Pattern execution complete.");
}

void PatternUnlocker::printPattern() {
    Serial.println("\n=== Current Pattern ===");
    for (size_t i = 0; i < patternLength; i++) {
        Point p = getGridPoint(pattern[i]);
        Serial.print("Step ");
        Serial.print(i);
        Serial.print(": Grid[");
        Serial.print(pattern[i]);
        Serial.print("] = (");
        Serial.print(p.x);
        Serial.print(", ");
        Serial.print(p.y);
        Serial.println(")");
    }
    Serial.println("======================\n");
}