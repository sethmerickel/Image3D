#include "FboRendererFactory.h"

#include "GlFuncs.h"

#include "ImageRenderer.h"

QQuickFramebufferObject::Renderer* 
FboRendererFactory::createRenderer() const
{
   GlFuncs* gl_funcs = getGlFuncs();

   return new ImageRenderer(gl_funcs); 
}
