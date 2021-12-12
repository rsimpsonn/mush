#include "SuperShroom.h"
#include "Mycelium.h"
#include "Rectangle.h"
#include "Mushroom.h"
#include "Shape.h"
#include "glm/ext.hpp"
#include <iostream>

SuperShroom::SuperShroom()
{
}

SuperShroom::SuperShroom(int param1, int param2, int param3, MushroomType mushroomType) :
    Shape(param1, param2, param3),
    m_mushroomType(mushroomType)
{
    m_mushroom = std::make_unique<Mushroom>(param1, param2, mushroomType);
    m_mycelium = std::make_unique<Mycelium>(param1, param2, mushroomType);
    initializeOpenGLShapeProperties();
}


void SuperShroom::tessellate(int param1, int param2, int param3) {
    std::vector<Triangle> mushTris = m_mushroom->getTriangles(1, param2, param3);
    std::vector<std::tuple<Triangle, glm::mat4>> mycTris = m_mycelium->getTriangles(param1, param2, param3);
    std::vector<GLfloat> tessellation;


    for (int i = 0; i < mushTris.size(); i++) {
        mushTris[i].addToVector(&tessellation, glm::scale(glm::vec3{param1, param1, param1}));
    }

    for (int i = 0; i < mycTris.size(); i++) {
        Triangle t;
        glm::mat4 m;
        std::tie(t, m) = mycTris[i];

        //std::cout << glm::to_string(m) << std::endl;
        t.addToVector(&tessellation, m);
    }


    m_vertexData = tessellation;

    initializeOpenGLShapeProperties();
}

std::vector<std::tuple<Triangle,glm::mat4>> SuperShroom::getTriangles(int param1, int param2, int param3) {
    std::vector<Triangle> mushTris = m_mushroom->getTriangles(1, param2, param3);
    std::vector<std::tuple<Triangle, glm::mat4>> mycTris = m_mycelium->getTriangles(param1, param2, param3);
    std::vector<std::tuple<Triangle,glm::mat4>> out;


    for (int i = 0; i < mushTris.size(); i++) {
        out.push_back(std::make_tuple(mushTris[i],  glm::translate(glm::vec3{0, pow(2,param1 - 1), 0}) * glm::scale(glm::vec3{pow(2,param1 - 1), pow(2,param1 - 1),pow(2,param1 - 1)})));
    }

    for (int i = 0; i < mycTris.size(); i++) {
        Triangle t;
        glm::mat4 m;
        std::tie(t, m) = mycTris[i];

        //std::cout << glm::to_string(m) << std::endl;
        out.push_back(std::make_tuple(t, glm::scale(glm::vec3{2, 2, 2}) * glm::translate(glm::vec3{0, param1/2, 0}) * m));
    }

    return out;
}

void SuperShroom::runTessellation(std::vector<GLfloat> t) {
    m_vertexData = t;
    initializeOpenGLShapeProperties();

    std::cout << "FINISHED" << std::endl;
}
