#pragma once
#include "harmonic_oscillator.hpp"
#include <Eigen/Dense>

Eigen::Vector2d rk4_step(harmonicOscillator& inputSystem, Eigen::Vector2d& state, double h, double t);
