#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include "shapes/Triangle.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
    ~Rectangle();
    void splitBy(int n);
    void splitByX(int n);
    void splitByY(int n);

    std::vector<Triangle> getTriangles();

private:
    int m_split_x;
    int m_split_y;

    glm::vec3 m_p1;
    glm::vec3 m_p2;
    glm::vec3 m_p3;
    glm::vec3 m_p4;
};

#endif // RECTANGLE_H
