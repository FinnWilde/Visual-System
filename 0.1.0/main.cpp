#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>

using Eigen::Vector2d;

class harmonicOscillator { //this class represents any oscillator of form ax..+bx.+cx=0

public:

    double m, c, k; //members of the class - every instant of the class will have these parameters

    harmonicOscillator(double mass, double damping, double stiffness) //constructor
        : m(mass), c(damping), k(stiffness) {}


    Vector2d evaluate(Vector2d state) const { //const to ensure function does not change members
        return Vector2d(state[1], (-c * state[1] - k * state[0]) / m); //rearranges 2nd order ODE into two first order ODEs. Row 0 = dx/dt, row 1 = dv/dt
    }
};

Vector2d rk4_step(harmonicOscillator& inputSystem, Vector2d state, double h)
{
    Vector2d k1 = inputSystem.evaluate(state);
    Vector2d k2 = inputSystem.evaluate(state + h * k1 / 2);
    Vector2d k3 = inputSystem.evaluate(state + h * k2 / 2);
    Vector2d k4 = inputSystem.evaluate(state + h * k3);

    return state + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}


int main() {

    double t = 0;
    double h = 0.1;
    harmonicOscillator inputSystem(2.0, 5.0, 3.0); //system params , m,c,k
    Vector2d state(1, 0); //initial conditions x0, v0
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

