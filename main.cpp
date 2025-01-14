#include "ZoomSensCalc.h"

int main() {
    double sens = 6.8;
    float viewAngleIncrement = viewAngleIncrementFinder(sens);

    std::cout << std::setprecision(16) << viewAngleIncrement << "\n" << std::endl;
    std::vector<float> x1x2 = dotTowardAngle(viewAngleIncrement, 2, 1);
    std::cout << x1x2[0] << "\t" << x1x2[1] << "\n" << std::endl;
    std::cout << angleAfterTurns(0.1f, 1.05f, -1);

    std::string block;
    std::cin >> block;
}