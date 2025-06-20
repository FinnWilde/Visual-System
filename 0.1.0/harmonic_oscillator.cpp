#include "harmonic_oscillator.hpp"

harmonicOscillator::harmonicOscillator(double mass, double damping, double stiffness) //constructor
    : m(mass), c(damping), k(stiffness) {}

Eigen::Vector2d harmonicOscillator::evaluate(Eigen::Vector2d state) const { //member function
    return Eigen::Vector2d(state[1], (-c * state[1] - k * state[0]) / m); //returns dx/dt (row 0) and dv/dt (row 1) given inut values x (state[0]) and v (state[1])
}