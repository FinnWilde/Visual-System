#include "rk4.hpp"
using namespace Eigen;

Vector3d rk4_step(harmonicOscillator& inputSystem, Vector3d& state, Vector2d& reference, double h, double t) {
    Vector3d k1 = inputSystem.evaluate(state, reference, t);
    Vector3d k2 = inputSystem.evaluate(state + h * k1 / 2, reference, t);
    Vector3d k3 = inputSystem.evaluate(state + h * k2 / 2, reference, t);
    Vector3d k4 = inputSystem.evaluate(state + h * k3, reference, t);

    return state + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}

//uses Runge-Kutta 4 to approximate v, I and crucially x a step (h) in time later than the last values of v, I and x.
//recall state is a 3d vector containing (x, v, I)
//reference is a 2d vector containing (r, rDot)