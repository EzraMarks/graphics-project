#include "glwidget.h"

#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include "settings.h"

#include "openglshape.h"
#include "gl/textures/Texture2D.h"
#include "gl/shaders/ShaderAttribLocations.h"

using namespace CS123::GL;

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_quad(nullptr),
      m_chemicalsFBO1(nullptr), m_chemicalsFBO2(nullptr),
      m_evenPass(true)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    glEnable(GL_DEPTH_TEST);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create shader programs.
    m_chemicalInitProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_init.frag");
    m_chemicalUpdateProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_update.frag");
    m_chemicalDrawProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_draw.frag");

    std::vector<GLfloat> quadData = {-1,  1, 0,
                                      0,  1,
                                     -1, -1, 0,
                                      0,  0,
                                      1,  1, 0,
                                      1,  1,
                                      1, -1, 0,
                                      1,  0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    m_chemicalsFBO1 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_chemicalsFBO2 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    auto prevFBO = m_evenPass ? m_chemicalsFBO1 : m_chemicalsFBO2;
    auto nextFBO = m_evenPass ? m_chemicalsFBO2 : m_chemicalsFBO1;
    m_evenPass = !m_evenPass;

    if (settings.isFirstPass) {
        initChemicals(prevFBO);
        settings.isFirstPass = false;
    }

    updateChemicals(prevFBO, nextFBO);
    drawChemicals(nextFBO);
    update();
}

void GLWidget::initChemicals(std::shared_ptr<FBO> FBO) {
    QImage image = QImage(settings.imagePath); // TODO: Add error checking

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());

    FBO->bind();
    glUseProgram(m_chemicalInitProgram);

    GLint locImage = glGetUniformLocation(m_chemicalInitProgram, "image");
    glUniform1i(locImage, 0);
    GLint locImageWidth = glGetUniformLocation(m_chemicalInitProgram, "imageWidth");
    glUniform1i(locImageWidth, image.width());
    GLint locImageHeight = glGetUniformLocation(m_chemicalInitProgram, "imageHeight");
    glUniform1i(locImageHeight, image.height());
    GLint locCanvasWidth = glGetUniformLocation(m_chemicalInitProgram, "canvasWidth");
    glUniform1i(locCanvasWidth, m_width);
    GLint locCanvasHeight = glGetUniformLocation(m_chemicalInitProgram, "canvasHeight");
    glUniform1i(locCanvasHeight, m_height);

    m_quad->draw();
    FBO->unbind();
}

void GLWidget::updateChemicals(std::shared_ptr<FBO> prevFBO, std::shared_ptr<FBO> nextFBO) {
    nextFBO->bind();
    glUseProgram(m_chemicalUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();

    // Sends uniforms containing the previous state of the simulation
    GLint locWidth = glGetUniformLocation(m_chemicalUpdateProgram, "width");
    glUniform1i(locWidth, m_width);
    GLint logHeight = glGetUniformLocation(m_chemicalUpdateProgram, "height");
    glUniform1i(logHeight, m_height);
    GLint locPrevChemicals = glGetUniformLocation(m_chemicalUpdateProgram, "prevChemicals");
    glUniform1i(locPrevChemicals, 0);

    // Sends uniforms containing the reaction-diffusion parameters
    GLint locDt = glGetUniformLocation(m_chemicalUpdateProgram, "dt");
    glUniform1f(locDt, settings.dt);
    GLint locDiffusionRateA = glGetUniformLocation(m_chemicalUpdateProgram, "diffusionRateA");
    glUniform1f(locDiffusionRateA, settings.diffusionRateA);
    GLint locDiffusionRateB = glGetUniformLocation(m_chemicalUpdateProgram, "diffusionRateB");
    glUniform1f(locDiffusionRateB, settings.diffusionRateB);
    GLint locFeedRate = glGetUniformLocation(m_chemicalUpdateProgram, "feedRate");
    glUniform1f(locFeedRate, settings.feedRate / 10.f);
    GLint locKillRate = glGetUniformLocation(m_chemicalUpdateProgram, "killRate");
    glUniform1f(locKillRate, settings.killRate / 10.f);

    m_quad->draw();
    prevFBO->getColorAttachment(0).unbind();
    nextFBO->unbind();
}

void GLWidget::drawChemicals(std::shared_ptr<FBO> FBO) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_chemicalDrawProgram);

    glActiveTexture(GL_TEXTURE0);
    FBO->getColorAttachment(0).bind();

    GLint locTex = glGetUniformLocation(m_chemicalDrawProgram, "tex");
    glUniform1i(locTex, 0);
    GLint locWidth = glGetUniformLocation(m_chemicalDrawProgram, "width");
    glUniform1i(locWidth, m_width);
    GLint locHeight = glGetUniformLocation(m_chemicalDrawProgram, "height");
    glUniform1i(locHeight, m_height);
    GLint locColor = glGetUniformLocation(m_chemicalDrawProgram, "color");
    glUniform3f(locColor, settings.color.red() / 255.f, settings.color.green() / 255.f, settings.color.blue() / 255.f);

    m_quad->draw();
    FBO->getColorAttachment(0).unbind();
}

// This is called at the beginning of the program between initializeGL and
// the first paintGL call, as well as every time the window is resized.
void GLWidget::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    m_chemicalsFBO1 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_chemicalsFBO2 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    settings.isFirstPass = true;
}
