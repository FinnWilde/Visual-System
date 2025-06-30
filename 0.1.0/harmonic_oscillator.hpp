#pragma once
#include <Eigen/Dense>
#include <functional>
#include <utility>

class harmonicOscillator {
public:
	std::function<double(double)> a;
	std::function<double(double, double, double)> b;
	std::function<double(double, double, double, double)> u;
	

	harmonicOscillator(std::function<double(double)> xDotDotFunc, std::function<double(double, double, double)> plantFunc, std::function<double(double, double, double, double)> inputFunc);

	Eigen::Vector3d evaluate(Eigen::Vector3d state, Eigen::Vector2d reference, double t) const;
};