#pragma once
#include <Eigen/Dense>

class harmonicOscillator {
public:
	double m, c, k;

	harmonicOscillator(double mass, double damping, double stiffness);

	Eigen::Vector2d evaluate(Eigen::Vector2d state) const;
};