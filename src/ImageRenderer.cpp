#include "ImageRenderer.h"

#include <iostream>

#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>

#include "GlFuncs.h"
#include "Layer.h"
#include "ShaderProgram.h"
#include "Triangle.h"


ImageRenderer::ImageRenderer(
   GlFuncs* gl_funcs, 
   Layer&& layer,
   const Camera& camera)
   :m_layer(std::move(layer)),
    m_gl_funcs(gl_funcs),
    m_fbo(nullptr),
    m_camera(camera),
    m_window_width(-1.0),
    m_window_height(-1.0)
{
   // Add some stuff to draw 
}


ImageRenderer::~ImageRenderer()
{
   std::cout << "~ImageRenderer()" << std::endl;
}


void
ImageRenderer::render()
{
   m_gl_funcs->glClearColor(0.0, 0.0, 0.001, 1.0);
   m_gl_funcs->glClear(GL_COLOR_BUFFER_BIT);
   m_gl_funcs->glDepthMask(GL_FALSE);
   
   m_layer.draw(m_camera);

   assert(m_fbo != nullptr);
   m_fbo->window()->resetOpenGLState();
}


QOpenGLFramebufferObject* 
ImageRenderer::createFramebufferObject(const QSize &size) 
{
   QOpenGLFramebufferObjectFormat format;
   format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
   format.setSamples(4);
   return new QOpenGLFramebufferObject(size, format);
}


void
ImageRenderer::synchronize(QQuickFramebufferObject* fbo)
{
   if (m_fbo == nullptr && fbo != nullptr)
      m_fbo = fbo;
}


void 
ImageRenderer::setWindowSize(float window_width, float window_height)
{
   std::cout << "window width: " << window_width << std::endl;
   m_window_width = window_width;
   m_window_height = window_height;
}
