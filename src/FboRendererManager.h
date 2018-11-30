#pragma once

#include <iostream>

#include <QtQuick/QQuickFramebufferObject.h>

#include "Camera.h"

class ImageRenderer;


class FboRendererManager : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   
   FboRendererManager();

   Renderer* createRenderer() const;
   
   void resizeWindow(float window_width, float window_height);


public slots:
   
   //void resizeWindow(float window_width, float window_height);

   //void OnWidthChanged(int width)
   //{
   //   std::cout << "OnWidthChanged(width)" << std::endl;
   //}
   //
private:
   ImageRenderer* m_renderer;
   Camera m_camera;


};
