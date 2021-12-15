#include "SuperShroom.h"
#include "Mycelium.h"
#include "Rectangle.h"
#include "Mushroom.h"
#include "Shape.h"
#include "glm/ext.hpp"
#include <iostream>
#include "MushroomForest.h"

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
    std::vector<std::tuple<Triangle, glm::mat4>> mycTris = m_mycelium->getTriangles(param1, param2, param3, true);
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

std::tuple<std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, glm::mat4> SuperShroom::getBoth(int param1, int param2, glm::mat4 transl, bool getTop) {
    std::vector<Triangle> top;
    std::vector<Triangle> gills;
    std::vector<Triangle> gillLines;
    std::vector<Triangle> stem;
    float randomRotation = arc4random()%90;
    std::tie(top, gills, gillLines, stem) = m_mushroom->getAll(1, param2, 1);
    std::vector<std::tuple<Triangle, glm::mat4>> mycTris = m_mycelium->getTriangles(param1, param2, 1, getTop);
    std::vector<GLfloat> mushTopTessellation;
    std::vector<GLfloat> mushGillsTessellation;
    std::vector<GLfloat> mushGillLinesTessellation;
    std::vector<GLfloat> mushStemTessellation;
    std::vector<GLfloat> mycTessellation;
    float f = 52.7082 + (1.128885 - 52.7082)/(1 + (pow(float(param1)/6.49427, 3.82))); // y = 52.7082 + (1.128885 - 52.7082)/(1 + (x/6.49427)^3.820115)
    glm::mat4 mushTransformation = transl * glm::rotate(glm::radians(randomRotation), glm::vec3(0.f,1.f,0.f)) * glm::translate(glm::vec3{0, f, 0}) * glm::scale(glm::vec3{f, f,f});

    for (int i = 0; i < top.size(); i++) {
        top[i].addToVector(&mushTopTessellation, mushTransformation);
    }

    for (int i = 0; i < gills.size(); i++) {
        gills[i].addToVector(&mushGillsTessellation, mushTransformation);
    }

    for (int i = 0; i < gillLines.size(); i++) {
        gillLines[i].addToVector(&mushGillLinesTessellation, mushTransformation);
    }

    for (int i = 0; i < stem.size(); i++) {
        stem[i].addToVector(&mushStemTessellation, mushTransformation);
    }

    for (int i = 0; i < mycTris.size(); i++) {
        Triangle t;
        glm::mat4 m;
        std::tie(t, m) = mycTris[i];

        float yF = 17.15525 + (0.2356819 - 17.15525)/(1.f + pow(float(param1)/6.405077,3.79));//y = 17.15525 + (0.2356819 - 17.15525)/(1 + (x/6.405077)^3.786371)

        //std::cout << glm::to_string(m) << std::endl;
        t.addToVector(&mycTessellation, transl * glm::scale(glm::vec3{2, 2, 2}) * glm::translate(glm::vec3{0, yF, 0}) * m);
    }

    return std::make_tuple(mushTopTessellation, mushGillsTessellation, mushGillLinesTessellation, mushStemTessellation, mycTessellation, mushTransformation);
}


std::vector<std::tuple<Triangle,glm::mat4>> SuperShroom::getTriangles(int param1, int param2, int param3) {
    std::vector<Triangle> mushTris = m_mushroom->getTriangles(1, param2, param3);
    std::vector<std::tuple<Triangle, glm::mat4>> mycTris = m_mycelium->getTriangles(param1, param2, param3, true);
    std::vector<std::tuple<Triangle,glm::mat4>> out;


    for (int i = 0; i < mushTris.size(); i++) {
        out.push_back(std::make_tuple(mushTris[i],  glm::translate(glm::vec3{0, pow(2,param1 - 1), 0}) * glm::scale(glm::vec3{pow(2,param1 - 1), pow(2,param1 - 1),pow(2,param1 - 1)})));
    }

    for (int i = 0; i < mycTris.size(); i++) {
        Triangle t;
        glm::mat4 m;
        std::tie(t, m) = mycTris[i];

        //std::cout << glm::to_string(m) << std::endl;
        out.push_back(std::make_tuple(t, glm::scale(glm::vec3{2, 2, 2}) * glm::translate(glm::vec3{0, param1/2.1 * pow(param1/2.2, 2)/2.3, 0}) * m));
    }

    return out;
}

void SuperShroom::runTessellation(std::vector<GLfloat> t) {
    m_vertexData = t;
    initializeOpenGLShapeProperties();

    std::cout << "FINISHED" << std::endl;
}
