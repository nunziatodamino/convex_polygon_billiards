# 🔬 BZ Reaction Simulation in C++

This project explores the spatiotemporal behavior of the **Belousov–Zhabotinsky (BZ) reaction** using two approaches in C++:

1. A **discrete cellular automaton (CA)** to model wave propagation via state transitions.
2. A **continuous reaction-diffusion PDE system** based on the **Oregonator model**, a reduced chemical model of the BZ reaction.

---

## 🧱 Phase 1 — Cellular Automaton Model

In this phase, we simulate the BZ reaction using a **simplified excitation-based cellular automaton** on a 2D grid. Each cell is in one of three states:

- `Resting`
- `Excited`
- `Refractory`

### Update Rules (Example):

1. A `Resting` cell becomes `Excited` if one or more neighbors are `Excited`
2. An `Excited` cell becomes `Refractory`
3. A `Refractory` cell returns to `Resting` after a fixed refractory period

These rules qualitatively replicate the **target waves** and **spiral wave formation** seen in the BZ reaction.

---

## 🌊 Phase 2 — Oregonator Reaction-Diffusion PDE

This phase models the actual **concentration fields** of reacting chemical species using the **Oregonator equations** extended with **diffusion terms**.

### System of PDEs:

Let:
- \( X \): concentration of the activator (e.g., HBrO\(_2\))
- \( Y \): inhibitor (e.g., Br\(^-\))
- \( Z \): oxidized catalyst (e.g., ferroin)

The equations are:

\[
\begin{aligned}
\frac{\partial X}{\partial t} &= \frac{1}{\epsilon} \left( qY - XY + X(1 - X) \right) + D_X \nabla^2 X \\
\frac{\partial Y}{\partial t} &= XY - Y + D_Y \nabla^2 Y \\
\frac{\partial Z}{\partial t} &= f(X - Z) + D_Z \nabla^2 Z
\end{aligned}
\]

Where:
- \( \epsilon, q, f \) are reaction parameters
- \( D_X, D_Y, D_Z \) are diffusion coefficients
- \( \nabla^2 \) is the 2D Laplacian operator, approximated via finite differences

This model captures the **nonlinear kinetics** and **spatial diffusion** leading to rich pattern formation (e.g., rotating spirals).

---

## 🛠 Project Goals

- Visualize the emergence of BZ-like wave patterns
- Compare **qualitative CA rules** vs **quantitative PDE modeling**
- Implement custom 2D solvers and visualizers in modern C++

---

## 📁 Planned Directory Structure

/src
ca/ # Cellular automaton implementation
pde/ # Oregonator PDE simulation
core/ # Shared data structures, grid logic
renderer/ # Visualization (SDL2/SFML)
utils/ # Parameter loading, CLI tools
/plots # Generated visualizations

README.md

---

## 🔧 Technologies

- Language: **C++17**
- Libraries: SDL2 or SFML (planned for visualization)
- Numerical Methods: Euler integration, finite difference Laplacian
- Build System: CMake (planned)

---

## 📚 References

- Field, R. J., & Noyes, R. M. (1974). *Oscillations in chemical systems. IV. Limit cycle behavior in a model of a real chemical reaction*. **J. Chem. Phys., 60**, 1877. [https://doi.org/10.1063/1.1681288](https://doi.org/10.1063/1.1681288)
- Epstein, I. R., & Pojman, J. A. (1998). *An Introduction to Nonlinear Chemical Dynamics: Oscillations, Waves, Patterns, and Chaos*
- Tyson, J. J. (1977). *Oscillations and waves in chemical systems*. Lecture Notes in Biomathematics.

---

## 📌 Status

- [x] Design and prototyping
- [ ] Cellular automaton working version
- [ ] Oregonator PDE solver
- [ ] Visualization
- [ ] Parameter tuning and animations

---

## 🚀 License

This project is for personal, educational, and experimental purposes. No license specified yet.

