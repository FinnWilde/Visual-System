#include "graphics.hpp"

int renderGraphics(double xMax, double xMin, double instances, double tMax, Eigen::MatrixXd& outputData) { 

    float yMax = static_cast<float>(xMax); //note xMax from ODE is now yMax - switching from t,x axis to x,y for graphics
    float yMin = static_cast<float>(xMin);

    

    sf::Vector2f windowFrame(800.f, 600.f); //window size
    sf::Vector2f margin(70.f, 50.f); //margin between graph and window
    sf::Vector2f graphFrame = windowFrame - (margin * 2.0f);
    float axisWidth = 1.f;
    float gridlineLength = 10.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Try 4 or 8 for good quality
    sf::RenderWindow window(sf::VideoMode(windowFrame.x,windowFrame.y), "Anti-Aliased Window", sf::Style::Default, settings);
    
    sf::Font sansRoman;
    if (!sansRoman.loadFromFile("Fonts/cmunrm.ttf")) {
        // Handle error if the font fails to load
        return 1;
        std::cout << "oof" << std::endl;
    }
    
    sf::Font italic;
    if (!italic.loadFromFile("Fonts/cmunti.ttf")) {
        // Handle error if the font fails to load
        return 1;
        std::cout << "oof" << std::endl;
    }

  

    
    if (yMin >= 0) { //want to still render to 0 even if all data is above/below 0
        yMin = 0;
    }
    else if (yMax <= 0) {
        yMax = 0;
    }

    //Set X Scale
    float xScale = setScale(tMax, 10.f);
    float gridDivisionsRight = std::ceil(tMax / xScale); //find number of vertical gridlines

    //Set Y Scale
    float deltaY = yMax - yMin;
    float yScale = setScale(deltaY, 8.f);
    float gridDivisionsAbove = std::ceil(yMax / yScale); //find number of horizontal gridlines
    float gridDivisionsBelow = std::floor(yMin / yScale);

    //speacial cases - gives graph some space at the limits (but not if the limit is 0)
    if (yMax >= 0.99 * yScale * gridDivisionsAbove && gridDivisionsAbove != 0) { 
        gridDivisionsAbove += 1;
    }
    if (yMin <= 0.99 * yScale * gridDivisionsBelow && gridDivisionsBelow != 0) {
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

    sf::Text xLabel("t", italic, 28);
    setOriginToCentre(xLabel);
    xLabel.setFillColor(sf::Color::White);
    xLabel.setPosition(margin.x + graphFrame.x + 15, xAxisHeight - axisWidth / 2  - 15);

    sf::Text yLabel("x", italic, 28);
    setOriginToCentre(yLabel);
    yLabel.setFillColor(sf::Color::White);
    yLabel.setPosition(margin.x + 15, margin.y - 15);

    sf::Text zero("0", sansRoman, 16);
    setOriginToCentre(zero);
    zero.setFillColor(sf::Color::White);
    zero.setPosition(margin.x - 10, xAxisHeight - axisWidth/2);

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

        window.draw(xLabel);
        window.draw(yLabel);
        window.draw(zero);
        
        drawGridlines(window, gridlineLength / 2, axisWidth, margin.x, xAxisHeight, 0.f, -graphFrame.y / (gridDivisionsAbove - gridDivisionsBelow), gridDivisionsAbove); //horizontal (above xAxis)
        drawGridlines(window, gridlineLength / 2, axisWidth, margin.x, xAxisHeight, 0.f, graphFrame.y / (gridDivisionsAbove - gridDivisionsBelow), std::abs(gridDivisionsBelow)); //horizontal (below xAxis)
        drawGridlines(window, axisWidth, gridlineLength, margin.x - axisWidth / 2, xAxisHeight - gridlineLength / 2, graphFrame.x / gridDivisionsRight, 0.f, gridDivisionsRight); //vertical

        

        drawXLabels(window, sansRoman, margin.x, xAxisHeight + gridlineLength / 2, 2 * graphFrame.x / (gridDivisionsRight), std::floor(gridDivisionsRight / 2), xScale); //horizontal (above xAxis)
        drawYLabels(window, sansRoman, margin.x, xAxisHeight, -2 * graphFrame.y / (gridDivisionsAbove - gridDivisionsBelow), std::floor(gridDivisionsAbove / 2), yScale, 1); //horizontal (above xAxis)
        drawYLabels(window, sansRoman, margin.x, xAxisHeight, 2 * graphFrame.y / (gridDivisionsAbove - gridDivisionsBelow), std::abs(std::ceil(gridDivisionsBelow / 2)), yScale, -1); //horizontal (above xAxis)
      


        window.display();
    }
}

void setOriginToCentre(sf::Text &text) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f
    );
}

float setScale(float delta, float idealDivs) {
 
    float exactPowerOne = log10(delta / idealDivs);
    float powerOne = std::round(exactPowerOne);
    float marginOne = std::abs(exactPowerOne - powerOne);

    float exactPowerFiveByTwo = log10(delta / (2.5 * idealDivs));
    float powerFiveByTwo = std::round(exactPowerFiveByTwo);
    float marginFiveByTwo = std::abs(exactPowerFiveByTwo - powerFiveByTwo);

    float exactPowerFive = log10(delta / (5* idealDivs));
    float powerFive = std::round(exactPowerFive);
    float marginFive = std::abs(exactPowerFive - powerFive);

    float scale = std::pow(10, powerOne);

    if (marginFiveByTwo < marginOne) {
        scale = 2.5 * std::pow(10, powerFiveByTwo);   
    }
    if (marginFive < marginFiveByTwo && marginFive < marginOne) {
        scale = 5 * std::pow(10, powerFive);
    }
    
    return scale;
}

void drawGridlines(sf::RenderWindow& window, float xLength, float yLength, float xStartPosition, float yStartPosition, float xStep, float yStep, float numOfGridlines) {
    for (int i = 1; i <= numOfGridlines; i++) {
        sf::RectangleShape gridline(sf::Vector2f(xLength, yLength));
        gridline.setPosition(xStartPosition + i * xStep, yStartPosition + i * yStep);
        gridline.setFillColor(sf::Color::White);
        window.draw(gridline);
    }
}

void drawXLabels(sf::RenderWindow& window, sf::Font font, float xPosition, float yPosition, float xStep, float numOfLabels, float scale) {
    for (int i = 1; i <= numOfLabels; i++) {
        std::ostringstream oss;
        oss << std::setprecision(2) << 2 * i * scale;
        sf::Text label(oss.str(), font, 16);

   
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(
            textBounds.left + textBounds.width / 2.f,
            textBounds.top
        );

        label.setPosition(xPosition + i * xStep, yPosition + 5);
        label.setFillColor(sf::Color::White);
        window.draw(label);
    }
}

void drawYLabels(sf::RenderWindow& window, sf::Font font, float xPosition, float yPosition, float yStep, float numOfLabels, float scale, float multiplyer) {
    for (int i = 1; i <= numOfLabels; i++) {
        std::ostringstream oss;
        oss << std::setprecision(1) << 2 * i * scale * multiplyer;
        sf::Text label(oss.str(), font, 16);
        
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(
            textBounds.left + textBounds.width,
            textBounds.top + textBounds.height / 2.f
        );

        label.setPosition(xPosition - 5, yPosition + i * yStep);
        label.setFillColor(sf::Color::White);
        window.draw(label);
    }
}