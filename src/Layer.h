#pragma once

#include <glm/glm.hpp>

#include "Drawable.hpp"
#include "GlFuncs.h"


class Layer
{
public:
   Layer(
      GlFuncs* gl_funcs,
      ShaderProgram&& sp, 
      Drawable&& drawable);

   Layer(Layer&& rhs);
   Layer& operator=(Layer&& rhs);

   // Not copyable
   Layer(const Layer&) = delete;
   Layer& operator=(const Layer&) = delete;


   ~Layer(); 

   void draw();
   void reload();

private:
   GlFuncs* m_gl_funcs;
   ShaderProgram m_sp;
   Drawable m_drawable;
};

