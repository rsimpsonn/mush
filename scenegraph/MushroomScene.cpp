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

    int MAPLENGTH = 10;
    std::vector<float> map(MAPLENGTH * MAPLENGTH, 0);

    std::vector<GLfloat> tessellation;

    generateMap(settings.maxMushComplexity, settings.numMushrooms, settings.minMushComplexity, 0.2, map);
    for (int i = 0; i < MAPLENGTH; i++) {
        for (int j = 0; j < MAPLENGTH; j++) {
            if (map[i * MAPLENGTH + j] > 0) {
                std::vector<std::tuple<Triangle,glm::mat4>> tris = m_classic->getTriangles(map[i * MAPLENGTH + j], 8, 1);
                for (int k = 0; k < tris.size(); k++) {
                    Triangle t;
                    glm::mat4 m;
                    std::tie(t, m) = tris[k];

                    t.addToVector(&tessellation, glm::translate(glm::vec3{i, 0, j}) * m);
                }
            }
        }
    }
    m_shape = std::make_unique<MushroomForest>(tessellation);
    m_shape->tessellate(0, 0, 0);
}

void MushroomScene::generateMap(int n, int r, int min, float dropoff, std::vector<float> &map) {
    int creating = (n == min) ? r : std::floor(float(r) * dropoff);

    for (int i = 0; i < creating; i++) {
        int dropAt = rand() % map.size();
        while (map[dropAt] != 0) {
            dropAt = rand() % map.size();
        }

        map[dropAt] = n;
    }

    if (n <= min) {
        return;
    } else {
        generateMap(n - 1, r - creating, min, dropoff, map);
    }
}



