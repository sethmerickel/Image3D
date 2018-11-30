#include <iostream>
#include <exception>

#include <QtGui/QGuiApplication>
#include <QtGui/QSurfaceFormat>
#include <QtQuick/QQuickView>

#include "FboRendererManager.h"

int main(int argc, char** argv)
{
   int rslt = 0;
   try
   {
      // Set the surface format to get OpenGL version > 2.0
      QSurfaceFormat format;     
      format.setProfile(QSurfaceFormat::CoreProfile);
      format.setVersion(4,1);
      QSurfaceFormat::setDefaultFormat(format);

      QGuiApplication app(argc, argv);

      qmlRegisterType<FboRendererManager>("Image3D", 1, 0, "FboRendererManager");

      QQuickView view;
      view.setResizeMode(QQuickView::SizeRootObjectToView);
      view.setSource(QUrl("qrc:///main.qml"));
      view.show();

      rslt = app.exec();
   }
   catch (std::exception& e)
   {
      std::cout << "Exception!! - " << e.what() << std::endl;
      exit(1);
   }
   catch (...)
   {
      std::cout << "Something aweful happened!!" << std::endl;
      exit(1);
   }

   return rslt;
}
