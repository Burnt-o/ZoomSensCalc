#include "ZoomSensCalc.h"
#include "Constants.h"
int main() {
    double sens = 6.8;
    float viewAngleIncrement = viewAngleIncrementFinder(sens);

    {
        std::cout << "Calculating zoom sens manip for SC!" << std::endl;
        auto zoomSensManipResult = calcZoomSensManip(viewAngleIncrement, SC_startingAngle, SC_targetAngle, SC_targetAngle, 2, 0, 0, 3);


        if (zoomSensManipResult.empty())
            std::cout << "no manips found :(";

        for (auto& manip : zoomSensManipResult)
        {
            std::cout << manip << std::endl;
        }
    }


    // try a single manip for RS3 and CJSS ? 

    {
        std::cout << "Calculating zoom sens manip for 343: RS3 AND CJSS!!" << std::endl;
        auto zoomSensManipResult = calcZoomSensManip(viewAngleIncrement, 5.3184395f, 3.4001875f, 5.0436749f, 2, -1, -1, 1000);
        if (zoomSensManipResult.empty())
            std::cout << "no manips found :(";

        for (auto& manip : zoomSensManipResult)
        {
            std::cout << manip << std::endl;
        }


    }

    std::string block;
    std::cin >> block;
}