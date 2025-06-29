#include "harmonic_oscillator.hpp"

harmonicOscillator::harmonicOscillator(std::function<double(double)> massFunc, std::function<double(double)> dampingFunc, std::function<double(double)> stiffnessFunc, std::function<double(double)> inputFunc) //constructor
    : m(std::move(massFunc)), c(std::move(dampingFunc)), k(std::move(stiffnessFunc)), u(std::move(inputFunc)) {}

Eigen::Vector2d harmonicOscillator::evaluate(Eigen::Vector2d state, double t) const { //member function
    return Eigen::Vector2d(state[1], (-c(t) * state[1] - k(t) * state[0] + u(t)) / m(t)); //returns dx/dt (row 0) and dv/dt (row 1) given input values x (state[0]) and v (state[1])
}