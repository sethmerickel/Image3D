#pragma once

#include <QtQuick/QQuickFramebufferObject.h>

class FboRendererFactory : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   Renderer* createRenderer() const;
};
