#include "harmonic_oscillator.hpp"

harmonicOscillator::harmonicOscillator(std::function<double(double)> xDotDotFunc, std::function<double(double, double, double)> plantFunc, std::function<double(double, double, double, double)> inputFunc) //constructor
    : a(std::move(xDotDotFunc)), b(std::move(plantFunc)), u(std::move(inputFunc)) {}

Eigen::Vector3d harmonicOscillator::evaluate(Eigen::Vector3d state, Eigen::Vector2d reference, double t) const { //member function
    Eigen::Vector2d error = reference - state.head<2>();
    return Eigen::Vector3d(state[1], (-b(t, state[1], state[0]) + u(t, error[0], error[1], state[2])) / a(t), error[0]); //state derivative

    //returns dx/dt (row 0), dv/dt (row 1) and error (row 3) 
    //given input values x (state[0]), v (state[1]) and errorIntegral (state[3])
}