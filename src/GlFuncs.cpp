#include "GlFuncs.h"

#include <QtGui/QOpenGLContext>

GlFuncs* getGlFuncs()
{
   auto* context = QOpenGLContext::currentContext();
   if (context->isValid() == false)
      throw std::runtime_error("Invalid context");

   auto* surface = context->surface();
   context->makeCurrent(surface);

   auto* gl_funcs = context->versionFunctions<GlFuncs>();
   
   if (gl_funcs == nullptr)
      throw std::runtime_error("Can't get Qt OpenGL Functions object");

   return gl_funcs;
}
