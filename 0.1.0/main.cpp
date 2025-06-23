#include "harmonic_oscillator.hpp"
#include "rk4.hpp"
#include "graphics.hpp"


#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>


int main() {

    double t = 0;
    double h = 0.01;
    harmonicOscillator inputSystem(1.0, 5.0, 2.0); //system params ->  m - mass (kg) | c - damping (kg/s) | k - stiffness (kg/s^2)  
    Eigen::Vector2d state(5, 0); //initial conditions -> x0 | v0
    double simTime = 10;

    int instances = static_cast<int>(simTime / h) + 1; //total number of data points (ensures an integer output)
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

        state = rk4_step(inputSystem, state, h);

        if (state[0] > xMax) xMax = state[0];
        if (state[0] < xMin) xMin = state[0];

        t += h;
    }

    std::cout << "xMax: " << xMax
        << ", xMin " << xMin << std::endl;

    int graphicsStatus = renderGraphics(xMax,xMin,instances,simTime,outputData);

    return 0;
}


