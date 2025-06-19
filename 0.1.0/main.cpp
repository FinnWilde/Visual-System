#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>

using namespace Eigen;

Vector2d ode(double c, double k, double m, double x, double v)
{

    double dxdt = v;
    double dvdt = (-(c * v) - (k * x)) / m;
    
    return Vector2d(dxdt, dvdt);

}

Vector2d rk4(double h, double x, double v, double c, double k, double m)
{   
    Vector2d prev(2);
    prev(0) = x;
    prev(1) = v;
       
    Vector2d k1 = ode(c, k, m, x, v);
    Vector2d k2 = ode(c, k, m, x + h * k1[0] / 2, v + h * k1[1] / 2);
    Vector2d k3 = ode(c, k, m, x + h * k2[0] / 2, v + h * k2[1] / 2);
    Vector2d k4 = ode(c, k, m, x + h * k3[0], v + h * k3[1]);

    return  prev + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);

}

int main() {

    double t = 0;
    double m = 2;
    double c = 5;
    double k = 3;
    double h = 0.1;
    double x0 = 1;
    double v0 = 0;

    t = t + h;
    Vector2d next = rk4(h, x0, v0, c, k, m);
    
    std::cout <<"Time (t): " << t
        << ", Position (x): " << next[0]
        << ", Velocity (v): " << next[1] << std::endl;

    for (int i = 0; i < 200; i++) {

        t = t + h;
        double x = next[0];
        double v = next[1];

        next = rk4(h, x, v, c, k, m);
        
        std::cout << "Time (t): " << t
            << ", Position (x): " << next[0]
            << ", Velocity (v): " << next[1] << std::endl;
    }

  
    return 0;
}









































































































