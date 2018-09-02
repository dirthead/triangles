#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

#include <triangles.h>


class Scene
    : public QOpenGLWidget
    , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Scene(QWidget * parent);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    const float _sceneSize;
    const uint64_t _triangleCount;
    const float _near;
    const float _far;
    const float _left;
    const float _bottom;
    Triangles _triangles;

    friend class MainWindow;
};

#endif // SCENE_H

