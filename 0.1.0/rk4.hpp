#pragma once
#include "harmonic_oscillator.hpp"
#include <Eigen/Dense>

Eigen::Vector3d rk4_step(harmonicOscillator& inputSystem, Eigen::Vector3d& state, Eigen::Vector2d& reference, double h, double t);
