#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>

void renderGraphics(double yMax,double yMin, double instances, double tMax, Eigen::MatrixXd& outputData);