#include <QtQuick/QQuickFramebufferObject.h>

#include <memory>

#include "Camera.h"
#include "GlFuncs.h"
#include "Layer.h"

class FboRendererManager;
class QOpenGLFramebufferObject;
class QSize;

class ImageRenderer :
   public QQuickFramebufferObject::Renderer
{
public:
   ImageRenderer(GlFuncs* gl_funcs, Layer&& layer, const Camera& camera);

   // Not copyable
   ImageRenderer(const ImageRenderer&)  = delete;
   ImageRenderer& operator=(const ImageRenderer&) = delete;

   virtual ~ImageRenderer();
   
   void render() override;

   QOpenGLFramebufferObject* 
   createFramebufferObject(const QSize &size) override;
   void synchronize(QQuickFramebufferObject* fbo) override;
   void setWindowSize(float window_width, float window_height);

private:
     
   Layer m_layer;
   GlFuncs* m_gl_funcs;
   FboRendererManager* m_fbo;
   Camera m_camera;
};

