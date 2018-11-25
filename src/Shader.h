#pragma once

#include <string>

#include <OpenGL/gl.h>

#include "GlFuncs.h"


enum class ShaderType : char
{
   VERTEX = 0,
   FRAGMENT,
   GEOMETRY
};

class Shader
{
public:
   Shader(GlFuncs* gl_funcs, ShaderType type);
   
   Shader(
      GlFuncs* gl_funcs,
      ShaderType type,
      const std::string& fname);

   // Move only
   Shader(const Shader&) = delete;

   // Move only
   Shader& operator=(const Shader&) = delete;

   Shader(Shader&& shader);

   Shader& operator=(Shader&& shader);
   
   ~Shader();

   void compile(const std::string& source);

   GLuint getId() { return m_id; }
   
   ShaderType getShaderType() { return m_type; }

   static std::string readFromFile(const std::string& fname);

private:
   GlFuncs* m_gl_funcs;
   std::string m_source; 
   ShaderType m_type;
   GLuint m_id;
};
