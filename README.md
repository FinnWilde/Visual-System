# Visual System

In its current version, Visual System is simply a second order ODE solver and grapher.

Enter any second order ODE in form:
$a(t)\ddot{x} + b(t, x, \dot{x}) = u(t)$

The program is also set up to accept a plant function, reference function, $K_p$, $K_i$ and $K_d$ values for PID control. The reference line will be displayed in blue, with the feedback line displayed in green. 

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

### Pendulum System with Damping (Attempting to Balance Upright with PID Control)

Plant: $\ddot{x} + \dot{x} + 9.81\text{sin}(x) = u$

Initial Conditions:
$x_0 = 0\text{ rad}, \quad v_0 = 0\text{ rad s}^{-1}$

Controller:
$K_p = 40, \quad K_i = 27, \quad K_d = 8$

Reference:
$r(x) = π$

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/de8318e9-9845-4f5c-a58c-f0451262567b" />

### Linear Second Order (Attempting to Force Oscillation with PID)


Plant: $2\ddot{x} + 3\dot{x} + 5x = u$

Initial Conditions:
$x_0 = 0\text{ m}, \quad v_0 = 0\text{ ms}^{-1}$

Controller:
$K_p = 50, \quad K_i = 50, \quad K_d = 15$

Reference:
$r(t) = 0.5\text{sin}(t) + 10$

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/5051faa9-7c05-4563-9fd0-d963bef45ce6" />

### Linear Second Order (Attempting to Force Oscillation with PID, with Disturbances and Saturation Limits)


Plant: $2\ddot{x} + 3\dot{x} + 5x = u + d$

Initial Conditions:
$x_0 = 0\text{ m}, \quad v_0 = 0\text{ ms}^{-1}$

Controller:
$K_p = 50, \quad K_i = 50, \quad K_d = 15$

Reference:
$r(t) = 0.5\text{sin}(t) + 10$

Disturbance:
$d(t) = 5 + 20\text{sin}(0.3πt) + 40 e^{-0.5 (t - 12)^2}$

Saturation Limits:
$F_{max} = 100\text{ N}, \quad F_{min} = -100\text{ N}$

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/90c53bf3-35c4-40d2-8258-ea6408d9a472" />

## How does it Work?

VisualSystem uses an rk4 solver, the 4th order of the runge-kutta series of numerical solvers. For rk4 solvers to work, they require a first order ODE in form $\dot{x} = f(x,t)$
This means the general form of the second order ODE must be rearranged into two first order ODEs of the required form:

$a(t)\ddot{x} + b(t, \dot{x}, x) = u(t)$

becomes:

$\dot{v} = (u(t) - b(t,v,x))/a(t)$

and

$\dot{x} = v$

<br>

For free responses, the program then combines these two first order equations into one state vector derivative: 

$\dot{y} = \[\dot{v} , \dot{x}\]$

which can be input into the rk4 solver, along with initial state vector $y_0 = \[v_0 , x_0\]$ and a time step $h$, to find an approximate next state vector $y_{n+1}$. This process iterates until the desired time has elapsed.

<br>

For PID controlled responses, $u(t) = K_pe(t) + K_iE(t) + K_d\dot{e}(t)$

where:

$e(t)$ is the error at any given time, i.e the difference between the output value and the reference value: $e(t) = r(t) - x(t)$,

$E(t)$ is the integral of that error with respect to time,

$\dot{e}(t)$ is the differential of that error with respect to time

$e(t)$ and $\dot{e}(t)$ can be easily calculated (because we already know $x$ and $\dot{x}$ at any moment, and $r$ and $\dot{r}$ are already known), however, we need a third column in our state vector to find $E(t)$. 

The derivative state vector now comprises:

$\dot{v} = (u(t) - b(t,v,x))/a(t)$

$\dot{x} = v$

$\dot{E} = r - x$

Now the new derivative state vector is input into the rk4 solver with the initial state vector (now  $y_0 = \[v_0 , x_0, E_0\]$), and finds the next approximate state vector $y_{n+1}$. 

<br>

The feedback values are stored in a large matrix, alongside the reference values, and this data is sent to the SFML grapher, along with the maximum and minimum values (so the grapher can calculate the scale).


