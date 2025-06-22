#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>


void renderGraphics(double xMax,double xMin, double instances, double tMax, Eigen::MatrixXd& outputData);
float setScale(float delta, float idealDivs);