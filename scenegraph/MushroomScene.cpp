#include "MushroomScene.h"
#include "Camera.h"
#include "shapes/OpenGLShape.h"
#include <SupportCanvas3D.h>
#include "shapes/ExampleShape.h"
#include <QFileDialog>
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Cone.h"
#include "shapes/Sphere.h"
#include "shapes/Mycelium.h"
#include "shapes/Mushroom.h"
#include "shapes/SuperShroom.h"
#include <iostream>
#include "glm/ext.hpp"
#include "shapes/MushroomForest.h"
#include "CS123ISceneParser.h"

#include <sstream>

using namespace CS123::GL;
#include "gl/shaders/CS123Shader.h"
#include "gl/shaders/Shader.h"

#include "ResourceLoader.h"

MushroomScene::MushroomScene(int width, int height) :
    ShapesScene(width, height)
{

    m_classic = std::make_unique<SuperShroom>(1, 1, 1, MushroomType::MUSHROOM_CLASSIC);
    m_bell = std::make_unique<SuperShroom>(1, 1, 1, MushroomType::MUSHROOM_BELL);
    m_pancake = std::make_unique<SuperShroom>(1, 1, 1, MushroomType::MUSHROOM_PANCAKE);


    //TODO: [SHAPES] Allocate any additional memory you need...

}

MushroomScene::~MushroomScene()
{
    // Pro-tip: If you use smart pointers properly, this destructor should be empty
}


void MushroomScene::settingsChanged() {
    // TODO: [SHAPES] Fill this in, for now default to an example shape

    std::cout << "running again" << std::endl;
    m_objects.clear();
    int MAPLENGTH = 20;
    std::vector<float> map(MAPLENGTH * MAPLENGTH, 0);

    std::vector<GLfloat> tessellation;

    generateMap(settings.maxMushComplexity, settings.numMushrooms, settings.minMushComplexity, 0.2, map);
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            if (map[i * MAPLENGTH + j] > 0) {
                std::vector<GLfloat> mushTop;
                std::vector<GLfloat> mushGills;
                std::vector<GLfloat> mushStem;
                std::vector<GLfloat> myc;
                glm::mat4 mushT;
                std::tie(mushTop, mushGills, mushStem, myc, mushT) = m_classic->getBoth(map[i * MAPLENGTH + j], 8, glm::translate(glm::vec3{i - float(MAPLENGTH) / 2, -1.f, -j}));

                m_objects.push_back(std::make_tuple(mushTop,MushroomSceneType::MUSHROOM_TOP,mushT));
                m_objects.push_back(std::make_tuple(mushGills,MushroomSceneType::MUSHROOM_GILLS,mushT));
                m_objects.push_back(std::make_tuple(mushStem,MushroomSceneType::MUSHROOM_STEM,mushT));
                m_objects.push_back(std::make_tuple(myc,MushroomSceneType::MUSHROOM_MYCELIUM,glm::mat4()));
            }
        }
    }
    m_shape = std::make_unique<MushroomForest>(tessellation);
    m_shape->tessellate(0, 0, 0);
}

void MushroomScene::renderGeometry() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    CS123SceneMaterial m0 = CS123SceneMaterial();
    m0.clear();
    m0.cAmbient.r = 0.75f;
    m0.cAmbient.g = 0.9f;
    m0.cAmbient.b = 0.85f;
    m0.cDiffuse.r = 0.4f;
    m0.cDiffuse.g = 0.9f;
    m0.cSpecular.r = m0.cSpecular.g = m0.cSpecular.b = 1;
    m0.shininess = 100;


    CS123SceneMaterial m1 = CS123SceneMaterial();
    m1.clear();
    m1.cAmbient.r = 0.9f;
    m1.cAmbient.g = 0.0f;
    m1.cAmbient.b = 0.9f;
    m1.cDiffuse.r = 1.0f;
    m1.cDiffuse.g = 0.5f;
    m1.cSpecular.r = m1.cSpecular.g = m1.cSpecular.b = 1;
    m1.shininess = 100;

    CS123SceneMaterial m3 = CS123SceneMaterial();
    m3.clear();
    m3.cAmbient.r = 0.8f;
    m3.cAmbient.g = 0.4f;
    m3.cAmbient.b = 0.9f;
    m3.cDiffuse.r = 1.0f;
    m3.cDiffuse.g = 0.5f;
    m3.cSpecular.r = m3.cSpecular.g = m3.cSpecular.b = 1;
    m3.shininess = 100;

    for (int i = 0; i < m_objects.size(); i++) {
        std::vector<GLfloat> f;
        MushroomSceneType m;
        glm::mat4 t;
        std::tie(f, m, t) = m_objects[i];

        switch (m) {
        case MushroomSceneType::MUSHROOM_TOP:
            m_phongShader->applyMaterial(m1);
            //m_phongShader->setUniform("m", t);
            break;
        case MushroomSceneType::MUSHROOM_MYCELIUM:
            m_phongShader->applyMaterial(m0);
            break;
        case MushroomSceneType::MUSHROOM_STEM:
            m_phongShader->applyMaterial(m3);
            break;
        case MushroomSceneType::MUSHROOM_GILLS:
            m_phongShader->applyMaterial(m3);
            break;
        }

        m_shape = std::make_unique<MushroomForest>(f);
        m_shape->tessellate(0, 0, 0);
        m_shape->draw();
    }
}

void MushroomScene::generateMap(int n, int r, int min, float dropoff, std::vector<float> &map) {
    int creating = (n == min) ? r : std::floor(float(r) * dropoff);

    for (int i = 0; i < creating; i++) {
        int dropAt = rand() % map.size();
        while (!validBlock(n, dropAt, map)) {
            std::cout << "REDO" << std::endl;
            dropAt = rand() % map.size();
        }

       fillBlock(n, dropAt, map);
       map[dropAt] = n;
    }

    if (n <= min) {
        return;
    } else {
        generateMap(n - 1, r - creating, min, dropoff, map);
    }
}

bool MushroomScene::validBlock(int n, int i, std::vector<float> &map) {
    int r = glm::floor(float(n)/2);
    int side = r * 2 + 1;
    int MAPLENGTH = 20;
    int startIndex = i - MAPLENGTH * r - r;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int currIndex = startIndex + i * MAPLENGTH + j;
            if (currIndex >= map.size() || currIndex < 0) {
                continue;
            }
            if (map[currIndex] != 0) {
                return false;
            }
        }
    }

    return true;
}

void MushroomScene::fillBlock(int n, int i, std::vector<float> &map) {
    int r = glm::floor(float(n)/2);
    int side = r * 2 + 1;
    int MAPLENGTH = 20;
    int startIndex = i - MAPLENGTH * r - r;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int currIndex = startIndex + i * MAPLENGTH + j;
            if (currIndex >= map.size() || currIndex < 0) {
                continue;
            }
            map[currIndex] = -1;
        }
    }
}





