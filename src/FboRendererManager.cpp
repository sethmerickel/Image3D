#include "FboRendererManager.h"

#include "GlFuncs.h"

#include "ImageRenderer.h"

FboRendererManager::FboRendererManager()
   :QQuickFramebufferObject()
{
   setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer* 
FboRendererManager::createRenderer() const
{
   GlFuncs* gl_funcs = getGlFuncs();

   //m_renderer = new ImageRenderer(gl_funcs); 
   //return m_renderer;
   return new ImageRenderer(gl_funcs); 

}
