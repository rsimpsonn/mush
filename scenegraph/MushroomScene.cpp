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

void MushroomScene::renderPhongPass(SupportCanvas3D *context) {
    if (settings.myceliumView) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }

    ShapesScene::renderPhongPass(context);
}


void MushroomScene::settingsChanged() {
    // TODO: [SHAPES] Fill this in, for now default to an example shape
    m_objects.clear();
    int MAPLENGTH = 20;
    std::vector<float> map(MAPLENGTH * MAPLENGTH, 0);

    std::vector<GLfloat> tessellation;

    std::vector<ColorScheme> schemes;
    if (settings.pinkEnabled) {
        schemes.push_back(ColorScheme::PINK);
    }
    if (settings.orangeEnabled) {
        schemes.push_back(ColorScheme::ORANGE);
    }
    if (settings.yellowEnabled) {
        schemes.push_back(ColorScheme::YELLOW);
    }
    if (schemes.size() == 0) {
        schemes.push_back(ColorScheme::PINK);
    }
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

                ColorScheme color = schemes[arc4random()%schemes.size()];
                m_objects.push_back(std::make_tuple(mushTop,MushroomSceneType::MUSHROOM_TOP,mushT,color));
                m_objects.push_back(std::make_tuple(mushGills,MushroomSceneType::MUSHROOM_GILLS,mushT,color));
                m_objects.push_back(std::make_tuple(mushStem,MushroomSceneType::MUSHROOM_STEM,mushT,color));
                m_objects.push_back(std::make_tuple(myc,MushroomSceneType::MUSHROOM_MYCELIUM,glm::mat4(),color));


            }
        }
    }
    m_shape = std::make_unique<MushroomForest>(tessellation);
    m_shape->tessellate(0, 0, 0);
}

void MushroomScene::renderGeometry() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // PINK COLOR SCHEME
    CS123SceneMaterial pink = CS123SceneMaterial();
    pink.clear();
    pink.cAmbient.r = 0.2f;
    pink.cAmbient.g = 0.0f;
    pink.cAmbient.b = 0.7f;
    pink.cDiffuse.r = 0.7f;
    pink.cDiffuse.g = 0.1f;
    pink.cDiffuse.b = 0.0f;
    pink.cSpecular.r = pink.cSpecular.g = pink.cSpecular.b = 1;
    pink.shininess = 100;

    CS123SceneMaterial pinkStem = CS123SceneMaterial();
    pinkStem.clear();
    pinkStem.cAmbient.r = 0.2f;
    pinkStem.cAmbient.g = 0.0f;
    pinkStem.cAmbient.b = 0.9f;
    pinkStem.cDiffuse.r = 1.0f;
    pinkStem.cDiffuse.g = 0.5f;
    pinkStem.cSpecular.r = pinkStem.cSpecular.g = pinkStem.cSpecular.b = 1;
    pinkStem.shininess = 100;

    CS123SceneMaterial pinkGills = CS123SceneMaterial();
    pinkGills.clear();
    pinkGills.cAmbient.r = 0.2f;
    pinkGills.cAmbient.g = 0.0f;
    pinkGills.cAmbient.b = 0.7f;
    pinkGills.cDiffuse.r = 1.0f;
    pinkGills.cDiffuse.g = 0.2f;
    pinkGills.cDiffuse.b = 0.5f;
    pinkGills.cSpecular.r = pinkGills.cSpecular.g = pinkGills.cSpecular.b = 1;
    pinkGills.shininess = 100;

    CS123SceneMaterial greenMyc = CS123SceneMaterial();
    greenMyc.clear();
    greenMyc.cAmbient.r = 0.2f;
    greenMyc.cAmbient.g = 0.7f;
    greenMyc.cAmbient.b = 0.4f;
    greenMyc.cDiffuse.r = 0.2f;
    greenMyc.cDiffuse.g = 0.7f;
    greenMyc.cDiffuse.b = 0.2f;
    greenMyc.cSpecular.r = greenMyc.cSpecular.g = greenMyc.cSpecular.b = 1;
    greenMyc.shininess = 100;

    // ORANGE COLOR SCHEME
    CS123SceneMaterial orangeGills = CS123SceneMaterial();
    orangeGills.clear();
    orangeGills.cAmbient.r = 0.9f;
    orangeGills.cAmbient.g = 0.2f;
    orangeGills.cAmbient.b = 0.0f;
    orangeGills.cDiffuse.r = 0.5f;
    orangeGills.cDiffuse.g = 0.0f;
    orangeGills.cDiffuse.b = 0.0f;
    orangeGills.cSpecular.r = orangeGills.cSpecular.g = orangeGills.cSpecular.b = 1;
    orangeGills.shininess = 100;

    CS123SceneMaterial orange = CS123SceneMaterial();
    orange.clear();
    orange.cAmbient.r = 0.9f;
    orange.cAmbient.g = 0.2f;
    orange.cAmbient.b = 0.0f;
    orange.cDiffuse.r = 0.4f;
    orange.cDiffuse.g = 0.2f;
    orange.cDiffuse.b = 0.0f;
    orange.cSpecular.r = orange.cSpecular.g = orange.cSpecular.b = 1;
    orange.shininess = 100;

    CS123SceneMaterial orangeStem = CS123SceneMaterial();
    orangeStem.clear();
    orangeStem.cAmbient.r = 1.0f;
    orangeStem.cAmbient.g = 0.5f;
    orangeStem.cAmbient.b = 0.0f;
    orangeStem.cDiffuse.r = 0.7f;
    orangeStem.cDiffuse.g = 0.2f;
    orangeStem.cDiffuse.b = 0.0f;
    orangeStem.cSpecular.r = orangeStem.cSpecular.g = orangeStem.cSpecular.b = 1;
    orangeStem.shininess = 100;

    CS123SceneMaterial blueMyc = CS123SceneMaterial();
    blueMyc.clear();
    blueMyc.cAmbient.r = 0.2f;
    blueMyc.cAmbient.g = 0.7f;
    blueMyc.cAmbient.b = 0.9f;
    blueMyc.cDiffuse.r = 0.2f;
    blueMyc.cDiffuse.g = 0.7f;
    blueMyc.cDiffuse.b = 0.5f;
    blueMyc.cSpecular.r = blueMyc.cSpecular.g = blueMyc.cSpecular.b = 1;
    blueMyc.shininess = 100;

    // YELLOW COLOR SCHEME
    CS123SceneMaterial yellow = CS123SceneMaterial();
    yellow.clear();
    yellow.cAmbient.r = 0.5f;
    yellow.cAmbient.g = 0.9f;
    yellow.cAmbient.b = 0.3f;
    yellow.cDiffuse.r = 0.5f;
    yellow.cDiffuse.g = 0.9f;
    yellow.cDiffuse.b = 0.0f;
    yellow.cSpecular.r = yellow.cSpecular.g = yellow.cSpecular.b = 1;
    yellow.shininess = 100;

    CS123SceneMaterial yellowStem = CS123SceneMaterial();
    yellowStem.clear();
    yellowStem.cAmbient.r = 0.8f;
    yellowStem.cAmbient.g = 0.9f;
    yellowStem.cAmbient.b = 0.0f;
    yellowStem.cDiffuse.r = 0.4f;
    yellowStem.cDiffuse.g = 0.4f;
    yellowStem.cDiffuse.b = 0.4f;
    yellowStem.cSpecular.r = yellowStem.cSpecular.g = yellowStem.cSpecular.b = 1;
    yellowStem.shininess = 100;

    CS123SceneMaterial yellowGills = CS123SceneMaterial();
    yellowGills.clear();
    yellowGills.cAmbient.r = 0.1f;
    yellowGills.cAmbient.g = 0.9f;
    yellowGills.cAmbient.b = 0.3f;
    yellowGills.cDiffuse.r = 0.1f;
    yellowGills.cDiffuse.g = 0.9f;
    yellowGills.cDiffuse.b = 0.0f;
    yellowGills.cSpecular.r = yellowGills.cSpecular.g = yellowGills.cSpecular.b = 1;
    yellowGills.shininess = 100;

    CS123SceneMaterial purpleMyc = CS123SceneMaterial();
    purpleMyc.clear();
    purpleMyc.cAmbient.r = 0.4f;
    purpleMyc.cAmbient.g = 0.0f;
    purpleMyc.cAmbient.b = 0.9f;
    purpleMyc.cDiffuse.r = 0.4f;
    purpleMyc.cDiffuse.g = 0.0f;
    purpleMyc.cDiffuse.b = 0.9f;
    purpleMyc.cSpecular.r = purpleMyc.cSpecular.g = purpleMyc.cSpecular.b = 1;
    purpleMyc.shininess = 100;

    for (int i = 0; i < m_objects.size(); i++) {
        std::vector<GLfloat> f;
        MushroomSceneType m;
        glm::mat4 t;
        ColorScheme c;
        std::tie(f, m, t, c) = m_objects[i];

        switch (c) {
            case ColorScheme::PINK:
//                std::cout << "pink" << std::endl;
                switch (m) {
                    case MushroomSceneType::MUSHROOM_TOP:
                        m_phongShader->applyMaterial(pink);
                        //m_phongShader->setUniform("m", t);
                        break;
                    case MushroomSceneType::MUSHROOM_MYCELIUM:
                        m_phongShader->applyMaterial(greenMyc);
                        break;
                    case MushroomSceneType::MUSHROOM_STEM:
                        m_phongShader->applyMaterial(pinkStem);
                        break;
                    case MushroomSceneType::MUSHROOM_GILLS:
                        m_phongShader->applyMaterial(pinkGills);
                        break;
                }
                break;
            case ColorScheme::ORANGE:
//                std::cout << "orange" << std::endl;
                switch (m) {
                    case MushroomSceneType::MUSHROOM_TOP:
                        m_phongShader->applyMaterial(orange);
                        //m_phongShader->setUniform("m", t);
                        break;
                    case MushroomSceneType::MUSHROOM_MYCELIUM:
                        m_phongShader->applyMaterial(blueMyc);
                        break;
                    case MushroomSceneType::MUSHROOM_STEM:
                        m_phongShader->applyMaterial(orangeStem);
                        break;
                    case MushroomSceneType::MUSHROOM_GILLS:
                        m_phongShader->applyMaterial(orangeGills);
                        break;
                }
                break;
            case ColorScheme::YELLOW:
//                std::cout << "yellow" << std::endl;
                switch (m) {
                    case MushroomSceneType::MUSHROOM_TOP:
                        m_phongShader->applyMaterial(yellow);
                        //m_phongShader->setUniform("m", t);
                        break;
                    case MushroomSceneType::MUSHROOM_MYCELIUM:
                        m_phongShader->applyMaterial(purpleMyc);
                        break;
                    case MushroomSceneType::MUSHROOM_STEM:
                        m_phongShader->applyMaterial(yellowStem);
                        break;
                    case MushroomSceneType::MUSHROOM_GILLS:
                        m_phongShader->applyMaterial(yellowGills);
                        break;
                }
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





