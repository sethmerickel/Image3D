#include <QtQuick/QQuickFramebufferObject.h>

#include <memory>
#include <vector>

#include "GlFuncs.h"
#include "Layer.h"


class QOpenGLFramebufferObject;
class QSize;

class ImageRenderer :
   public QQuickFramebufferObject::Renderer
{
public:
   ImageRenderer(GlFuncs* gl_funcs);
   
   void render() override;

   QOpenGLFramebufferObject* 
   createFramebufferObject(const QSize &size) override;

private:
     
   std::vector<std::unique_ptr<Layer>> m_layers;
   GlFuncs* m_gl_funcs;
};

