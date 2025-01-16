#include "ZoomSensCalc.h"
#include "Constants.h"

// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float mainSens) {
    return mainSens * 0.0003878509742f; // Magic number found by Burnt
}

// Find the two angles between which our target angle is
// If startingAngle == targetAngle, returns startingAngle.
ClosestDotsToAngle dotTowardAngle(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle
) noexcept {

    if (startingAngle == targetAngle)
        return ClosestDotsToAngle(targetAngle, targetAngle);


    // Move startingAngle to the target one dot at a time(Increment if startingAngle is to the left of targetAngle, decrement if to the right)
    // Using an if-else statement instead of while because we only want one of these to happen
    if (startingAngle < targetAngle) {
        for (; startingAngle < targetAngle; startingAngle += viewAngleIncrement) {}
        if (startingAngle == targetAngle) return ClosestDotsToAngle(targetAngle, targetAngle);
        return ClosestDotsToAngle(startingAngle, startingAngle - viewAngleIncrement);
    }
    else if (startingAngle > targetAngle) {
        for (; startingAngle > targetAngle; startingAngle -= viewAngleIncrement) {}
        if (startingAngle == targetAngle) return ClosestDotsToAngle(targetAngle, targetAngle);
        return ClosestDotsToAngle(startingAngle + viewAngleIncrement, startingAngle);
    }
}

// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    float viewAngleIncrement,
    float startingAngle,
    int counterClockwiseTurns
) noexcept {
    // Depending on which way we are turning, increment/decrement the startingAngle
    // When we cross the zero boundary, we have completed a turn
    // Since radians work mod two pi, we subtract/add two pi to the resulting angle
    while (counterClockwiseTurns > 0) {
        startingAngle += viewAngleIncrement;
        if (startingAngle > twoPiRadians) {
            counterClockwiseTurns--;
            startingAngle -= twoPiRadians;
        }
    }
    while (counterClockwiseTurns < 0) {
        startingAngle -= viewAngleIncrement;
        if (startingAngle < 0) {
            counterClockwiseTurns++;
            startingAngle += twoPiRadians;
        }
    }
    return startingAngle;
}

std::vector<ZoomSensManipResult> calcZoomSensManip(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngel1,
    float targetAngel2,
    float zoomFactor,
    int cCTurnsFor1,
    int totalCCTurnsFor2,
    int maxDots
) {
    ClosestDotsToAngle x1x2 = dotTowardAngle(viewAngleIncrement, angleAfterTurns(viewAngleIncrement, startingAngle, cCTurnsFor1), targetAngel1);
    ClosestDotsToAngle p1p2 = dotTowardAngle(viewAngleIncrement, angleAfterTurns(viewAngleIncrement, startingAngle, totalCCTurnsFor2), targetAngel2);

    std::vector<ZoomSensManipResult> out = {};



    float eq1delta1 = targetAngel1 - x1x2.closestRightDot;
    float eq2delta1 = targetAngel2 - p1p2.closestRightDot;
    float eq1delta2 = targetAngel1 - x1x2.closestLeftDot;
    float eq2delta2 = targetAngel2 - p1p2.closestLeftDot;
    float y = 0.0f;
    int b = 0;
    float bCheck = 0.0f;

    // bCheck exists only to check if b is actually an integer
    for (short a = 1; a <= maxDots; a++) {
        y = eq1delta1 / a;
        b = eq2delta1 / y;
        bCheck = eq2delta1 / y;
        if (b == bCheck && b <= maxDots) {
            out.push_back(ZoomSensManipResult{
                y / (viewAngleIncrement / zoomFactor), 
                    a, 
                    b - a
                });
        }
        b = eq2delta2 / y;
        bCheck = eq2delta2 / y;
        if (b == bCheck && b <= maxDots) {
            out.push_back(ZoomSensManipResult{
                y / (viewAngleIncrement / zoomFactor),
                    a,
                    b - a
                });
        }
    }
    for (short a = -1; a >= -maxDots; a--) {
        y = eq1delta2 / a;
        b = eq2delta2 / y;
        bCheck = eq2delta2 / y;
        if (b == bCheck) {
            out.push_back(ZoomSensManipResult{
                y / (viewAngleIncrement / zoomFactor), 
                    a, 
                    b - a
                });
        }
        b = eq2delta1 / y;
        bCheck = eq2delta1 / y;
        if (b == bCheck) {
            out.push_back(ZoomSensManipResult{
                y / (viewAngleIncrement / zoomFactor),
                    a,
                    b - a
                });
        }
    }
    return out;
}
