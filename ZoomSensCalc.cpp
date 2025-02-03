#include <string>
#include <array>
#include <vector>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <cmath>
#include <format>
#include "Constants.h"

struct ClosestDotsToAngle
{
    float closestLeftDot;
    float closestRightDot;

    explicit ClosestDotsToAngle(float l, float r) : closestLeftDot(l), closestRightDot(r) { assert(l >= r); }
};

struct ZoomSensManipResult
{
    float ZoomSensitivityValue; // value to set in MCC settings menu
    int DotsToFirstAngle; 
    int SecondAngleExtraDots;

    friend std::ostream& operator<<(std::ostream& o, ZoomSensManipResult const& res) {
        o << "Zoom Sensitivity Value: " << res.ZoomSensitivityValue << std::endl;
        o << "Dots to first angle: " << res.DotsToFirstAngle << std::endl;
        o << "Additonal dots to second angle: " <<res.SecondAngleExtraDots << std::endl;
        return o;
    }
};


// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float mainSens) {
    constexpr float c1 = 0.02222222276f;
    constexpr float c2 = 3.141592741f;
    constexpr float c3 = 180.f;

    mainSens *= c1;
    mainSens *= c2;
    mainSens /= c3;
    return mainSens;
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
    float targetAngle1,
    float targetAngle2,
    float zoomFactor,
    int cCTurnsFor1,
    int totalCCTurnsFor2,
    int maxDots
) {
    ClosestDotsToAngle x1x2 = dotTowardAngle(viewAngleIncrement, angleAfterTurns(viewAngleIncrement, startingAngle, cCTurnsFor1), targetAngle1);
    ClosestDotsToAngle p1p2 = dotTowardAngle(viewAngleIncrement, angleAfterTurns(viewAngleIncrement, startingAngle, totalCCTurnsFor2), targetAngle2);

    std::vector<ZoomSensManipResult> out = {};

    float eq1delta1 = targetAngle1 - x1x2.closestRightDot;
    float eq2delta1 = targetAngle2 - p1p2.closestRightDot;
    float eq1delta2 = targetAngle1 - x1x2.closestLeftDot;
    float eq2delta2 = targetAngle2 - p1p2.closestLeftDot;

    float eq2delta1C = targetAngle2 - p1p2.closestRightDot;
    float eq2delta2C = targetAngle2 - p1p2.closestLeftDot;
    float y = 0.0f;
    int b = 0;
    float bCheck = 0.0f;

    // bCheck exists only to check if b is actually an integer
    for (short i = 0; i <= maxDots; i++) {
        for (short j = 0; j <= maxDots; j++) {
            for (short a = 1; a <= maxDots; a++) {
                y = eq1delta1 / a;
                b = eq2delta1 / y;
                bCheck = eq2delta1 / y;
                if (abs(b - bCheck) <= 0.001f && abs(b - a) <= maxDots) {
                    out.push_back(ZoomSensManipResult{
                        y / (viewAngleIncrement / zoomFactor),
                            a,
                            b - a
                        });
                }
                b = eq2delta2 / y;
                bCheck = eq2delta2 / y;
                if (abs(b - bCheck) <= 0.001f && abs(b - a) <= maxDots) {
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
                if (abs(b - bCheck) <= 0.001f && abs(b - a) <= maxDots) {
                    out.push_back(ZoomSensManipResult{
                        y / (viewAngleIncrement / zoomFactor),
                            a,
                            b - a
                        });
                }
                b = eq2delta1 / y;
                bCheck = eq2delta1 / y;
                if (abs(b - bCheck) <= 0.001f && abs(b - a) <= maxDots) {
                    out.push_back(ZoomSensManipResult{
                        y / (viewAngleIncrement / zoomFactor),
                            a,
                            b - a
                        });
                }
            }
            eq2delta1 += viewAngleIncrement;
            eq2delta2 -= viewAngleIncrement;
        }
        eq1delta1 += viewAngleIncrement;
        eq1delta2 -= viewAngleIncrement;
        eq2delta1 = eq2delta1C;
        eq2delta2 = eq2delta2C;
    }
    return out;
}