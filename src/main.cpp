#include <unistd.h>

#include "../include/constants.h"
#include "../include/geometry.h"
#include "../include/renderer.h"
#include "../include/shapes.h"

[[noreturn]] int main(){
    Renderer renderer;
    Torus torus;


    while (true) {
        renderer.clearScreen();

        // Update rotation angles
        torus.angleY += ROTATION_SPEED;
        torus.angleX += ROTATION_SPEED * 0.4;  // Slower X rotation
        auto baseVertices = torus.getVertices();
        // Apply rotations to get new vertex positions
        for (int i = 0; i < baseVertices.size(); i++) {
            auto vertex = baseVertices[i];
            vertex = rotateX(rotateY(rotateZ(vertex, torus.angleZ), torus.angleY), torus.angleX);
            torus.vertices[i] = vertex;
        }

        // Draw all vertex

        for (auto p: torus.vertices) {
            renderer.plotPoint(p, '#');
        }

        // Draw all edges
        const auto& vertices = torus.vertices;
        const auto& edges = torus.edges;

        // for (const auto& edge : edges) {
        //     if (edge.start < vertices.size() && edge.end < vertices.size()) {
        //         renderer.drawLine(vertices[edge.start], vertices[edge.end]);
        //     }
        // }

        renderer.showGrid();

        // Control frame rate
        usleep(FRAME_DELAY_US);
    }
}
