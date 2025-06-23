#pragma once
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <iomanip>


int renderGraphics(double xMax,double xMin, double instances, double tMax, Eigen::MatrixXd& outputData);

void setOriginToCentre(sf::Text &text);
float setScale(float delta, float idealDivs);
void drawGridlines(sf::RenderWindow& window, float xLength, float yLength, float xStartPosition, float yStartPosition, float xStep, float yStep, float numOfGridlines);
void drawXLabels(sf::RenderWindow& window, sf::Font font, float xPosition, float yPosition, float xStep, float numOfLabels, float scale);
void drawYLabels(sf::RenderWindow& window, sf::Font font, float xPosition, float yPosition, float yStep, float numOfLabels, float scale, float multiplyer);