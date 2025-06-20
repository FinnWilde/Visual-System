#include "graphics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


void initWindow(double xMax, double xMin, double instances) {

    float windowX = 800; //define window size
    float windowY = 600;

    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Graph"); //create the window

    float axisWidth = 1;

    //               Graphing Frame Size         Ratio                 Offset
    float xAxisHeight = (windowY-150) * ((xMax) / (xMax - xMin)) + 75 - axisWidth/2; 
    std::cout << "xAxis Height: " << xAxisHeight << std::endl;

    if (xMin > 0) {
        xAxisHeight = windowY - 50;
    }

    /*
    ^finds the height the x axis should sit at
    if Xmin is negative, the x axis should sit so that pixels above : pixels below = xMax : xMin
    (note that the axis frame is 100 pixels shorter than the window frame, and the graphing frame is a further 50 pixels shorter than the axis frame
    - axisWidth/2 is to ensure the axis sits centrally so the ratio is as close to xMax:xMin as possible)
    if Xmin is positve, the x axis should sit in the bottom corner
    */
    
    sf::RectangleShape xAxis(sf::Vector2f(windowX - 100, axisWidth));
    xAxis.setPosition(50.f, xAxisHeight);
    xAxis.setFillColor(sf::Color::White);

    sf::RectangleShape yAxis(sf::Vector2f(axisWidth, windowY -98)); //+2 to fill the otherwise vacant square in the bottom left
    yAxis.setOrigin(yAxis.getSize().x, 0);
    yAxis.setPosition(50.f, 50.f);
    yAxis.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(xAxis);
        window.draw(yAxis);
        window.display();
    }
}