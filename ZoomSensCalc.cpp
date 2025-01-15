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
        else
            if (startingAngle == targetAngle) outAngles.push_back(-1);
    if (startingAngle == targetAngle) outAngles.push_back(-2);
    outAngles.push_back(rightDot);
    outAngles.push_back(leftDot);
    return outAngles;
}

// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    float viewAngleIncrement,
    float startingAngle,
    int counterClockwiseTurns
) {
    // Depending on which way we are turning, increment/decrement the startingAngle
    // When we cross the zero boundary, we have completed a turn
    // Since radians work mod two pi, we subtract/add two pi to the resulting angle
    while (counterClockwiseTurns > 0) {
        startingAngle -= viewAngleIncrement;
        if (startingAngle < 0) {
            counterClockwiseTurns--;
            startingAngle += twoPi;
        }
    }
    while (counterClockwiseTurns < 0) {
        startingAngle += viewAngleIncrement;
        if (startingAngle > twoPi) {
            counterClockwiseTurns++;
            startingAngle -= twoPi;
        }
    }
    return startingAngle;
}

std::vector<float> calcZoomSensManip(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle1,
    float targetAngle2,
    float zoomFactor,
    int counterClockwiseTurns,
    int maxDots
) {
    startingAngle = angleAfterTurns(viewAngleIncrement, startingAngle, counterClockwiseTurns);
    std::vector<float> x1x2 = dotTowardAngle(viewAngleIncrement, startingAngle, targetAngle1);
    std::vector<float> p1p2 = dotTowardAngle(viewAngleIncrement, startingAngle, targetAngle2);

    std::vector<float> out = {};

    if (x1x2[0] == -1) { std::cout << "Target Angle 1 and starting angle are already matching!" << std::endl; return out; }
    if (p1p2[0] == -1) { std::cout << "Target Angle 2 and starting angle are already matching!" << std::endl; return out; }
    if (x1x2[0] == -2) { std::cout << "Target Angle 1 does not need a zoom manip" << std::endl; return out; }
    if (p1p2[0] == -2) { std::cout << "Target Angle 2 does not need a zoom manip" << std::endl; return out; }

    float eq1delta1 = targetAngle1 - x1x2[0];
    float eq2delta1 = targetAngle2 - p1p2[0];
    float eq1delta2 = targetAngle1 - x1x2[1];
    float eq2delta2 = targetAngle2 - p1p2[1];
    float y = 0.0f;
    int b = 0;
    float bCheck = 0.0f;

    // bCheck exists only to check if b is actually an integer
    for (short a = 1; a <= maxDots; a++) {
        y = eq1delta1 / a;
        b = eq2delta1 / y;
        bCheck = eq2delta1 / y;
        if (b == bCheck) {
            out.push_back(y / (viewAngleIncrement / zoomFactor));
            out.push_back(a);
            out.push_back(b - a);
        }
        b = eq2delta2 / y;
        bCheck = eq2delta2 / y;
        if (b == bCheck) {
            out.push_back(y / (viewAngleIncrement / zoomFactor));
            out.push_back(a);
            out.push_back(b - a);
        }
    }
    for (short a = -1; a >= -maxDots; a--) {
        y = eq1delta2 / a;
        b = eq2delta2 / y;
        bCheck = eq2delta2 / y;
        if (b == bCheck) {
            out.push_back(y / (viewAngleIncrement / zoomFactor));
            out.push_back(a);
            out.push_back(b - a);
        }
        b = eq2delta1 / y;
        bCheck = eq2delta1 / y;
        if (b == bCheck) {
            out.push_back(y / (viewAngleIncrement / zoomFactor));
            out.push_back(a);
            out.push_back(b - a);
        }
    }
    return out;
}
