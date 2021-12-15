#ifndef MUSHROOMSCENE_H
#define MUSHROOMSCENE_H

#include "OpenGLScene.h"
#include "shapes/Shape.h"

#include <memory>

#include <GL/glew.h>

#include "gl/datatype/FBO.h"
#include "Settings.h"
#include "ShapesScene.h"

#include "shapes/SuperShroom.h"


/**
 *
 * @class MushroomScene
 *
 * A scene that is used to render a single shape.
 *
 * This scene has no notion of the scene graph, so it will not be useful to you in
 * assignments requiring the display of multiple shapes. Luckily, the first time you
 * will need that kind of functionality is in the Sceneview assignment... and we've
 * left that task up to you in the SceneviewScene class.
 *
 * By default, the ShapesScene displays only a single triangle. You'll need to do
 * a little work here to render your shapes. You could render the shapes directly
 * in this class, or you could pass the work on to one or more subclasses. Think
 * carefully about your design here - you'll be reusing your shapes multiple times
 * during this course!
 */
class MushroomScene : public ShapesScene {
public:
    MushroomScene(int width, int height);
    virtual ~MushroomScene();

    virtual void settingsChanged() override;
    virtual void renderGeometry() override;
    virtual void renderPhongPass(SupportCanvas3D *context) override;

private:
    std::unique_ptr<SuperShroom> m_classic;
    std::unique_ptr<SuperShroom> m_bell;
    std::unique_ptr<SuperShroom> m_pancake;
    std::vector<std::tuple<std::vector<GLfloat>,MushroomSceneType,glm::mat4,ColorScheme>> m_objects;
    void generateMap(int n, int r, int min, float dropoff, std::vector<float> &map);
    bool validBlock(int n, int i, std::vector<float> &map);
    void fillBlock(int n, int i, std::vector<float> &map);
};

#endif // MUSHROOMSCENE_H
