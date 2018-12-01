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

   void resizeWindow(float window_width, float window_height);
   
private:

   glm::vec3 windowToScene(const glm::vec3& w_point) const;
   glm::vec3 sceneToWindow(const glm::vec3& w_point) const;
   
   ImageRenderer* m_renderer;
   Camera m_camera;
   float m_window_width;
   float m_window_height;

};
