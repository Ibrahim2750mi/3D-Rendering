#pragma once

#include "geometry.h"

// Canvas/Display
constexpr int CANVAS_HEIGHT = 60;
constexpr int CANVAS_WIDTH = 60;

// Camera/Projection
constexpr int CAMERA_Z_DEPTH = 5;
constexpr int CAMERA_ZOOM = 6;

// Animation
constexpr int FRAME_DELAY_US = 8333;  // ~60 FPS
constexpr double ROTATION_SPEED = 0.05;

// Torus parameters
constexpr double TORUS_MAJOR_RADIUS = 2.0;
constexpr double TORUS_MINOR_RADIUS = 1.0;
constexpr int TORUS_PHI_STEPS = 20;
constexpr int TORUS_THETA_STEPS = 30;

// Cube parameters
constexpr double CUBE_SIZE = 1.0;

// Light source
const Point3d LIGHT_SOURCE = {0, 0, -1};
