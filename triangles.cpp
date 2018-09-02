#include <triangles.h>


void
Triangles::Initialize(const double & designSize, const uint16_t boxCount)
{
    _designSize = designSize;
    _triangleCount = boxCount;
    _cellSize = _designSize / _triangleCount;
    _boxSize = _cellSize / 2.0;
    _vertexCount = _triangleCount * _triangleCount * 3;

    CreateTriangles();
    CreateShaderProgram();
}


void
Triangles::Draw(const QMatrix4x4 & matrix)
{
    _program.bind();
    _program.setUniformValue(_matrixLocation, matrix);
    {
        _vertexArrayObject.bind();
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
        _vertexArrayObject.release();
    }
    _program.release();
}


void
Triangles::CreateTriangles()
{
    const double z = -100.0;

    _vertexes = new QVector3D[ _vertexCount ];

    for (uint64_t row = 0; row < _triangleCount; ++row)
    {
        float y = row * _cellSize;

        for (uint64_t col = 0; col < _triangleCount; ++col)
        {
            float       x       = col * _cellSize;
            uint64_t    index   = col * 3 + row * _triangleCount * 3;

            _vertexes[ index + 0 ] = QVector3D(x, y, z);
            _vertexes[ index + 1 ] = QVector3D(x + _boxSize, y, z);
            _vertexes[ index + 2 ] = QVector3D(x, y + _boxSize, z);
        }
    }
}


void
Triangles::CreateShaderProgram()
{
    _program.addShaderFromSourceCode(QOpenGLShader::Vertex, VertexShader());
    _program.addShaderFromSourceCode(QOpenGLShader::Fragment, FragmentShader());
    _program.link();
    _program.bind();

    _vertexBuffer.create();
    _vertexBuffer.bind();
    _vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vertexBuffer.allocate(_vertexes, _vertexCount);

    _vertexArrayObject.create();
    _vertexArrayObject.bind();

    _matrixLocation = _program.uniformLocation("matrix");
    _vertexLocation = _program.attributeLocation("vertexCoord");
    _program.enableAttributeArray(_vertexLocation);
    _program.setAttributeBuffer(_vertexLocation, GL_FLOAT, 0, 3, 0);

    _vertexArrayObject.release();
    _vertexBuffer.release();
    _program.release();
}


QString
Triangles::VertexShader()
{
    return QString(
    "attribute highp vec3 vertexCoord;\n"
    "uniform mediump mat4 matrix;\n"
    "\n"
    "void main() {\n"
    "   gl_Position = matrix * vec4(vertexCoord, 1.0);\n"
    "}");
}


QString
Triangles::FragmentShader()
{
    return QString(
    "void main() {\n"
    "   gl_FragColor = vec4(0.0,1.0,0.0,1.0);\n"
    "}");
}

