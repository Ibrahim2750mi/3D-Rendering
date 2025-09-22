#include "../include/light.h"
#include "../include/constants.h"
#include <cmath>
#include <string>

char lambertShading(const TorusVertex &p) {

    // Geometrical property of torus, center and point position vector gives normal vector
    const Point3d surfaceNormal = {
        TORUS_MINOR_RADIUS*cos(p.theta)*cos(p.phi),
        TORUS_MINOR_RADIUS*sin(p.theta)*cos(p.phi),
        TORUS_MINOR_RADIUS*sin(p.phi)
    };

    const double intensity = surfaceNormal.z * LIGHT_SOURCE.z / TORUS_MINOR_RADIUS;
    const std::string chars = ".,-~:;=!*#$@";  // Dark to bright
    const int index = static_cast<int>((intensity + 1) * 0.5 * (chars.length() - 1));
    return chars[index];
}
