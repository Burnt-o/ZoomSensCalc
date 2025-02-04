#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float& mainSens);

// Find the two angles between which our target angle is

struct ClosestDotsToAngle
{
    float closestLeftDot;
    float closestRightDot;

    explicit ClosestDotsToAngle(float l, float r) : closestLeftDot(l), closestRightDot(r) {}
};

// Find the two angles between which our target angle is
// If startingAngle == targetAngle, returns startingAngle.
ClosestDotsToAngle dotTowardAngle(
    const float& viewAngleIncrement,
    float startingAngle,
    const float& targetAngle
) noexcept;


// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    const float& viewAngleIncrement,
    float startingAngle,
    int& counterClockwiseTurns
) noexcept;


struct ZoomSensManipResult
{
    float ZoomSensitivityValue; // value to set in MCC settings menu
    int DotsToFirstAngle; 
    int SecondAngleExtraDots;

    friend std::ostream& operator<<(std::ostream& o, const ZoomSensManipResult& res) {
        o << "Zoom Sensitivity Value: " << res.ZoomSensitivityValue << std::endl;
        o << "DotsToFirstAngle: " << res.DotsToFirstAngle << std::endl;
        o << "Additonal dots to second angle: " <<res.SecondAngleExtraDots << std::endl;
        return o;
    }
};

std::vector<ZoomSensManipResult> calcZoomSensManip(
    const float& viewAngleIncrement,
    float& startingAngle,
    const float& targetAngle1,
    const float& targetAngle2,
    const float& zoomFactor,
    int& cCTurnsFor1,
    int& totalCCTurnsFor2,
    const int& maxDots
);