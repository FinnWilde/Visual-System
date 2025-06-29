#include "harmonic_oscillator.hpp"
#include "rk4.hpp"
#include "graphics.hpp"


#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>


int main() {

    int instances = 5000;//number of steps, higher steps -> higher quality, but longer load time
    double t = 0; //start time
    
    auto xDotDotFunction = [](double t) {  return 1;  };
    auto xDotFunction = [](double t) {  return (- 2 )/ (50 - 2 * t);  };
    auto xFunction = [](double t) { return 0; };
    auto inputFunction = [](double t) { return 1000/(50-2*t); };
    auto reference = [](double t) {return 3; };

    harmonicOscillator inputSystem(xDotDotFunction, xDotFunction, xFunction, inputFunction); //system params ->  m - mass (kg) | c - damping (kg/s) | k - stiffness (kg/s^2)  | u - input (N)  
    Eigen::Vector2d state(0, 0); //initial conditions -> x0 | v0

    double simTime = 20;
    double h = simTime/instances; //step size (s)

    Eigen::MatrixXd outputData(instances, 3); //matrix to store output data
    double xMax = state[0];
    double xMin = state[0];
 
    for (int i = 0; i < instances; i++) {

        /*
        std::cout << "Time (t): " << t
            << ", Position (x): " << state[0]
            << ", Velocity (v): " << state[1] << std::endl;
        */
        outputData(i, 0) = t;
        outputData(i, 1) = state[0];
        outputData(i, 2) = state[1];

        state = rk4_step(inputSystem, state, h, t);

        if (state[0] > xMax) xMax = state[0];
        if (state[0] < xMin) xMin = state[0];

        t += h;
    }

    std::cout << "xMax: " << xMax
        << ", xMin " << xMin << std::endl;

    int graphicsStatus = renderGraphics(xMax,xMin,instances,simTime,outputData);

    return 0;
}


