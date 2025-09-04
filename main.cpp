#include <iostream>
#include <array>

constexpr int CANVAS_HEIGHT = 30;
constexpr int CANVAS_WIDTH = 40;

constexpr int CAMERA_Z_DEPTH = 5;
constexpr int CAMERA_ZOOM = 10;

std::array<std::array<char, CANVAS_WIDTH>, CANVAS_HEIGHT> grid;


struct Point3d {
    int x,y,z;
};

struct Edge {
    int start,end;
};

struct Cube {
    std::array<Point3d, 8> vertices{{
        {-1, -1, -1},  // 0: back bottom-left
        { 1, -1, -1},  // 1: back bottom-right
        { 1,  1, -1},  // 2: back top-right
        {-1,  1, -1},  // 3: back top-left
        {-1, -1,  1},  // 4: front bottom-left
        { 1, -1,  1},  // 5: front bottom-right
        { 1,  1,  1},  // 6: front top-right
        {-1,  1,  1}   // 7: front top-left
    }};

    std::array<Edge, 12> edges{{
        // Back face (z = -1) - vertices 0,1,2,3
        {0, 1}, {1, 2}, {2, 3}, {3, 0},

        // Front face (z = +1) - vertices 4,5,6,7
        {4, 5}, {5, 6}, {6, 7}, {7, 4},

        // Connecting back to front
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    }};
};

Point3d project3d(Point3d point) {
    int screenX = point.x * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_WIDTH / 2;
    int screenY = point.y * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_HEIGHT / 2;
    return {screenX, screenY, point.z*CAMERA_ZOOM};
}

void showGrid() {
    for (auto &row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    for (auto &row : grid) {
        for (char &cell : row) {
            cell = '.';
        }
    }

    for (auto point : cube.vertices) {
        Point3d pointProjected = project3d(point);
        grid[pointProjected.y][pointProjected.x] = '#';
    }
    showGrid();
}
