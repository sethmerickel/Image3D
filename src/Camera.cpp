#include "Camera.h"

#include <iostream>

#include <glm/ext.hpp>

//------------------------------------------------------------------------------

Camera::Camera()
  :m_position(0.0),
   m_window_width(-1.0),
   m_window_height(-1.0),
   m_view_width(-1.0),
   m_view_height(-1.0)
{

}

//------------------------------------------------------------------------------

void 
Camera::setPosition(const glm::vec3& position)
{
   m_position = position;
}

//------------------------------------------------------------------------------
 
void 
Camera::setWindowWidth(float window_width)
{
   m_window_width = window_width;
}

//------------------------------------------------------------------------------

void 
Camera::setWindowHeight(float window_height)
{
   m_window_height = window_height;
}

//------------------------------------------------------------------------------

void 
Camera::setViewWidth(float view_width)
{
   m_view_width = view_width;
}

//------------------------------------------------------------------------------

void 
Camera::setViewHeight(float view_height)
{
   m_view_height = view_height;
}
 
//------------------------------------------------------------------------------

glm::mat4 
Camera::getTransform() const
{
   auto left = -m_view_width/2.0;
   auto rght =  m_view_width/2.0;
   auto topp =  m_view_height/2.0;
   auto bttm = -m_view_height/2.0;
   auto proj = glm::ortho(left, rght, topp, bttm);
   if (m_window_width < m_window_height)
   {
      auto ar = m_window_width / m_window_height;
      proj[1][1] = ar*proj[1][1];
   }
   else
   {
      auto ar = m_window_height / m_window_width;
      proj[0][0] = ar*proj[0][0];
   }
   return proj;
}
