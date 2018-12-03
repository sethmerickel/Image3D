#include "ImageRenderer.h"

#include <iostream>

#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>

#include "FboRendererManager.h"
#include "GlFuncs.h"
#include "Layer.h"
#include "ShaderProgram.h"
#include "Triangle.h"


namespace
{
   float ZOOM_SPEED = 0.01;
   float ZOOM_MIN = 0.0;
   float ZOOM_MAX = 100.0;
};

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

ImageRenderer::~ImageRenderer()
{

}

//------------------------------------------------------------------------------

void
ImageRenderer::render()
{
   m_gl_funcs->glClearColor(0.0, 0.0, 0.001, 1.0);
   m_gl_funcs->glClear(GL_COLOR_BUFFER_BIT);
   m_gl_funcs->glDisable(GL_DEPTH_TEST);
   
   m_layer.draw(m_camera);

   assert(m_fbo != nullptr);
   m_fbo->window()->resetOpenGLState();
   update();
}

//------------------------------------------------------------------------------

QOpenGLFramebufferObject* 
ImageRenderer::createFramebufferObject(const QSize &size) 
{
   QOpenGLFramebufferObjectFormat format;
   format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
   format.setSamples(4);
   return new QOpenGLFramebufferObject(size, format);
}

//------------------------------------------------------------------------------

void
ImageRenderer::synchronize(QQuickFramebufferObject* fbo)
{

   std::puts("CALLING synchronize()");

   if (m_fbo == nullptr && fbo != nullptr)
   {
      auto* my_fbo = dynamic_cast<FboRendererManager*>(fbo);
      if (my_fbo != nullptr)
      {
         m_fbo = my_fbo;
         m_fbo->setRenderer(this);
      }
   }


   if (m_fbo != nullptr)
   {
      setWindowSize(m_fbo->getWindowWidth(), m_fbo->getWindowHeight());
   }

   //   float zoom_angle = m_fbo->getZoomAngleDelta();
   //   
   //   if (zoom_angle > 0.0)
   //   {
   //      auto zoom_x = m_fbo->getZoomX();
   //      auto zoom_y = m_fbo->getZoomY();
   //      auto zoom_delta = zoom_angle * ZOOM_SPEED;
   //      auto cur_zoom = m_camera.getZoomFactor();
   //      cur_zoom += zoom_delta;
   //      m_camera.setZoomFactor(cur_zoom);
   //      m_fbo->setZoomAngleDelta(0.0);
   //   }
   //}
}

//------------------------------------------------------------------------------

void 
ImageRenderer::setWindowSize(float window_width, float window_height)
{
   m_camera.setWindowWidth(window_width);
   m_camera.setWindowHeight(window_height);
}

//------------------------------------------------------------------------------

void 
ImageRenderer::zoom(float angle_delta)
{
   auto zoom_delta = angle_delta * ZOOM_SPEED;
   auto cur_zoom = m_camera.getZoomFactor();
   cur_zoom += zoom_delta;
   if (cur_zoom > ZOOM_MIN && cur_zoom < ZOOM_MAX)
      m_camera.setZoomFactor(cur_zoom);
}
