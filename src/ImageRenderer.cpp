#include "ImageRenderer.h"

#include <iostream>

#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>

#include "GlFuncs.h"
#include "LayerImpl.h"
#include "ShaderProgram.h"
#include "Triangle.h"


ImageRenderer::ImageRenderer(GlFuncs* gl_funcs)
   :m_layers(),
    m_gl_funcs(gl_funcs),
    m_fbo(nullptr)
{
   // Add some stuff to draw 
   ShaderProgram sp{
      m_gl_funcs,
      "src/Shaders/shader.vs", 
      "", 
      "src/Shaders/shader.fs"};

   std::cout << "Here I am" << std::endl;

   Triangle triangle{m_gl_funcs, sp};

   m_layers.emplace_back(
      new LayerImpl{m_gl_funcs, std::move(sp), std::move(triangle)});
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
   
   for (auto& layer : m_layers)
   {
      layer->draw();
   }

   if (m_fbo)
   {
      std::cout << "reseting state" << std::endl;
      m_fbo->window()->resetOpenGLState();
   }
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
