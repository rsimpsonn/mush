#ifndef MUSHROOMFOREST_H
#define MUSHROOMFOREST_H

#include "Shape.h"
#include <glm/glm.hpp>

class MushroomForest : public Shape
{
public:
    MushroomForest(std::vector<GLfloat> t);
    void tessellate(int param1, int param2, int param3);
};

#endif // MUSHROOMFOREST_H
