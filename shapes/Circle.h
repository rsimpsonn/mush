#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/glm.hpp>
#include <vector>
#include "shapes/Triangle.h"


class Circle
{
public:
    Circle(float radius, glm::vec3 center, int orientation);
    ~Circle();
    void spokeBy(int n);
    void concentricBy(int n);
    std::vector<Triangle> getTriangles();
    std::vector<glm::vec3> getOuterVertices();
    std::vector<Triangle> getTrianglesDecline(float n);
    float getRadius();
    float getYVal();

private:
    int m_vertices;
    float m_radius;
    glm::vec3 m_center;
    int m_orientation;
    int m_concentric;
    std::vector<Triangle> toTriangles(std::function<float(int)> func);

};

#endif // CIRCLE_H
