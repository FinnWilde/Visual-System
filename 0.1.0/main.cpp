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
    
    //Plant (not compatable with any functions of xDotDot yet...)
    auto xDotDotFunction = [](double t) {  return 2;  };
    auto plantFunction = [](double t, double xDot, double x) { return 0.1*xDot + 9.81*std::sin(x); };

    auto inputFunction = [](double t, double eDot, double e, double E) { 
        
        double Kp = 60, Ki = 5, Kd = 25;
        double maxInput = 50, minInput = -50;
        double input = Kp * e + Ki * E + Kd * eDot; 
        if (input > maxInput) {
            input = maxInput;
        }
        else if (input < minInput) {
            input = minInput;
        }
        
        std::cout << "input: " << input << std::endl;
        return input;
        
    };

    auto referenceFunction = [](double t) {return 3; };
    auto referenceDotFunction = [](double t) {return 0; };

    harmonicOscillator inputSystem(xDotDotFunction, plantFunction, inputFunction); //system params ->  m - mass (kg) | c - damping (kg/s) | k - stiffness (kg/s^2)  | u - input (N)  
    Eigen::Vector3d state(3.1415, 50, 0); //initial conditions -> x0 | v0 | E  
    Eigen::Vector2d referenceState(referenceFunction(0), referenceDotFunction(0));

    double simTime = 60;
    double h = simTime/instances; //step size (s)

    Eigen::MatrixXd outputData(instances, 3); //matrix to store output data
    double xMax = state[0];
    double xMin = state[0];
 
    for (int i = 0; i < instances; i++) {

        
        std::cout << "Time (t): " << t
            << ", Position (x): " << state[0]
            << ", Velocity (v): " << state[1] << std::endl;
        
        outputData(i, 0) = t;
        outputData(i, 1) = state[0];
        outputData(i, 2) = state[1];


        state = rk4_step(inputSystem, state, referenceState, h, t);

        if (state[0] > xMax) xMax = state[0];
        if (state[0] < xMin) xMin = state[0];

        t += h;

        referenceState(0) = referenceFunction(t);
        referenceState(1) = referenceDotFunction(t);
    }

    std::cout << "xMax: " << xMax
        << ", xMin " << xMin << std::endl;

    int graphicsStatus = renderGraphics(xMax,xMin,instances,simTime,outputData);

    return 0;
}


