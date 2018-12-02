#include "ImageRenderer.h"

#include <iostream>

#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>

#include "FboRendererManager.h"
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
    m_camera(camera)
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
   {
      auto* my_fbo = dynamic_cast<FboRendererManager*>(fbo);
      if (my_fbo != nullptr) 
         m_fbo = my_fbo;
   }

   if (m_fbo != nullptr)
   {
      setWindowSize(m_fbo->getWindowWidth(), m_fbo->getWindowHeight());
   }
}


void 
ImageRenderer::setWindowSize(float window_width, float window_height)
{
   std::cout << "window width: " << window_width << std::endl;
   m_camera.setWindowWidth(window_width);
   m_camera.setWindowHeight(window_height);
}
