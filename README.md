# Visual System

In it's current version, Visual System is simply a second order ODE solver and grapher.

Enter any second order ODE in form:
$a(t)\ddot{x} + b(t, x, \dot{x}) = u(t)$

The program is also set up to accept a plant function, reference function, Kp, Ki and Kd values for PID control. The reference line will be displayed in blue, with the feedback line displayed in green. 

## Examples:

### Mass Spring Damper (Free Response, No Control)


Plant: $2\ddot{x} + 3\dot{x} + 5x = 0$

Initial Conditions:
$x_0 = 6\text{ m}, \quad v_0 = 0\text{ ms}^{-1}$

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/898a4425-5335-433f-bb7f-89516b2fba3a" />

### Pendulum System with Damping (Free Response, No Control)
*Note x now represents pendulum angle from vertical, in radians.

Plant: $\ddot{x} + \dot{x} + 9.81\text{sin(x)} = 0$

Initial Conditions:
$x_0 = 3.1415\text{ rad}, \quad v_0 = 0\text{ rad s}^{-1}$

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/87194eba-d8cd-4c39-a89e-b4d7b630bf2c" />

