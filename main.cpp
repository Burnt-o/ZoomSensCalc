#include "ZoomSensCalc.h"
#include "Constants.h"
int main() {
    double sens = 6.8;
    float viewAngleIncrement = viewAngleIncrementFinder(sens);

    
    std::cout << "Calculating zoom sens manip for SC!" << std::endl;
    auto zoomSensManipResult = calcZoomSensManip(viewAngleIncrement, SC_startingAngle, SC_targetAngle, SC_targetAngle, 2, 0, 3);


    if (zoomSensManipResult.empty())
        std::cout << "no manips found :(";

    for (auto& manip : zoomSensManipResult)
    {
        std::cout << manip << std::endl;
    }


    std::string block;
    std::cin >> block;
}