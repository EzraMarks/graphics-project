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
#include "sphere.h"

using namespace CS123::GL;

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_phongProgram(0), m_textureProgram(0),
      m_quad(nullptr),
      m_chemicalsFBO1(nullptr), m_chemicalsFBO2(nullptr),
      m_evenPass(true), m_resolutionX(1024), m_resolutionY(1024),
      m_angleX(-0.5f), m_angleY(0.5f), m_zoom(4.f)
{
}

GLWidget::~GLWidget()
{
    glDeleteVertexArrays(1, &m_particlesVAO);
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    glEnable(GL_DEPTH_TEST);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create shader programs.
    m_phongProgram = ResourceLoader::createShaderProgram(
                ":/shaders/phong.vert", ":/shaders/phong.frag");
    m_textureProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/texture.frag");
    m_chemicalInitProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_init.frag");
    m_chemicalUpdateProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_update.frag");
    m_chemicalDrawProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/chemicals_draw.frag");

    // TODO: [Task 6] Fill in the positions and UV coordinates to draw a fullscreen quad
    // We've already set the vertex attributes for you, so be sure to follow those specifications
    // (triangle strip, 4 vertices, position followed by UVs)
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

    // We will use this VAO to draw our particles' triangles.
    // It doesn't need any data associated with it, so we don't have to make a full VAO instance
    glGenVertexArrays(1, &m_particlesVAO);
    // TODO [Task 13] Create m_particlesFBO1 and 2 with std::make_shared
    m_chemicalsFBO1 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_resolutionX, m_resolutionY, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_chemicalsFBO2 = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_resolutionX, m_resolutionY, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
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
    QImage img = QImage(settings.imagePath); // TODO: Add error checking

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, img.bits());

    FBO->bind();
    glUseProgram(m_chemicalInitProgram);

    GLint locTex = glGetUniformLocation(m_chemicalInitProgram, "tex");
    glUniform1i(locTex, 0);

    m_quad->draw();
    FBO->unbind();
}

void GLWidget::updateChemicals(std::shared_ptr<FBO> prevFBO, std::shared_ptr<FBO> nextFBO) {
    // TODO [Task 14] Move the particles from prevFBO to nextFBO while updating them
    nextFBO->bind();
    glUseProgram(m_chemicalUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();

    // Sends uniforms containing the previous state of the simulation
    GLint locResolutionX = glGetUniformLocation(m_chemicalUpdateProgram, "resolutionX");
    glUniform1i(locResolutionX, m_resolutionX);
    GLint locResolutionY = glGetUniformLocation(m_chemicalUpdateProgram, "resolutionY");
    glUniform1i(locResolutionY, m_resolutionY);
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
    glUniform1f(locFeedRate, settings.feedRate / 10.f); // TODO: this is shitty style
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
    setParticleViewport();

    glActiveTexture(GL_TEXTURE0);
    FBO->getColorAttachment(0).bind(); // TODO: unbind?

    GLint locTex = glGetUniformLocation(m_chemicalDrawProgram, "tex");
    glUniform1i(locTex, 0);
    GLint locResolutionX = glGetUniformLocation(m_chemicalDrawProgram, "resolutionX");
    glUniform1i(locResolutionX, m_resolutionX);
    GLint locResolutionY = glGetUniformLocation(m_chemicalDrawProgram, "resolutionY");
    glUniform1i(locResolutionY, m_resolutionY);

    m_quad->draw();
    FBO->getColorAttachment(0).unbind();
}

// This is called at the beginning of the program between initializeGL and
// the first paintGL call, as well as every time the window is resized.
void GLWidget::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    rebuildMatrices();
}

// Sets the viewport to ensure that {0,0} is always in the center of the viewport
// in clip space, and to ensure that the aspect ratio is 1:1
void GLWidget::setParticleViewport() {
    int maxDim = std::max(m_width, m_height);
    int x = (m_width - maxDim) / 2.0f;
    int y = (m_height - maxDim) / 2.0f;
    glViewport(x, y, maxDim, maxDim);
}

/// Mouse interaction code below.

void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_angleX += 3 * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 3 * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 100.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = glm::translate(glm::vec3(0, 0, -m_zoom)) *
             glm::rotate(m_angleY, glm::vec3(1,0,0)) *
             glm::rotate(m_angleX, glm::vec3(0,1,0));

    m_projection = glm::perspective(0.8f, (float)width()/height(), 0.1f, 100.f);
    update();
}
