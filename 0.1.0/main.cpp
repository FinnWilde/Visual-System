#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>

using namespace Eigen;

class HarmonicOscillator {
public:
    HarmonicOscillator(double mass, double damping, double stiffness)
        : m(mass), c(damping), k(stiffness) {}

    Vector2d ode(const Vector2d& state) const {
        double x = state[0];
        double v = state[1];
        return Vector2d(v, (-c * v - k * x) / m); //row 0 = dx/dt, row 1 = dv/dt
    }

    Vector2d rk4(double h, const Vector2d& state) const {
        Vector2d k1 = ode(state);
        Vector2d k2 = ode(state + (h / 2) * k1);
        Vector2d k3 = ode(state + (h / 2) * k2);
        Vector2d k4 = ode(state + h * k3);
        return state + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }

private:
    double m; // Mass
    double c; // Damping coefficient
    double k; // Stiffness
};

int main() {
    double t = 0;
    double h = 0.01;
    Vector2d state(2, 0); // Initial state: [x0, v0]

    // Initialize oscillator with constants
    HarmonicOscillator oscillator(2.0, 0, 3.0);

    // First step
    t += h;
    state = oscillator.rk4(h, state);
    std::cout << "Time (t): " << t << ", Position (x): " << state[0]
        << ", Velocity (v): " << state[1] << std::endl;

    // Subsequent steps
    for (int i = 0; i < 2000; i++) {
        t += h;
        state = oscillator.rk4(h, state);
        std::cout << "Time (t): " << t << ", Position (x): " << state[0]
            << ", Velocity (v): " << state[1] << std::endl;
    }

    return 0;
}