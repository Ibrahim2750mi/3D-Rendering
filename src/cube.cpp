// g++ -I include src/modules/*.cpp src/cube.cpp -o build/cube

#include <unistd.h>

#include "../include/constants.h"
#include "../include/geometry.h"
#include "../include/light.h"
#include "../include/renderer.h"
#include "../include/shapes.h"

[[noreturn]] int main(){
    Renderer renderer;
    Cube cube;

    auto baseVertices = cube.getVertices();

    while (true) {
        renderer.clearScreen();

        // Update rotation angles
        cube.angleY += ROTATION_SPEED;
        cube.angleX += ROTATION_SPEED * 0.4;
        cube.angleZ += ROTATION_SPEED;

        // Applying rotations to get new vertex positions
        for (int i = 0; i < baseVertices.size(); i++) {
            auto vertex = baseVertices[i];
            vertex = rotateX(rotateY(rotateZ(vertex, cube.angleX), cube.angleY), cube.angleZ);
            cube.vertices[i] = vertex;
        }

        for (auto [start, end]: cube.edges) {
            Point3d v1 = renderer.project3d(cube.vertices[start]);
            Point3d v2 = renderer.project3d(cube.vertices[end]);
            renderer.drawLine(v1, v2);
        }

        renderer.showGrid();

        // Control frame rate
        usleep(FRAME_DELAY_US);
    }
}