#pragma once

#include <glm/glm.hpp>

// Camera is in scene coordinates.  This is typically defined by the image 
// that is loaded.  The origin is the center of the image.  x is right and 
// y is up.

class Camera
{
public:
   Camera();

   void setPosition(const glm::vec3& position);

   void setZoomFactor(float zoom_factor);
   float getZoomFactor() const;
   void setWindowWidth(float window_width);
   void setWindowHeight(float window_height);
   void setViewWidth(float view_width);
   void setViewHeight(float view_height);
   
   glm::mat4 getTransform() const;

private:

   glm::vec3 m_position;
   float m_zoom_factor; //Number of screen pixels/image pixels
   float m_window_width;
   float m_window_height;
   float m_view_width;
   float m_view_height;
};
