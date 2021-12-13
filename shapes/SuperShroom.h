#ifndef SUPERSHROOM_H
#define SUPERSHROOM_H

#include "Shape.h"
#include "Mushroom.h"
#include "Mycelium.h"
#include "Settings.h"
#include "ShapesScene.h"
#include "MushroomForest.h"

class SuperShroom : public Shape
{
public:

    SuperShroom(int param1, int param2, int param3, MushroomType mushroomType);

    SuperShroom();
    void tessellate(int param1, int param2, int param3);
    std::vector<std::tuple<Triangle,glm::mat4>> getTriangles(int param1, int param2, int param3);
    std::tuple<std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, glm::mat4> getBoth(int param1, int param2, glm::mat4 t);
    void runTessellation(std::vector<GLfloat> t);

private:
    int m_mushroomType;
    std::unique_ptr<Mushroom> m_mushroom;
    std::unique_ptr<Mycelium> m_mycelium;
};

#endif // SUPERSHROOM_H
