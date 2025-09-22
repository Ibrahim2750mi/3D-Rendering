#include "../include/shapes.h"
#include "../include/geometry.h"
#include <cmath>

Cube::Cube() {
    Cube::generateVertices();
    Cube::generateEdges();
    baseVertices = vertices;  // Store original position for calculation
}

void Cube::generateVertices() {
    vertices.clear();

    // 8 vertices of a unit cube centered at origin
    vertices = {
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},  // 0: back bottom-left
        { CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},  // 1: back bottom-right
        { CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},  // 2: back top-right
        {-CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},  // 3: back top-left
        {-CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},  // 4: front bottom-left
        { CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},  // 5: front bottom-right
        { CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},  // 6: front top-right
        {-CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE}   // 7: front top-left
    };
}

void Cube::generateEdges() {
    edges.clear();
    edges = {
        {
            // Back face (z = -1) - vertices 0,1,2,3
            {0, 1}, {1, 2}, {2, 3}, {3, 0},

            // Front face (z = +1) - vertices 4,5,6,7
            {4, 5}, {5, 6}, {6, 7}, {7, 4},

            // Connecting back to front
            {0, 4}, {1, 5}, {2, 6}, {3, 7}
        }
    };
}



Torus::Torus(double R, double r, int phi, int theta)
    : majorRadius(R), minorRadius(r), phiSteps(phi), thetaSteps(theta) {
    Torus::generateVertices();
    Torus::generateEdges();
    baseVertices = vertices;  // Store original positions
}

// TORUS

void Torus::generateVertices() {
    vertices.clear();

    // Generate vertices using parametric torus equations
    for (int i = 0; i < phiSteps; i++) {
        for (int j = 0; j < thetaSteps; j++) {
            double phi = 2.0 * M_PI * i / phiSteps;     // 0 to 2π (around tube)
            double theta = 2.0 * M_PI * j / thetaSteps; // 0 to 2π (around major circle)

            // Parametric torus equations
            double x = (majorRadius + minorRadius * cos(phi)) * cos(theta);
            double y = (majorRadius + minorRadius * cos(phi)) * sin(theta);
            double z = minorRadius * sin(phi);

            vertices.push_back({x, y, z});
        }
    }
}

void Torus::generateEdges() {
    edges.clear();

    // Connect vertices to form wireframe
    for (int i = 0; i < phiSteps; i++) {
        for (int j = 0; j < thetaSteps; j++) {
            int current = i * thetaSteps + j;
            int next_phi = ((i + 1) % phiSteps) * thetaSteps + j;
            int next_theta = i * thetaSteps + ((j + 1) % thetaSteps);

            // Add bounds checking to prevent segfaults
            if (current < vertices.size() && next_phi < vertices.size()) {
                edges.push_back({current, next_phi});    // Connect along phi direction
            }
            if (current < vertices.size() && next_theta < vertices.size()) {
                edges.push_back({current, next_theta});  // Connect along theta direction
            }
        }
    }
}
