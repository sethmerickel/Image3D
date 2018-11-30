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
