#include "ZoomSensCalc.h"
#include "Constants.h"
int main() {
    float sens = 6.8f;
    float startingAngle = 0.0f;
    float targetAngle1 = 0.0f;
    float targetAngle2 = 0.0f;
    int cCTurns1 = 0;
    int cCturns2 = 0;
    float zoomFactor = 0.0f;
    int maxDots = 0;


    std::cout << "Main sensitivity: ";
    std::cin >> sens;
    std::cout << "\nStarting angle: ";
    std::cin >> startingAngle;
    std::cout << "\nTarget Angle 1: ";
    std::cin >> targetAngle1;
    std::cout << "\nTarget Angle 2: ";
    std::cin >> targetAngle2;
    std::cout << "\nThe number of counter clockwise turns you will be doing before the first trick(Negative values for clockwise): ";
    std::cin >> cCTurns1;
    std::cout << "\nThe total number of turns you will be doing before the second trick: ";
    std::cin >> cCturns2;
    std::cout << "\nThe zoom factor of your weapon: ";
    std::cin >> zoomFactor;
    std::cout << "\nThe maximum number of dots to use: ";
    std::cin >> maxDots;


        float viewAngleIncrement = viewAngleIncrementFinder(sens);
        std::cout << "\nCalculating manip..." << std::endl;
        std::cout << "with params:" << std::endl;
        std::cout << "sens:" << sens << std::endl;
        std::cout << "viewAngleIncrement:" << viewAngleIncrement << std::endl;
        std::cout << "startingAngle:" << startingAngle << std::endl;
        std::cout << "targetAngle1:" << targetAngle1 << std::endl;
        std::cout << "targetAngle2:" << targetAngle2 << std::endl;
        std::cout << "cCTurns1:" << cCTurns1 << std::endl;
        std::cout << "cCturns2:" << cCturns2 << std::endl;
        std::cout << "zoomFactor:" << zoomFactor << std::endl;
        std::cout << "maxDots:" << maxDots << std::endl;
        auto zoomSensResult = calcZoomSensManip(viewAngleIncrement, startingAngle, targetAngle1, targetAngle2, zoomFactor, cCTurns1, cCturns2, maxDots);

        if (zoomSensResult.empty()) std::cout << "\nNo manips found" << std::endl;

        for (auto& manip : zoomSensResult) {
            std::cout << manip << std::endl;
        }


    // {
    //     std::cout << "Calculating zoom sens manip for SC!" << std::endl;
    //     auto zoomSensManipResult = calcZoomSensManip(viewAngleIncrement, SC_startingAngle, SC_targetAngle, SC_targetAngle, 2, 0, 0, 3);


    //     if (zoomSensManipResult.empty())
    //         std::cout << "no manips found :(";

    //     for (auto& manip : zoomSensManipResult)
    //     {
    //         std::cout << manip << std::endl;
    //     }
    // }


    // // try a single manip for RS3 and CJSS ? 

    // {
    //     std::cout << "Calculating zoom sens manip for 343: RS3 AND CJSS!!" << std::endl;
    //     auto zoomSensManipResult = calcZoomSensManip(viewAngleIncrement, 5.3184395f, 3.4001875f, 5.0436749f, 2, -1, -1, 1000);
    //     if (zoomSensManipResult.empty())
    //         std::cout << "no manips found :(";

    //     for (auto& manip : zoomSensManipResult)
    //     {
    //         std::cout << manip << std::endl;
    //     }


    // }

    std::string block;
    std::cin >> block;
}