#include <QtQuick/QQuickFramebufferObject.h>

#include <memory>

#include "GlFuncs.h"
#include "Layer.h"


class QOpenGLFramebufferObject;
class QSize;

class ImageRenderer :
   public QQuickFramebufferObject::Renderer
{
public:
   ImageRenderer(GlFuncs* gl_funcs, Layer&& layer);

   // Not copyable
   ImageRenderer(const ImageRenderer&)  = delete;
   ImageRenderer& operator=(const ImageRenderer&) = delete;

   virtual ~ImageRenderer();
   
   void render() override;

   QOpenGLFramebufferObject* 
   createFramebufferObject(const QSize &size) override;
   void synchronize(QQuickFramebufferObject* fbo) override;

private:
     
   Layer m_layer;
   GlFuncs* m_gl_funcs;
   QQuickFramebufferObject* m_fbo;
};

