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

      onWheel: 
      {
         fbo_renderer_manager.setZoomAngleDelta(wheel.angleDelta.y)
         //console.log("angleDelta: " + wheel.angleDelta)
      }

      onPressed:
      {
         //console.log("here")
         //console.log("pressed x:) //" + mouse.x + " y: " mouse.y) 
      }

      onPositionChanged:
      {
         //fbo_rendeerer_manager.moveCamera(mouse.x, mouse.y)
      }

      onReleased:
      {
         
      }
   }
}
