#pragma once

#include "Texture.h"

#include "GlFuncs.h"


class ShaderProgram;

class Triangle 
{
public:
   Triangle(GlFuncs* gl_funcs, const ShaderProgram& sp);
   Triangle(Triangle&& tri);
   Triangle& operator=(Triangle&& rhs);

   friend void draw(Triangle& triangle, ShaderProgram& sp);
   friend void update(Triangle& triangle);

private:
  GlFuncs* m_gl_funcs;
  GLuint m_vbo_id;
  GLuint m_vao_id;
  GLuint m_ebo_id;
  Texture m_texture;
};
