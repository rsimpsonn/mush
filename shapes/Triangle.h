#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "glm/glm.hpp"
#include "GL/glew.h"

class Triangle
{
public:
    Triangle();
    Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, std::function<glm::vec3 (glm::vec3 p)> func);
    ~Triangle();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getNormals();

    void addVertex(glm::vec3 src, glm::vec3 dest1, glm::vec3 dest2);
    void addVertex(glm::vec3 src, std::function<glm::vec3 (glm::vec3 p)> func);
    void addToVector(std::vector<GLfloat> *v);
    void addToVector(std::vector<GLfloat> *v, glm::mat4 t);
    void remapNormals(std::function<glm::vec3 (glm::vec3 p)> func);
    void remapNormals(std::function<glm::vec3 (glm::vec3 p)> func, std::function<bool (glm::vec3 p)> ignoreIf);

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;


};

#endif // TRIANGLE_H
