#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include "WinUtilities.h"
// Find the increment in radians when we move one dot with a particular sensitivity
float viewAngleIncrementFinder(float mainSens);

// Find the two angles between which our target angle is

struct ClosestDotsToAngle
{
    float closestLeftDot;
    float closestRightDot;

    explicit ClosestDotsToAngle(float l, float r) : closestLeftDot(l), closestRightDot(r) { assert(l >= r); }
};

// Find the two angles between which our target angle is
// If startingAngle == targetAngle, returns startingAngle.
ClosestDotsToAngle dotTowardAngle(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle
) noexcept;


// Find the view angle after doing the specified number of clockwise turns
// Specifically, the first angle we get after crossing the zero bundary
float angleAfterTurns(
    float viewAngleIncrement,
    float startingAngle,
    int counterClockwiseTurns
) noexcept;


struct ZoomSensManipResult
{
    float ZoomSensitivityValue; // value to set in MCC settings menu
    int DotsToFirstAngle; 
    int SecondAngleExtraDots;

    friend std::ostream& operator<<(std::ostream& o, ZoomSensManipResult const& res) {
        o << "Zoom Sensitivity Value: " << ExactFloatToString(res.ZoomSensitivityValue) << std::endl;
        o << "DotsToFirstAngle: " << res.DotsToFirstAngle << std::endl;
        o << "Additonal dots to second angle: " <<res.SecondAngleExtraDots << std::endl;
        return o;
    }
};

std::vector<ZoomSensManipResult> calcZoomSensManip(
    float viewAngleIncrement,
    float startingAngle,
    float targetAngle1,
    float targetAngle2,
    float zoomFactor,
    int counterClockwiseTurns,
    int maxDots
);