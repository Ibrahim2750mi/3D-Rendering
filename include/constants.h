#pragma once

// Canvas/Display
constexpr int CANVAS_HEIGHT = 40;
constexpr int CANVAS_WIDTH = 40;

// Camera/Projection
constexpr int CAMERA_Z_DEPTH = 5;
constexpr int CAMERA_ZOOM = 10;

// Animation
constexpr int FRAME_DELAY_US = 16666;  // ~60 FPS
constexpr double ROTATION_SPEED = 0.05;

// Torus parameters
constexpr double TORUS_MAJOR_RADIUS = 2.0;
constexpr double TORUS_MINOR_RADIUS = 1.0;
constexpr int TORUS_PHI_STEPS = 10;
constexpr int TORUS_THETA_STEPS = 15;

// Cube parameters
constexpr double CUBE_SIZE = 1.0;
