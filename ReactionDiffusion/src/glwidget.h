#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr

#include <memory>  // std::unique_ptr

#include "gl/datatype/FBO.h"

class OpenGLShape;

using namespace CS123::GL;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    void initChemicals(std::shared_ptr<FBO> FBO);
    void updateChemicals(std::shared_ptr<FBO> prevFBO, std::shared_ptr<FBO> nextFBO);
    void drawChemicals(std::shared_ptr<FBO> FBO);

    int m_width;
    int m_height;

    GLuint m_chemicalInitProgram;
    GLuint m_chemicalUpdateProgram;
    GLuint m_chemicalDrawProgram;

    std::unique_ptr<OpenGLShape> m_quad;

    std::shared_ptr<FBO> m_chemicalsFBO1;
    std::shared_ptr<FBO> m_chemicalsFBO2;
    bool m_evenPass;
};

#endif // GLWIDGET_H
