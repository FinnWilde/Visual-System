#include "rk4.hpp"
using Eigen::Vector2d;

Vector2d rk4_step(harmonicOscillator& inputSystem, Vector2d& state, double h) {
    Vector2d k1 = inputSystem.evaluate(state);
    Vector2d k2 = inputSystem.evaluate(state + h * k1 / 2);
    Vector2d k3 = inputSystem.evaluate(state + h * k2 / 2);
    Vector2d k4 = inputSystem.evaluate(state + h * k3);

    return state + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}

//uses Runge-Kutta 4 to approximate v and crucially x a step (h) in time later than the last values of v and x.
//recall state is a 2d vector containing (x,v)