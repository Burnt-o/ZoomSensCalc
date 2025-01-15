#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float mainSens);

// Find the two angles between which our target angle is
std::vector<float> dotTowardAngle(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle
);


// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    float viewAngleIncrement,
    float startingAngle,
    int counterClockwiseTurns
);

std::vector<float> calcZoomSensManip(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle1,
    float targetAngle2,
    float zoomFactor,
    int counterClockwiseTurns,
    int maxDots
);