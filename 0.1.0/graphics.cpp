#include "graphics.hpp"

void renderGraphics(double xMax, double xMin, double instances, double tMax, Eigen::MatrixXd& outputData) { //note xMax from ODE is now yMax - switching from t,x axis to x,y for graphics

    float yMax = static_cast<float>(xMax);
    float yMin = static_cast<float>(xMin);

    

    sf::Vector2f windowFrame(800.f, 600.f);
    sf::Vector2f margin(50.f, 50.f);
    sf::Vector2f graphFrame = windowFrame - (margin * 2.0f);

    sf::RenderWindow window(sf::VideoMode(windowFrame.x, windowFrame.y), "Distance (m) against Time (s)"); //create the window

    float axisWidth = 1;
    
   
    if (yMin >= 0) {
        yMin = 0;
    }
    else if (yMax <= 0) {
        yMax = 0;
    }

    //Set X Scale
    float xScale = setYScale(tMax);

    float gridDivisionsRight = std::ceil(tMax / xScale);

    //Set Y Scale
    float deltaY = yMax - yMin;
    float yScale = setYScale(deltaY);

    float gridDivisionsAbove = std::ceil(yMax / yScale);
    float gridDivisionsBelow = std::floor(yMin / yScale);

    if (yMax == yScale * gridDivisionsAbove && gridDivisionsAbove != 0) {
        gridDivisionsAbove += 1;
    }
    if (yMin == yScale * gridDivisionsBelow && gridDivisionsBelow != 0) {
        gridDivisionsBelow += 1;
    }


    //Define Axis
    //              Graphing Frame Height                              Ratio                                           Offset
    float xAxisHeight = (graphFrame.y) * ((gridDivisionsAbove) / (gridDivisionsAbove - gridDivisionsBelow)) + margin.y - axisWidth / 2;
   
    sf::RectangleShape xAxis(sf::Vector2f(1.01 * (graphFrame.x), axisWidth)); //1.01 so it sticks out slightly on  the left
    xAxis.setPosition(margin.x - 0.01 * (graphFrame.x), xAxisHeight);
    xAxis.setFillColor(sf::Color::White);

    sf::RectangleShape yAxis(sf::Vector2f(axisWidth, graphFrame.y)); 
    yAxis.setPosition(margin.x, margin.y);
    yAxis.setFillColor(sf::Color::White);

   
    std::cout << "XScale: " << xScale << std::endl;
    std::cout << "YScale: " << yScale << std::endl;

    std::cout << "Above Divs: " << gridDivisionsAbove << std::endl;
    std::cout << "Below Divs: " << gridDivisionsBelow << std::endl;
    std::cout << "Right Divs: " << gridDivisionsRight << std::endl;

    float yMaxGraph = gridDivisionsAbove * yScale;
    float yMinGraph = gridDivisionsBelow * yScale;

    sf::VertexArray graphLine(sf::LineStrip, instances);
    for (int i = 0; i < instances; i++) {
        //                               Ratio                   Offset
        float x = ((graphFrame.x) * (outputData(i,0) / tMax)) + margin.x;
        float y = ((graphFrame.y) * ((yMaxGraph - outputData(i, 1)) / (yMaxGraph - yMinGraph))) + margin.y;
        graphLine[i].position = sf::Vector2f(x, y);
        graphLine[i].color = sf::Color(90, 224, 94);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(33, 33, 33));

        window.draw(xAxis);
        window.draw(yAxis);

        
        for (int i = 1; i <= gridDivisionsAbove; i++) {
            sf::RectangleShape horizontalGridline(sf::Vector2f(0.02*(graphFrame.x), axisWidth));
            horizontalGridline.setPosition(margin.x - 0.01 * (graphFrame.x), xAxisHeight - (i * (graphFrame.y) / (gridDivisionsAbove - gridDivisionsBelow)));
            horizontalGridline.setFillColor(sf::Color::White);
            window.draw(horizontalGridline);
        }
        for (int j = 1; j <= std::abs(gridDivisionsBelow); j++) {
            sf::RectangleShape horizontalGridline(sf::Vector2f(0.02 * (graphFrame.x), axisWidth));
            horizontalGridline.setPosition(margin.x - 0.01 * (graphFrame.x), xAxisHeight + (j * (graphFrame.y) / (gridDivisionsAbove - gridDivisionsBelow)));
            horizontalGridline.setFillColor(sf::Color::White);
            window.draw(horizontalGridline);
        }
        for (int k = 1; k <= std::abs(gridDivisionsRight); k++) {
            sf::RectangleShape verticalGridline(sf::Vector2f(axisWidth, 0.02 * (graphFrame.x)));
            verticalGridline.setPosition(margin.x + (k * graphFrame.x) / gridDivisionsRight, xAxisHeight - 0.01 * (graphFrame.x));
            verticalGridline.setFillColor(sf::Color::White);
            window.draw(verticalGridline);
        }


        window.draw(graphLine);
        window.display();
    }
}

float setYScale(float delta) {
    float idealDivs = 10;
    float exactPowerOne = log10(delta / idealDivs);
    float powerOne = std::round(exactPowerOne);
    float marginOne = std::abs(exactPowerOne - powerOne);

    float exactPowerFive = log10(delta / (5* idealDivs));
    float powerFive = std::round(exactPowerFive);
    float marginFive = std::abs(exactPowerFive - powerFive);

    float scale = std::pow(10, powerOne);

    if (marginFive < marginOne) {
        scale = 5 * std::pow(10, powerFive);   
    }
    
  

    return scale;
}