#include "../../include/geometry.h"
#include <cmath>

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