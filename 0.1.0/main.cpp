#include "harmonic_oscillator.hpp"
#include "rk4.hpp"

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>


int main() {

    double t = 0;
    double h = 0.1;
    harmonicOscillator inputSystem(2.0, 5.0, 3.0); //system params , m,c,k
    Eigen::Vector2d state(1, 0); //initial conditions x0, v0
    double simTime = 20;

    for (int i = 0; i < simTime / h + 1; i++) {

        std::cout << "Time (t): " << t
            << ", Position (x): " << state[0]
            << ", Velocity (v): " << state[1] << std::endl;

        state = rk4_step(inputSystem, state, h);

        t += h;
    }


    return 0;
}

