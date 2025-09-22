#pragma once

#include "geometry.h"
#include "constants.h"
#include <array>

using Grid = std::array<std::array<char, CANVAS_WIDTH>, CANVAS_HEIGHT>;

class Renderer {
private:
    Grid grid;

public:
    Renderer();

    // Core rendering functions
    void clearGrid();
    void showGrid() const;
    void clearScreen();

    // Rasterization algorithm
    static Point3d project3d(Point3d point);

    void plotPoint(Point3d p, char symbol);

    // Bresenham's algorithm to draw a line
    void drawLine(Point3d v1, Point3d v2);

    // Bounds checking
    static bool isInBounds(int x, int y);
};
