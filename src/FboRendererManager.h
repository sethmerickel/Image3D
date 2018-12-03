#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include <QtQuick/QQuickFramebufferObject.h>

#include "Camera.h"

class ImageRenderer;


class FboRendererManager : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   
   FboRendererManager();

   Renderer* createRenderer() const;
   
public slots:
   
   void setRenderer(ImageRenderer* renderer);

   void resizeWindow(float window_width, float window_height);
   float getWindowWidth() const;
   float getWindowHeight() const;

   void setZoomAngleDelta(float angle);
   float getZoomAngleDelta() const;
   float getZoomX() const;
   float getZoomY() const;

   void moveCamera(float mouse_x, float mouse_y);

   
private:

   glm::vec3 windowToScene(const glm::vec3& w_point) const;
   glm::vec3 sceneToWindow(const glm::vec3& w_point) const;
   
   ImageRenderer* m_renderer;
   Camera m_camera;
   float m_window_width;
   float m_window_height;
   float m_zoom_angle_delta;
   float m_zoom_x;
   float m_zoom_y;
};
