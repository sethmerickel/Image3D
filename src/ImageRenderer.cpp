#include "ImageRenderer.h"

#include <iostream>

#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>

#include "GlFuncs.h"
#include "LayerImpl.h"
#include "ShaderProgram.h"
#include "Triangle.h"


ImageRenderer::ImageRenderer(GlFuncs* gl_funcs)
   :m_gl_funcs(gl_funcs)
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


void
ImageRenderer::render()
{
   m_gl_funcs->glClearColor(0.0, 1.0, 1.0, 1.0);
   m_gl_funcs->glClear(GL_COLOR_BUFFER_BIT);
}


QOpenGLFramebufferObject* 
ImageRenderer::createFramebufferObject(const QSize &size) 
{
   QOpenGLFramebufferObjectFormat format;
   format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
   format.setSamples(4);
   return new QOpenGLFramebufferObject(size, format);
}