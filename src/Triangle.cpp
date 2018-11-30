#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>

#include "GlFuncs.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Triangle.h"


//-----------------------------------------------------------------------------

Triangle::Triangle(
   GlFuncs* gl_funcs,
   const ShaderProgram& sp,
   Texture&& texture)
   :m_gl_funcs(gl_funcs),
    m_texture(std::move(texture))
 {
   m_gl_funcs->glGenVertexArrays(1, &m_vao_id);
   m_gl_funcs->glBindVertexArray(m_vao_id);
   m_gl_funcs->glGenBuffers(1, &m_vbo_id);
   m_gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   
   GLfloat vertexData[] = {
      //  X     Y     Z       U     V
      0.0f, 0.8f, 0.0f,   0.5f, 0.0f,
     -0.8f,-0.8f, 0.0f,   0.0f, 1.0f,
      0.8f,-0.8f, 0.0f,   1.0f, 1.0f,
   };

   m_gl_funcs->glBufferData(
      GL_ARRAY_BUFFER, 
      sizeof(vertexData), 
      vertexData, 
      GL_STATIC_DRAW); 
   
   m_gl_funcs->glEnableVertexAttribArray(sp.attrib("vert"));
   m_gl_funcs->glVertexAttribPointer(
      sp.attrib("vert"),
      3,
      GL_FLOAT,
      GL_FALSE,
      5*sizeof(GLfloat),
      nullptr);

   m_gl_funcs->glEnableVertexAttribArray(sp.attrib("vertTexCoord"));
   m_gl_funcs->glVertexAttribPointer(
      sp.attrib("vertTexCoord"),
      2,
      GL_FLOAT,
      GL_TRUE,
      5*sizeof(GLfloat), 
      (const GLvoid*)(3 * sizeof(GLfloat)));

   m_gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, 0);
   m_gl_funcs->glBindVertexArray(0); 
}

//-----------------------------------------------------------------------------

Triangle::Triangle(Triangle&& tri)
   :m_gl_funcs(tri.m_gl_funcs),
    m_vbo_id(tri.m_vbo_id),
    m_vao_id(tri.m_vao_id),
    m_ebo_id(tri.m_ebo_id),
    m_texture(std::move(tri.m_texture))
{
}

//-----------------------------------------------------------------------------

Triangle& Triangle::operator=(Triangle&& rhs)
{
   std::swap(m_gl_funcs, rhs.m_gl_funcs);
   std::swap(m_vbo_id, rhs.m_vbo_id); 
   std::swap(m_vao_id, rhs.m_vao_id);
   std::swap(m_ebo_id, rhs.m_ebo_id);
   std::swap(m_texture, rhs.m_texture);
   return *this;
}

//-----------------------------------------------------------------------------

void draw(Triangle& triangle, ShaderProgram& sp)
{
   GlFuncs* gl_funcs = triangle.m_gl_funcs;
   sp.use();
   
   // Set sampler uniform
   GLint uni_loc = gl_funcs->glGetUniformLocation(sp.getId(), "tex");
   gl_funcs->glUniform1i(uni_loc, 0); // TODO: Texture class needs to manage this

   gl_funcs->glBindVertexArray(triangle.m_vao_id);

   gl_funcs->glActiveTexture(GL_TEXTURE0); // TODO: Texture class needs to manage this
   triangle.m_texture.bind();

   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   gl_funcs->glDrawArrays(GL_TRIANGLES, 0, 3);
   
   gl_funcs->glBindVertexArray(0);
   triangle.m_texture.unBind();
   sp.unUse();
}

//-----------------------------------------------------------------------------

void 
update(Triangle& triangle)
{
   // Nothing to update 
}

//-----------------------------------------------------------------------------

