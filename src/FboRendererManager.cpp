#include "FboRendererManager.h"

#include <memory>

#include "GlFuncs.h"

#include "ImageRenderer.h"
#include "Layer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Triangle.h"

//-----------------------------------------------------------------------------

FboRendererManager::FboRendererManager()
   :QQuickFramebufferObject(),
    m_renderer(nullptr),
    m_camera(),
    m_window_width(-1.0f),
    m_window_height(-1.0f),
    m_zoom_angle_delta(0.0f),
    m_zoom_x(0.0f),
    m_zoom_y(0.0f)
{
   setMirrorVertically(true);
}

//-----------------------------------------------------------------------------

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
   Camera camera;
   camera.setViewWidth(texture.getWidth());
   camera.setViewHeight(texture.getHeight());

   Triangle triangle{gl_funcs, sp, std::move(texture)};

   Layer layer{gl_funcs, std::move(sp), std::move(triangle)};

   return new ImageRenderer(gl_funcs, std::move(layer), camera); 
}

//-----------------------------------------------------------------------------

void 
FboRendererManager::setRenderer(ImageRenderer* renderer)
{
   m_renderer = renderer;
}

//-----------------------------------------------------------------------------

void 
FboRendererManager::resizeWindow(float window_width, float window_height)
{
   m_window_width = window_width;
   m_window_height = window_height;
}

//-----------------------------------------------------------------------------

float 
FboRendererManager::getWindowWidth() const
{
   return m_window_width; 
}

//-----------------------------------------------------------------------------

float 
FboRendererManager::getWindowHeight() const
{
   return m_window_height;
}

//-----------------------------------------------------------------------------

void 
FboRendererManager::setZoomAngleDelta(float angle)
{
   m_renderer->zoom(angle);
}

//-----------------------------------------------------------------------------

float 
FboRendererManager::getZoomAngleDelta() const
{
   return m_zoom_angle_delta;
}

//-----------------------------------------------------------------------------

float
FboRendererManager::getZoomX() const
{
   return m_zoom_x;
}

//-----------------------------------------------------------------------------

float 
FboRendererManager::getZoomY() const
{
   return m_zoom_y;
}

//-----------------------------------------------------------------------------

void 
FboRendererManager::moveCamera(float mouse_x, float mouse_y)
{

}

//-----------------------------------------------------------------------------

//glm::vec3 
//FboRendererManager::windowToScene(const glm::vec3& w_point) const
//{
//
//}

//-----------------------------------------------------------------------------
   
//glm::vec3 
//FboRendererManager::sceneToWindow(const glm::vec3& w_point) const
//{
//
//}

//-----------------------------------------------------------------------------
