#include "../../include/light.h"
#include "../../include/constants.h"
#include <cmath>
#include <string>

char lambertShading(const TorusVertex &p) {

    // Geometrical property of torus, center and point position vector gives normal vector
    const Point3d surfaceNormal = {
        TORUS_MINOR_RADIUS*cos(p.theta)*cos(p.phi),
        TORUS_MINOR_RADIUS*sin(p.theta)*cos(p.phi),
        TORUS_MINOR_RADIUS*sin(p.phi)
    };

    auto dot = surfaceNormal.x * LIGHT_SOURCE.x +
        surfaceNormal.y * LIGHT_SOURCE.y +
        surfaceNormal.z * LIGHT_SOURCE.z;
    dot /= sqrt(LIGHT_SOURCE.x*LIGHT_SOURCE.x + LIGHT_SOURCE.z*LIGHT_SOURCE.z + LIGHT_SOURCE.y*LIGHT_SOURCE.y);
    const double intensity = dot / TORUS_MINOR_RADIUS;
    const std::string chars = ".,-~:;=!*#$@";  // Dark to bright
    const int index = static_cast<int>((intensity + 1) * 0.5 * (chars.length() - 1));
    return chars[index];
}
