#include "Shader.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GlFuncs.h"

//-----------------------------------------------------------------------------

Shader::Shader(GlFuncs* gl_funcs, ShaderType type)
   :m_gl_funcs(gl_funcs),
    m_type(type)
{
   if (type == ShaderType::VERTEX)
      m_id = m_gl_funcs->glCreateShader(GL_VERTEX_SHADER);
   else if (type == ShaderType::GEOMETRY)
      m_id = m_gl_funcs->glCreateShader(GL_GEOMETRY_SHADER);
   else if (type == ShaderType::FRAGMENT)
      m_id = m_gl_funcs->glCreateShader(GL_FRAGMENT_SHADER);
   else
      throw std::runtime_error("Unsupported ShaderType");
}

//-----------------------------------------------------------------------------

Shader::Shader(
   GlFuncs* gl_funcs, 
   ShaderType type, 
   const std::string& fname)
   :Shader(gl_funcs, type)
{
   if (fname.empty() == true)
      throw std::runtime_error("Empty path to shader file");

   std::string source = Shader::readFromFile(fname);
   compile(source);
}

//-----------------------------------------------------------------------------

Shader::~Shader()
{
   m_gl_funcs->glDeleteShader(m_id);
}

//-----------------------------------------------------------------------------

Shader::Shader(Shader&& shader)
   :m_gl_funcs(shader.m_gl_funcs),
    m_type(shader.m_type),
    m_id(shader.m_id)
{
   shader.m_id = 0; // 0 is silently ignored by OpenGl
}


Shader& 
Shader::operator=(Shader&& shader)
{
   m_gl_funcs = shader.m_gl_funcs;
   m_type = shader.m_type;
   m_id = shader.m_id;
   shader.m_id = 0; // 0 is silently ignored by OpenGl
   return *this;
}

//-----------------------------------------------------------------------------

void 
Shader::compile(const std::string& source)
{
   const GLchar* source_ptr = source.c_str();
   m_gl_funcs->glShaderSource(m_id, 1, &source_ptr, nullptr);
   m_gl_funcs->glCompileShader(m_id);

   // Check compile status
   GLint status;
   m_gl_funcs->glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
   if (status != GL_TRUE)
   {
       GLsizei log_length = 0;
       GLchar message[1024];
       m_gl_funcs->glGetShaderInfoLog(m_id, 1024, nullptr, message);
       throw std::runtime_error(message);
   }
}

//-----------------------------------------------------------------------------

std::string 
Shader::readFromFile(const std::string& fname)
{
   std::ifstream ifs(fname);
   std::stringstream buffer;
   buffer << ifs.rdbuf();
   return buffer.str(); 
}

//-----------------------------------------------------------------------------
