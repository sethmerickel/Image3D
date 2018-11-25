#pragma once

#include <string>

#include <OpenGL/gl.h>

#include "GlFuncs.h"


class Texture 
{
public:
   Texture(GlFuncs* gl_funcs, const std::string& fname);
   ~Texture();

   // Movable
   Texture(Texture&& rhs);
   Texture& operator=(Texture&& rhs);

   // Not copyable
   Texture(const Texture&) = delete;
   Texture& operator=(const Texture&) = delete;

   GLuint getId() const;
   void bind();
   void unBind();

private:
   GlFuncs* m_gl_funcs;
   GLuint m_id;
   int m_width;
   int m_height;
   int m_channels;
};
