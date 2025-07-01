#include "harmonic_oscillator.hpp"
#include "rk4.hpp"
#include "graphics.hpp"


#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>
constexpr double PI = 3.14159265358979323846;


int main() {

    int instances = 5000;//number of steps, higher steps -> higher quality, but longer load time
    double t = 0; //start time
    
    //Plant (not compatable with any functions of xDotDot yet...)
    auto xDotDotFunction = [](double t) {  return 2;  };
    auto plantFunction = [](double t, double xDot, double x) { return 3 * xDot + 5 * x; };

    
    auto controllerFunction = [](double e, double eDot, double E) {
        double Kp = 0, Ki = 0, Kd = 0;

        double input = Kp * e + Ki * E + Kd * eDot;

        double maxInput = 50, minInput = -50;
        if (input > maxInput) input = maxInput;
        if (input < minInput) input = minInput;
        //std::cout << "e: " << e << ", eDot: " << eDot << ", E: " << E << " => input: " << input << std::endl;
        //std::cout << input << std::endl;
        return input;
    };
    auto disturbanceFunction = [](double t) { return 0; };
    auto inputFunction = [&controllerFunction, &disturbanceFunction](double t, double e, double eDot, double E) { return controllerFunction(e, eDot, E) + disturbanceFunction(t); };

    auto referenceFunction = [](double t) {return  0; };
    auto referenceDotFunction = [](double t) {return 0; }; //add solver here

    harmonicOscillator inputSystem(xDotDotFunction, plantFunction, inputFunction); //system params 
    Eigen::Vector3d state(501.65, 0, 0); //initial conditions -> x0 | v0 | E  
    Eigen::Vector2d referenceState(referenceFunction(0), referenceDotFunction(0)); //initial reference -> r | rDot

    double simTime = 20;
    double h = simTime/instances; //step size (s)

    Eigen::MatrixXd outputData(instances + 1, 4); //matrix to store output data
    double xMax = state[0];
    double xMin = state[0];
 
    for (int i = 0; i <= instances ; i++) {

        if (i == instances) {
            
            std::cout << "Time (t): " << t
            << ", Position (x): " << state[0]
            << ", Velocity (v): " << state[1] << std::endl;
        

        }
        
        outputData(i, 0) = t;
        outputData(i, 1) = state[0];
        outputData(i, 2) = state[1];
        outputData(i, 3) = referenceState[0];


        state = rk4_step(inputSystem, state, referenceState, h, t);

        if (state[0] > xMax) xMax = state[0];
        if (state[0] < xMin) xMin = state[0];

        t += h;

        referenceState[0] = referenceFunction(t);
        referenceState[1] = referenceDotFunction(t);

        if (referenceState[0] > xMax) xMax = referenceState[0];
        if (referenceState[0] < xMin) xMin = referenceState[0];
    }

    std::cout << "xMax: " << xMax
        << ", xMin " << xMin << std::endl;

    int graphicsStatus = renderGraphics(xMax,xMin,instances,simTime,outputData);

    return 0;
}


