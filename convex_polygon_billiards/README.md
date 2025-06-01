# Convex Polygon Billiards

**Convex Polygon Billiards** is a C++ simulation project that models the motion of particles within a convex polygonal boundary using reflective (billiard-style) boundary conditions. The simulation is designed to be interactive and modular, allowing for experimentation with different polygon shapes and particle counts.

---

## 📐 Project Overview

The simulation operates in two phases:

1. **Initialization**
   - User selects the number of sides `N` (3 ≤ N ≤ 12).
   - A convex polygon with `N` vertices is generated (initially regular).
   - User selects the number of particles `M` (1 ≤ M ≤ 100).
   - Particles are initialized with random positions inside the polygon and random velocities.

2. **Simulation**
   - Particles move linearly within the polygon.
   - When a particle hits a polygon edge, it reflects according to the law of reflection (angle of incidence = angle of reflection).
   - Simulation steps are updated over time, possibly visualized with a graphics library (TBD).

---

## ✅ Feature Checklist

- [ ] User-defined polygon with 3–12 sides
- [ ] Random generation of regular convex polygon
- [ ] User-defined number of particles (1–100)
- [ ] Random initialization of particle positions and velocities
- [ ] Reflective boundary conditions on polygon edges
- [ ] Time-stepped simulation loop
- [ ] Collision detection with polygon edges
- [ ] Simple visualization (e.g., using ASCII or graphics library)
- [ ] Particle trajectory tracking
- [ ] Export of simulation data or frames
- [ ] Real-time interaction (pause/resume/speed control)

---

## 🧱 Key Components (Planned)

### 1. `Polygon` Class
- Stores vertices of the polygon
- Provides methods for:
  - Edge detection
  - Point-in-polygon checks
  - Computing reflection normals

### 2. `Particle` Class
- Position (`x, y`)
- Velocity vector (`vx, vy`)
- Update method to compute motion
- Collision handling with polygon edges

### 3. `Simulation` Class
- Manages the list of particles and polygon
- Handles the main loop:
  - Position updates
  - Collision checks
  - Time stepping

---

## 🎮 User Input

```
Enter number of polygon sides (3–12): 7
Enter number of particles (1–100): 25
```

Initial conditions are generated and the simulation begins.

---

## 🧪 Implementation Notes

- Initial polygon is regular (equal side lengths and angles)
- Particles start with random direction and fixed speed
- Reflective boundaries follow geometric laws (mirror-like reflection)
- Time-stepping uses a fixed delta `dt`

---

## 🎨 Visualization (Optional / Planned)

- Use SFML, SDL2, or OpenGL for 2D rendering
- Display particle trails
- Color particles by velocity or time

---

## 🛠️ Build System

- CMake-based build setup (recommended)
- Standard C++17 or newer
- Cross-platform (Linux, Windows, macOS)

---

## 🚧 Future Design Considerations

- Support for arbitrary convex polygons (non-regular)
- Particle-particle collisions
- Exporting trajectories to file
- Real-time controls (pause, speed up, reset)

---

## 🧾 License

This project is in early development. Licensing will be added upon release.
