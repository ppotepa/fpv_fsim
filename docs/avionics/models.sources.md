awesome — here are 10 rock-solid, *formula-heavy* sources on flight mechanics & propeller modelling:

1. **Beard & McLain — *Small Unmanned Aircraft: Theory and Practice*** (free WIP PDF from the authors; 6-DOF model, propeller/thrust models, controller-ready). ([GitHub][1])
2. **Anderson — *Aircraft Performance & Design*** (classic; propulsive efficiency, range, climb, prop props). ([School of Aeronautics Neemrana][2])
3. **NASA Glenn “Propeller Thrust” (+ Beginner’s Guide to Aeronautics)** (clear derivations, actuator disk, efficiency). ([NASA GRC][3])
4. **UIUC Propeller Data Site** (measured C\_T, C\_P, η vs J for many APC/others; perfect for validating your model). ([M Selig][4])
5. **Stoll (Stanford) — *Design of Quiet UAV Propellers*** (rigorous theory + BEMT, noise/efficiency trade-offs). ([purl.stanford.edu][5])
6. **MIT OCW 16.333 notes** (aircraft EoM, linearisation; great for state-space). ([MIT OpenCourseWare][6])
7. **Princeton (Stengel) MAE331 Lecture 11 — Aircraft Equations of Motion** (clean inertial/body frames, Euler/quaternions). ([stengel.mycpanel.princeton.edu][7])
8. **Hull — *Fundamentals of Airplane Flight Mechanics*** (accessible derivations of 6-DOF & modes). ([aerostarsolutions.wordpress.com][8])
9. **NPTEL (IIT Bombay) — Propeller Theories / BEMT** (step-by-step blade-element momentum derivation). ([archive.nptel.ac.in][9])
10. **NREL *AeroDyn Theory Manual*** (BEM theory; written for turbines but maths ports to props with sign/convention tweaks). ([docs.nrel.gov][10])

# quick formula crib (C++-style)

## 6-DOF rigid body (body frame B)

```cpp
// States:
Vector3 r_E;          // position in Earth/inertial frame
Vector3 v_B;          // velocity in body frame
Vector3 omega_B;      // angular rates [p,q,r]
Quaternion q_BE;      // attitude (E->B), or Euler [phi,theta,psi]

// Kinematics:
dot(r_E)     = R_BE^T * v_B;                 // R_BE: body->earth rotation
dot(q_BE)    = 0.5 * Omega(omega_B) * q_BE;  // or Euler-rate matrix T(φ,θ,ψ)*omega_B

// Dynamics:
m * dot(v_B)   = F_B - cross(omega_B, m * v_B);                // F_B = F_aero + F_prop + F_grav(B)
I * dot(omega_B) = M_B - cross(omega_B, I * omega_B);          // I: inertia in B
```

(See MIT/Princeton notes for the exact T(φ,θ,ψ) and gravity in body components.) ([MIT OpenCourseWare][6])

## aerodynamics (fixed-wing)

```cpp
q  = 0.5 * rho * V^2;          // dynamic pressure
L  = q * S * C_L(alpha, ...);
D  = q * S * C_D(alpha, ...);
Y  = q * S * C_Y(beta, ...);
Mx = q * S * b * C_l(...);    // roll
My = q * S * c_bar * C_m(...);// pitch
Mz = q * S * b * C_n(...);    // yaw
```

(Use polars from your chosen airfoil; UIUC has low-Re data.) ([M Selig][11])

## propeller performance — non-dimensional

```cpp
J   = V / (n * D);                          // advance ratio (n in rev/s, D in m)
C_T = T / (rho * n*n * D*D*D*D);
C_P = P / (rho * n*n*n * D*D*D*D*D);
eta = J * C_T / C_P;                        // propulsive efficiency
```

(Definitions standard in NASA/UIUC/Anderson.) ([NASA GRC][3])

## actuator-disk (momentum theory, axial flight)

```cpp
// upstream airspeed V_infty, disk area A = pi*R*R
// induced velocity at disk v_i (solve from thrust balance)
T   = 2 * rho * A * v_i * (V_infty + v_i);
P_a = T * (V_infty + v_i);                  // air power added
eta = T * V_infty / P_shaft;                // overall propulsive efficiency
```

(Use this for intuition & estimates.) ([NASA GRC][3])

## blade-element / BEMT (steady, axial)

```cpp
// At radius r with chord c(r), pitch beta(r), B blades, tip speed Ω*r
V_ax   = V_infty * (1 + a);                 // axial induction a
V_tan  = Ω * r * (1 - a_prime);             // swirl induction a'
phi    = atan2(V_ax, V_tan);                // inflow angle
alpha  = beta(r) - phi;                     // section AoA
V_rel2 = V_ax*V_ax + V_tan*V_tan;

dT = 0.5 * rho * V_rel2 * c(r) * [ C_L(alpha)*cos(phi) - C_D(alpha)*sin(phi) ] * B * dr;
dQ = 0.5 * rho * V_rel2 * c(r) * [ C_L(alpha)*sin(phi) + C_D(alpha)*cos(phi) ] * r * B * dr;

T  = integral(dT, r= r_root..R);
Q  = integral(dQ, r= r_root..R);
P  = Ω * Q;
```

(Iterate a, a′ to satisfy momentum theory; good derivations in NPTEL/NREL/Stoll.) ([archive.nptel.ac.in][9])

## coupling to aircraft EoM

```cpp
F_prop_B = { T, 0, 0 };                 // along +x_body if tractor; flip for pusher as needed
M_prop_B = { Q_friction, Q_motor, ... } // include reaction torque about +x and any offset moments
F_total_B = F_aero_B + F_prop_B + F_grav_B;
M_total_B = M_aero_B + M_prop_B + M_ctrl_B;
```

(Placement/gyros: add rotor gyroscopic terms if Ω changes rapidly.)

---

want me to turn this into a tiny C++ (or C#) single-file sim scaffold that plugs in your preferred prop model and UIUC data?

[1]: https://github.com/byu-magicc/mavsim_public?utm_source=chatgpt.com "Small Unmanned Aircraft: Theory and Practice, by Randy ..."
[2]: https://soaneemrana.org/onewebmedia/AIRCRAFT%20PERFORMANCE%20AND%20DESIGN1.pdf?utm_source=chatgpt.com "and design"
[3]: https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/propeller-thrust/?utm_source=chatgpt.com "Propeller Thrust | Glenn Research Center - NASA"
[4]: https://m-selig.ae.illinois.edu/props/propDB.html?utm_source=chatgpt.com "UIUC Propeller Data Site"
[5]: https://purl.stanford.edu/dk871sj7273?utm_source=chatgpt.com "Design of quiet UAV propellers - Stanford Digital Repository"
[6]: https://ocw.mit.edu/courses/16-333-aircraft-stability-and-control-fall-2004/c6eee980ed173de9dde7f4ee453354ee_lecture_4.pdf?utm_source=chatgpt.com "16.333 Lecture 4 Aircraft Dynamics"
[7]: https://stengel.mycpanel.princeton.edu/MAE331Lecture11.pdf?utm_source=chatgpt.com "11. Aircraft Equations of Motion - Flight Path Computation"
[8]: https://aerostarsolutions.wordpress.com/wp-content/uploads/2011/10/fundmentals_of_airplane_flight_mechanics.pdf?utm_source=chatgpt.com "Fundamentals of Airplane Flight Mechanics"
[9]: https://archive.nptel.ac.in/content/storage2/courses/101101001/downloads/Intro-Propulsion-Lect-30.pdf?utm_source=chatgpt.com "Propeller theories Blade element theory"
[10]: https://docs.nrel.gov/docs/fy05osti/36881.pdf?utm_source=chatgpt.com "AeroDyn Theory Manual - Publications - NREL"
[11]: https://m-selig.ae.illinois.edu/?utm_source=chatgpt.com "UIUC Applied Aerodynamics Group"
