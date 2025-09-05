#include <iostream>
#include <algorithm>
#include <array>

constexpr int CANVAS_HEIGHT = 40;
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

Cube cube;

Point3d project3d(Point3d point) {
    int screenX = point.x * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_WIDTH / 2;
    int screenY = point.y * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_HEIGHT / 2;
    return {screenX, screenY, point.z*CAMERA_ZOOM};
}

double line(double m, double c, Point3d p) {
    return m*(p.x) - p.y +c ;
}

void drawLineAxis(int x0, int y0, int x1, int y1, double m, double c, bool swapXY) {
    int stepX = (x1 > x0) ? 1 : -1;
    int stepY = (y1 > y0) ? 1 : -1;

    if (y1 == y0) {
        stepY = 0;
    }

    if (y0 == 28 && y1 == 32) {
        std::cout << stepX << ' ' << stepY << '\n';
    }

    int x = x0, y = y0;

    while (x != x1) {
        if (swapXY) {
            if (y >= 0 && y < CANVAS_WIDTH && x >= 0 && x < CANVAS_HEIGHT) {
                grid[x][y] = '#';
            }
        } else {
            if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
                if (y0 == 32 && y1 == 28) {
                    std::cout << y << " " << x << '\n';
                }
                grid[y][x] = '#';
            }
        }

        x += stepX;
        double midpointTest = line(m, c, {x, y, 0}) + 0.5 * stepY;
        if (y0 == 32 && y1 == 28) {
            std::cout << midpointTest << m << '\n';
        }
        if (midpointTest*stepY > 0) {
            y += stepY;
        }
    }
}

void showGrid() {
    for (auto &row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void drawLine(Edge e) {
    Point3d v1, v2;
    v1 = project3d(cube.vertices[e.start]);
    v2 = project3d(cube.vertices[e.end]);

    int deltaX = abs(v1.x - v2.x);
    int deltaY = abs(v1.y - v2.y);

    if (e.start == 2 && e.end == 6) {
        std::cout << v1.x << " " << v1.y << " " << v2.x << " " << v2.y << "\n";
    }

    if (deltaX == 0) {
        int startY = std::min(v1.y, v2.y);
        int endY = std::max(v1.y, v2.y);
        for (int y = startY; y <= endY; y++) {
            if (v1.x >= 0 && v1.x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
                grid[y][v1.x] = '#';
            }
        }
        return;
    }

    double m = static_cast<double>(v1.y - v2.y) / (v1.x - v2.x);
    double c = v1.y - m*v1.x;

    if (deltaX >= deltaY) {

        drawLineAxis(v1.x, v1.y, v2.x, v2.y, m, c, false);
    } else {
        drawLineAxis(v1.y, v1.x, v2.y, v2.x, 1/m, v1.x - (1/m)*v1.y, true);
    }
}

int main() {
    for (auto &row : grid) {
        for (char &cell : row) {
            cell = '.';
        }
    }

    for (auto edge : cube.edges) {
        drawLine(edge);
    }
    grid[31][9]= '#';
    showGrid();
}
