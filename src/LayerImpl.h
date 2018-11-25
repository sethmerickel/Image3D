#pragma once

#include "Drawable.hpp"
#include "GlFuncs.h"
#include "Layer.h"


class LayerImpl : public Layer
{
public:
   LayerImpl(
      GlFuncs* gl_funcs,
      ShaderProgram&& sp, 
      Drawable&& drawable);

   virtual ~LayerImpl(); 

   virtual void draw() override;
   virtual void reload() override;
  
private:
   GlFuncs* m_gl_funcs;
   ShaderProgram m_sp;
   Drawable m_drawable;
};


