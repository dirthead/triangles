#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QString>


class Triangles
{
public:
    void    Initialize(const double & designSize, const uint16_t boxCount);
    void    Draw(const QMatrix4x4 & matrix);

private:
    void    CreateTriangles();
    void    CreateShaderProgram();
    QString VertexShader();
    QString FragmentShader();

private:
    QVector3D *                 _vertexes;
    QOpenGLShaderProgram        _program;
    QOpenGLBuffer               _vertexBuffer;
    QOpenGLVertexArrayObject    _vertexArrayObject;
    int                         _matrixLocation;
    int                         _vertexLocation;
    double                      _designSize;
    uint16_t                    _triangleCount;
    double                      _boxSize;
    double                      _cellSize;
    uint64_t                    _vertexCount;
};

#endif // TRIANGLES_H

