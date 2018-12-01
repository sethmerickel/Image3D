#include "Layer.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"


//------------------------------------------------------------------------------
Layer::Layer(
   GlFuncs* gl_funcs,
   ShaderProgram&& sp, 
   Drawable&& drawable) 
  :m_gl_funcs(gl_funcs),
   m_sp(std::move(sp)),
   m_drawable(std::move(drawable))
{

}

//------------------------------------------------------------------------------

Layer::~Layer()
{

}

//------------------------------------------------------------------------------

Layer::Layer(Layer&& rhs)
  :m_gl_funcs(rhs.m_gl_funcs),
   m_sp(std::move(rhs.m_sp)),
   m_drawable(std::move(rhs.m_drawable))
{

}

//------------------------------------------------------------------------------

Layer& 
Layer::operator=(Layer&& rhs)
{
   m_gl_funcs = rhs.m_gl_funcs;
   std::swap(m_sp, rhs.m_sp);
   std::swap(m_drawable, rhs.m_drawable);
   return *this;
}

//------------------------------------------------------------------------------

void
Layer::reload()
{
   ShaderProgram sp {
      m_gl_funcs,
      m_sp.getVsFname(),
      m_sp.getGsFname(),
      m_sp.getFsFname()};

   m_sp = std::move(sp);
}

//------------------------------------------------------------------------------

void
Layer::draw()
{
   m_sp.use();
   
   m_drawable.draw(m_sp);
  
   m_sp.unUse(); 

}

//------------------------------------------------------------------------------

void
Layer::draw(const Camera& camera)
{
   m_sp.use();
   
   glm::mat4 proj = camera.getTransform();
   m_sp.setUniformMat4("proj", glm::value_ptr(proj)); 
   m_drawable.draw(m_sp);
   
   m_sp.unUse(); 

}

