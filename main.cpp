#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <unistd.h>
#include <cmath>

constexpr int CANVAS_HEIGHT = 60;
constexpr int CANVAS_WIDTH = 60;

constexpr int CAMERA_Z_DEPTH = 5;
constexpr int CAMERA_ZOOM = 8;

std::array<std::array<char, CANVAS_WIDTH>, CANVAS_HEIGHT> grid;


struct Point3d {
    double x,y,z;
};

struct Edge {
    int start,end;
};



struct Torus {
    double R = 2.0;  // Major radius (donut thickness)
    double r = 1.0;  // Minor radius (tube thickness)

    std::vector<Point3d> vertices;
    std::vector<Edge> edges;

    double angleX = 0.0, angleY = 0.0, angleZ = 0.0;

    void generateVertices() {
        vertices.clear();
        edges.clear();

        int phi_steps = 12;    // Around the tube
        int theta_steps = 18;  // Around the major circle

        // Generate vertices using parametric equations
        for (int i = 0; i < phi_steps; i++) {
            for (int j = 0; j < theta_steps; j++) {
                double phi = 2.0 * M_PI * i / phi_steps;     // 0 to 2π
                double theta = 2.0 * M_PI * j / theta_steps; // 0 to 2π

                double x = (R + r * cos(phi)) * cos(theta);
                double y = (R + r * cos(phi)) * sin(theta);
                double z = r * sin(phi);

                vertices.push_back({x, y, z});
            }
        }

        // Generate edges to connect nearby vertices
        for (int i = 0; i < phi_steps; i++) {
            for (int j = 0; j < theta_steps; j++) {
                int current = i * theta_steps + j;
                int next_phi = ((i + 1) % phi_steps) * theta_steps + j;
                int next_theta = i * theta_steps + ((j + 1) % theta_steps);

                edges.push_back({current, next_phi});    // Connect along phi
                edges.push_back({current, next_theta});  // Connect along theta
            }
        }
    }
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

    double angleY = 0.0;
    double angleX = 0.0;
    double angleZ = 0.0;
};

Cube cube;

Point3d project3d(Point3d point) {
    double screenX = point.x * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_WIDTH / 2;
    double screenY = point.y * CAMERA_Z_DEPTH * CAMERA_ZOOM / (point.z + CAMERA_Z_DEPTH) + CANVAS_HEIGHT / 2;
    return {screenX, screenY, point.z*CAMERA_ZOOM};
}


void drawLine(Edge e) {
    Point3d v1 = project3d(cube.vertices[e.start]);
    Point3d v2 = project3d(cube.vertices[e.end]);

    int deltaX = v2.x - v1.x;  // Note: v2 - v1, not v1 - v2
    int deltaY = v2.y - v1.y;

    // Find the number of steps (the larger of the two deltas)
    int steps = std::max(abs(deltaX), abs(deltaY));

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

void showGrid() {
    for (auto &row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void clearScreen() {
    system("clear");
    for (auto &row : grid) {
        for (char &cell : row) {
            cell = ' ';
        }
    }
}

Point3d rotateX(Point3d p, double angle) {
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    return {p.x,
            (p.y * cos_a - p.z * sin_a),
            (p.y * sin_a + p.z * cos_a)};
}

Point3d rotateY(Point3d p, double angle) {
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    return {(p.x * cos_a + p.z * sin_a),
            p.y,
            (-p.x * sin_a + p.z * cos_a)};
}

Point3d rotateZ(Point3d p, double angle) {
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    return {(p.x * cos_a - p.y * sin_a),
            (p.x * sin_a + p.y * cos_a),
            p.z};
}


[[noreturn]] int main(){

    // std::array<Point3d, 8> baseVertices = cube.vertices;
    Torus torus;

    // In main(), before the loop:
    torus.generateVertices();
    std::vector<Point3d> baseVertices = torus.vertices;
    while (true) {
        clearScreen();
        // cube.angleY += 0.05;
        // cube.angleX += 0.05;
        // cube.angleZ += 0.05;

        torus.angleX += 0.1;
        torus.angleY += 0.1;
        torus.angleZ += 0.1;
        // Rotate vertices
        for (size_t i = 0; i < torus.vertices.size(); i++) {
            torus.vertices[i] = rotateZ(rotateY(rotateX(baseVertices[i], torus.angleX), torus.angleY), torus.angleZ);
        }

        // Draw edges
        // for (auto edge : torus.edges) {
        //     drawLine(edge);  // Use your existing drawLine function
        // }

        for (auto vertex: baseVertices) {
            vertex = rotateZ(rotateY(rotateX(vertex, torus.angleX), torus.angleY), torus.angleZ);
            vertex = project3d(vertex);
            grid[static_cast<int>(vertex.y)][static_cast<int>(vertex.x)] = '#';
        }

        // recompute rotated vertices
        // for (int i = 0; i < 8; i++) {
            // cube.vertices[i] = rotateZ(rotateX(rotateY(baseVertices[i], cube.angleY), cube.angleX), cube.angleZ);
        // }
        //
        // for (auto edge : cube.edges) {
        //     drawLine(edge);
        // }
        // cube.angleY += 0.01;
        // for (auto vertex: baseVertices) {
        //     // vertex = project3d(vertex);
        //     vertex = rotateZ(rotateX(rotateY(vertex, cube.angleY), cube.angleX), cube.angleZ);
        //     // std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z << "\n";
        //     vertex = project3d(vertex);
        //     grid[static_cast<int>(vertex.y)][static_cast<int>(vertex.x)] = '#';
        // }

        showGrid();
        usleep(100000);
    }
}
