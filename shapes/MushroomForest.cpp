#include "MushroomForest.h"

MushroomForest::MushroomForest(std::vector<GLfloat> t)
{
    m_vertexData = t;
}

void MushroomForest::tessellate(int param1, int param2, int param3) {
    initializeOpenGLShapeProperties();
}
