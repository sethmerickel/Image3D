#pragma once

#include <iostream>

#include <QtQuick/QQuickFramebufferObject.h>


class ImageRenderer;


class FboRendererManager : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   
   FboRendererManager();

   Renderer* createRenderer() const;

public slots:
   
   //void resizeWindow(float window_width, float window_height);

   //void OnWidthChanged(int width)
   //{
   //   std::cout << "OnWidthChanged(width)" << std::endl;
   //}
   //
private:
   ImageRenderer* m_renderer;

};
