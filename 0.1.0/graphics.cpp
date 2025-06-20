#include "graphics.hpp"

void renderGraphics(double yMax, double yMin, double instances, double tMax, Eigen::MatrixXd& outputData) { //note xMax from ODE is now yMax - switching from t,x axis to x,y for graphics

    float windowX = 800; //define window size
    float windowY = 600;

    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Distance (m) against Time (s)"); //create the window

    float axisWidth = 1;
    float axisMargin = 50;
   

    //                     Graphing Frame Height              Ratio                      Offset
    float xAxisHeight = (windowY - 2 * axisMargin) * ((yMax) / (yMax - yMin)) + axisMargin - axisWidth / 2;
    std::cout << "xAxis Height: " << xAxisHeight << std::endl;
    if (yMin > 0) {
        xAxisHeight = windowY - 50;
    }

    /*
    ^finds the height the x axis should sit at
    if Xmin is negative, the x axis should sit so that pixels above : pixels below = yMax : yMin
    (note that the axis frame is 100 pixels shorter than the window frame
    - axisWidth/2 is to ensure the axis sits centrally so the ratio is as close to yMax:yMin as possible)
    if yMin is positve, the x axis should sit in the bottom corner
    */
    
    sf::RectangleShape xAxis(sf::Vector2f(windowX - 100, axisWidth));
    xAxis.setPosition(50.f, xAxisHeight);
    xAxis.setFillColor(sf::Color::White);

    sf::RectangleShape yAxis(sf::Vector2f(axisWidth, windowY -98)); //+2 to fill the otherwise vacant square in the bottom left
    yAxis.setOrigin(yAxis.getSize().x, 0);
    yAxis.setPosition(50.f, 50.f);
    yAxis.setFillColor(sf::Color::White);

    sf::VertexArray graphLine(sf::LineStrip, instances);
    for (int i = 0; i < instances; i++) {
        float x = static_cast<float>((windowX - 2 * axisMargin) * (outputData(i,0) / tMax)) + axisMargin;
        float y = static_cast<float>((windowY - 2 * axisMargin) * ((yMax - outputData(i, 1)) / (yMax - yMin))) + axisMargin;
        graphLine[i].position = sf::Vector2f(x, y);
        graphLine[i].color = sf::Color::Green;
    }

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
        window.draw(graphLine);
        window.display();
    }
}