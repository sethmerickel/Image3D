#include "FboRendererManager.h"

#include <memory>

#include "GlFuncs.h"

#include "ImageRenderer.h"
#include "Layer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Triangle.h"

FboRendererManager::FboRendererManager()
   :QQuickFramebufferObject(),
    m_camera()
{
   setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer* 
FboRendererManager::createRenderer() const
{
   GlFuncs* gl_funcs = getGlFuncs();

   ShaderProgram sp{
      gl_funcs,
      "src/Shaders/shader.vs", 
      "", 
      "src/Shaders/shader.fs"};
   
   Texture texture{gl_funcs, "src/textures/wall.jpg"};

   Triangle triangle{gl_funcs, sp, std::move(texture)};

   Layer layer{gl_funcs, std::move(sp), std::move(triangle)};

   //m_renderer = new ImageRenderer(gl_funcs); 
   //return m_renderer;
   return new ImageRenderer(gl_funcs, std::move(layer)); 

}
