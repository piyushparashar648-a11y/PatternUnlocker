#include "PatternUnlocker.h"

// Android 3x3 Grid Coordinates mapping (1000x1000 normalized absolute range)
// Grid layout:
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
const Point GRID_COORDINATES[9] = {
    {250, 250}, {500, 250}, {750, 250}, // Top row
    {250, 500}, {500, 500}, {750, 500}, // Middle row
    {250, 750}, {500, 750}, {750, 750}  // Bottom row
};

// Define pattern sequence (0 to 8 matching the grid layout)
const int pattern[] = {0, 4, 8, 1, 3, 5, 7, 2, 6};
const size_t patternLength = sizeof(pattern) / sizeof(pattern[0]);

// Create PatternUnlocker instance
PatternUnlocker unlocker(GRID_COORDINATES, 9, pattern, patternLength);

void setup() {
    // Initialize the pattern unlocker
    unlocker.begin();
    
    // Print the pattern to serial for debugging
    unlocker.printPattern();
    
    // Safety delay before executing unlock attempt
    delay(3000);
    
    // Execute the pattern unlock gesture
    unlocker.executePatternUnlock();
}

void loop() {
    // Idle loop after pattern sequence execution
    delay(1000);
}