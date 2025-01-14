#include "ZoomSensCalc.h"

const float twoPi = 6.283185482f;

// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float mainSens) {
    return mainSens * 0.0003878509742f; // Magic number found by Burnt
}

// Find the two angles between which our target angle is
std::vector<float> dotTowardAngle(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle
) {

    float rightDot = 0.0f;
    float leftDot = 0.0f;
    // Using a vector because I don't know how else you would return 2 things with one function
    std::vector<float> outAngles = {};

    // Move startingAngle to the target one dot at a time(Increment if startingAngle is to the left of targetAngle, decrement if to the right)
    // Using an if-else statement instead of while because we only want one of these to happen
    if (startingAngle < targetAngle) {
        for (; startingAngle < targetAngle; startingAngle += viewAngleIncrement) {}
        leftDot = startingAngle;
        rightDot = leftDot - viewAngleIncrement;

    }
    else
        if (startingAngle > targetAngle) {
            for (; startingAngle > targetAngle; startingAngle -= viewAngleIncrement) {}
            rightDot = startingAngle;
            leftDot = rightDot + viewAngleIncrement;
        }

    outAngles.push_back(rightDot);
    outAngles.push_back(leftDot);
    return outAngles;
}

// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    float viewAngleIncrement,
    float startingAngle,
    int counterClockiseTurns
) {
    // Depending on which way we are turning, increment/decrement the startingAngle
    // When we cross the zero boundary, we have completed a turn
    // Since radians work mod two pi, we subtract/add two pi to the resulting angle
    while (counterClockiseTurns > 0) {
        startingAngle -= viewAngleIncrement;
        if (startingAngle < 0) {
            counterClockiseTurns--;
            startingAngle += twoPi;
        }
    }
    while (counterClockiseTurns < 0) {
        startingAngle += viewAngleIncrement;
        if (startingAngle > twoPi) {
            counterClockiseTurns++;
            startingAngle -= twoPi;
        }
    }
    return startingAngle;
}
