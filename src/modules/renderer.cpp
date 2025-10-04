#include "../../include/renderer.h"
#include <cstdlib>
#include <iostream>

Renderer::Renderer() {
    clearGrid();
}

void Renderer::clearGrid() {
    for (auto &row : grid) {
        for (char &cell : row) {
            cell = ' ';
        }
    }
}

void Renderer::showGrid() const {
    for (auto &row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void Renderer::clearScreen() {
    // On windows change this to cls
    system("clear");
    clearGrid();
}

Point3d Renderer::project3d(const Point3d point) {
    double screenX = point.x * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_WIDTH / 2;
    double screenY = point.y * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_HEIGHT / 2;
    return Point3d(screenX, screenY, point.z * CAMERA_ZOOM);
}

void Renderer::plotPoint(Point3d p, char symbol) {
    p = project3d(p);
    if (isInBounds(p.x, p.y)) {
        grid[p.y][p.x] = symbol;
    }
}

bool Renderer::isInBounds(int x, int y) {
    return x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT;
}

void Renderer::drawLine(Point3d v1, Point3d v2) {

    float deltaX = v2.x - v1.x;
    float deltaY = v2.y - v1.y;

    // Find the number of steps (the larger of the two deltas)
    float steps = std::max(abs(deltaX), abs(deltaY));

    // If both points are the same, just draw one point
    if (steps == 0) {
        if (v1.x >= 0 && v1.x < CANVAS_WIDTH && v1.y >= 0 && v1.y < CANVAS_HEIGHT) {
            grid[static_cast<int>(v1.y)][static_cast<int>(v1.x)] = '#';
        }
        return;
    }

    // Step along the line
    for (int i = 0; i <= steps; i++) {
        // Interpolate between v1 and v2
        int x = v1.x + (i * deltaX) / steps;
        int y = v1.y + (i * deltaY) / steps;

        // Bounds checking
        if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
            grid[y][x] = '#';
        }
    }
}
