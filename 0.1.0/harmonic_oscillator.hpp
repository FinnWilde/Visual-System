#pragma once
#include <Eigen/Dense>
#include <functional>
#include <utility>

class harmonicOscillator {
public:
	std::function<double(double)>m, c, k, u;

	harmonicOscillator(std::function<double(double)> massFunc, std::function<double(double)> dampingFunc, std::function<double(double)> stiffnessFunc, std::function<double(double)> inputFunc);

	Eigen::Vector2d evaluate(Eigen::Vector2d state, double t) const;
};