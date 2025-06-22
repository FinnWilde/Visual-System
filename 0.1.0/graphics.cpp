#include "graphics.hpp"

void renderGraphics(double xMax, double xMin, double instances, double tMax, Eigen::MatrixXd& outputData) { 

    float yMax = static_cast<float>(xMax); //note xMax from ODE is now yMax - switching from t,x axis to x,y for graphics
    float yMin = static_cast<float>(xMin);

    

    sf::Vector2f windowFrame(800.f, 600.f); //window size
    sf::Vector2f margin(50.f, 50.f); //margin between graph and window
    sf::Vector2f graphFrame = windowFrame - (margin * 2.0f);
    float axisWidth = 1.f;
    float gridlineLength = 10.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Try 4 or 8 for good quality
    sf::RenderWindow window(sf::VideoMode(windowFrame.x,windowFrame.y), "Anti-Aliased Window", sf::Style::Default, settings);
    
    
    if (yMin >= 0) { //want to still render to 0 even if all data is above/below 0
        yMin = 0;
    }
    else if (yMax <= 0) {
        yMax = 0;
    }

    //Set X Scale
    float xScale = setScale(tMax, 17.f);
    float gridDivisionsRight = std::ceil(tMax / xScale); //find number of vertical gridlines

    //Set Y Scale
    float deltaY = yMax - yMin;
    float yScale = setScale(deltaY, 12.f);
    float gridDivisionsAbove = std::ceil(yMax / yScale); //find number of horizontal gridlines
    float gridDivisionsBelow = std::floor(yMin / yScale);

    //speacial cases - gives graph some space at the limits (but not if the limit is 0)
    if (yMax == yScale * gridDivisionsAbove && gridDivisionsAbove != 0) { 
        gridDivisionsAbove += 1;
    }
    if (yMin == yScale * gridDivisionsBelow && gridDivisionsBelow != 0) {
        gridDivisionsBelow -= 1;
    }

    //Define Axis size, position
    //              Graphing Frame Height                              Ratio                                  Offset
    float xAxisHeight = (graphFrame.y) * ((gridDivisionsAbove) / (gridDivisionsAbove - gridDivisionsBelow)) + margin.y;
   
    sf::RectangleShape xAxis(sf::Vector2f(graphFrame.x, axisWidth));
    xAxis.setPosition(margin.x, xAxisHeight - axisWidth/2);
    xAxis.setFillColor(sf::Color::White);

    sf::RectangleShape yAxis(sf::Vector2f(axisWidth, graphFrame.y));
    yAxis.setPosition(margin.x - axisWidth / 2, margin.y);
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

        window.draw(graphLine);

        window.draw(xAxis);
        window.draw(yAxis);

        
    
        for (int i = 0; i <= gridDivisionsAbove; i++) {
            sf::RectangleShape horizontalGridline(sf::Vector2f(gridlineLength / 2, axisWidth));
            horizontalGridline.setPosition(margin.x, xAxisHeight - (i * (graphFrame.y) / (gridDivisionsAbove - gridDivisionsBelow)));
            horizontalGridline.setFillColor(sf::Color::White);
            window.draw(horizontalGridline);
        }
        for (int j = 0; j <= std::abs(gridDivisionsBelow); j++) {
            sf::RectangleShape horizontalGridline(sf::Vector2f(gridlineLength / 2, axisWidth));
            horizontalGridline.setPosition(margin.x, xAxisHeight + (j * (graphFrame.y) / (gridDivisionsAbove - gridDivisionsBelow)));
            horizontalGridline.setFillColor(sf::Color::White);
            window.draw(horizontalGridline);
        }
        for (int k = 0; k <= std::abs(gridDivisionsRight); k++) {
            sf::RectangleShape verticalGridline(sf::Vector2f(axisWidth, gridlineLength));
            verticalGridline.setPosition(margin.x - axisWidth / 2 + (k * graphFrame.x) / gridDivisionsRight, xAxisHeight - gridlineLength/2);
            verticalGridline.setFillColor(sf::Color::White);
            window.draw(verticalGridline);
        }

        
        window.display();
    }
}

float setScale(float delta, float idealDivs) {
 
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