#include "scene.h"


Scene::Scene(QWidget * parent)
    : QOpenGLWidget(parent)
    , _sceneSize(1000000.0f)
    , _triangleCount(30)
    , _near(0.0f)
    , _far(100.0f)
    , _left(0.0f)
    , _bottom(0.0f)
{
}


void
Scene::initializeGL()
{
    initializeOpenGLFunctions();
    _triangles.Initialize(_sceneSize, _triangleCount);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void
Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLint screenWidth = width();
    GLint screenHeight = height();
    float virtualWidth = _sceneSize;
    float virtualHeight = _sceneSize;

    float targetAspectRatio = virtualWidth / virtualHeight;
    GLint vpW = screenWidth;
    GLint vpH = vpW / targetAspectRatio + 0.5f;

    if (vpH > screenHeight)
    {
        vpH = screenHeight;
        vpW = vpH * targetAspectRatio + 0.5f;
    }

    GLint vpX = screenWidth / 2.0f - vpW / 2.0f + 0.5f;
    GLint vpY = screenHeight / 2.0f - vpH / 2.0f + 0.5f;

    // Center the scene in the viewport
    glViewport(vpX, vpY, vpW, vpH);


    // Model      - no translation or scaling
    // View       - setting the view has no effect
    // Projection - using ortho for 2D scene

    QMatrix4x4 mvpMatrix;

    mvpMatrix.ortho(_left, virtualWidth, _bottom, virtualHeight,
        _near, _far);

    _triangles.Draw(mvpMatrix);
}

