// To include once
#pragma once

struct Point3d {
    double x, y, z;

    Point3d() : x(0), y(0), z(0) {}
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
};

Point3d rotateX(Point3d p, double angle);
Point3d rotateY(Point3d p, double angle);
Point3d rotateZ(Point3d p, double angle);
