#include "Camera.h"

#include <iostream>

#include <glm/ext.hpp>

//------------------------------------------------------------------------------

Camera::Camera()
  :m_position(512.0f, 0.0f, 0.0f),
   m_zoom_factor(1.0),
   m_window_width(-1.0),
   m_window_height(-1.0),
   m_view_width(-1.0),
   m_view_height(-1.0)
{

}

//------------------------------------------------------------------------------

void
Camera::setZoomFactor(float zoom_factor)
{
   m_zoom_factor = zoom_factor;
}

//------------------------------------------------------------------------------

float 
Camera::getZoomFactor() const
{
   return m_zoom_factor;
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
   auto left = -m_window_width / m_zoom_factor / 2.0f + m_position.x;
   auto rght =  m_window_width / m_zoom_factor / 2.0f + m_position.x;
   auto topp =  m_window_height / m_zoom_factor / 2.0f + m_position.y;
   auto bttm = -m_window_height / m_zoom_factor / 2.0f + m_position.y;
   
   auto proj = glm::ortho(left, rght, topp, bttm);
   //proj = glm::scale(proj, glm::vec3(m_zoom_factor, m_zoom_factor, 1.0f));

   return proj;
}
