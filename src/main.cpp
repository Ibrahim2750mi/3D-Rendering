#include <cmath>
#include <math.h>
#include <string>
#include <unistd.h>

#include "../include/constants.h"
#include "../include/geometry.h"
#include "../include/light.h"
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
            auto temp = torus.torusVertices[i];
            torus.torusVertices[i] = {vertex, temp.phi, temp.theta};
        }

        // Draw all vertices

        for (auto p: torus.torusVertices) {
            renderer.plotPoint(p.position, lambertShading(p));
        }

        renderer.showGrid();

        // Control frame rate
        usleep(FRAME_DELAY_US);
    }
}
