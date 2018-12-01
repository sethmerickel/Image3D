import QtQuick 2.0

import Image3D 1.0

Item 
{
   width: 400
   height: 400

   FboRendererManager 
   {
      id: fbo_renderer_manager
      anchors.fill: parent
      anchors.margins: 10
      width: parent.width
      height: parent.height

      Component.onCompleted:
      {
         resizeWindow(width, height)
      }

      onWidthChanged:
      {
         resizeWindow(width, height)
      }

      onHeightChanged:
      {
         resizeWindow(width, height)
      }
   }

   MouseArea
   {
      anchors.fill: parent
      onClicked: 
      {
         console.log("Clicked")
         console.log("x: " + mouse.x + " y: " + mouse.y)
      }
   }
}
