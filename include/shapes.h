#pragma once

#include "geometry.h"
#include "constants.h"
#include <vector>
#include <array>

struct Edge {
    int start, end;
};

// Base class for 3D shapes
class Shape3D {
protected:
    std::vector<Point3d> baseVertices;  // Original vertices

public:
    std::vector<Edge> edges;
    std::vector<Point3d> vertices;  // Current transformed vertices
    // Destructor to prevent memory leaks from daughter classes
    virtual ~Shape3D() = default;

    double angleX = 0.0;
    double angleY = 0.0;
    double angleZ = 0.0;

    // Pure virtual functions - must be implemented by derived classes
    virtual void generateVertices() = 0;
    virtual void generateEdges() = 0;

    // Getters
    const std::vector<Point3d>& getVertices() const { return baseVertices; }
};


class Cube : public Shape3D {
public:
    Cube();

    void generateVertices() override;
    void generateEdges() override;
};

// Torus implementation
class Torus : public Shape3D {
private:
    double majorRadius;
    double minorRadius;
    int phiSteps;
    int thetaSteps;

public:
    Torus(double R = TORUS_MAJOR_RADIUS, double r = TORUS_MINOR_RADIUS,
          int phi = TORUS_PHI_STEPS, int theta = TORUS_THETA_STEPS);

    void generateVertices() override;
    void generateEdges() override;

};
