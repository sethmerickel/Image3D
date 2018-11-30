find_package(GLM REQUIRED CONFIG)
message( "GLM FOUND ${GLM_FOUND}" )
message( "GLM INCLUDE DIR ${GLM_INCLUDE_DIRS}" )
message( "CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}" )
include_directories(
   ../include 
   ${GLM_INCLUDE_DIRS}
   ${Qt5Widgets_INCLUDE_DIRS} 
   ${QtQml_INCLUDE_DIRS})

add_definitions(
   ${Qt5Widgets_DEFINITIONS} 
   ${QtQml_DEFINITIONS} 
   ${${Qt5Quick_DEFINITIONS}})

qt5_add_resources(QT_RESOURCES qml.qrc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(PROJECT "Image3D")
project(${PROJECT})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
   "Camera.cpp"
   "FboRendererManager.cpp"
   "GlFuncs.cpp"
   "ImageRenderer.cpp"
   "Layer.cpp"
   "Shader.cpp"
   "ShaderProgram.cpp"
   "Texture.cpp"
   "Triangle.cpp"
   "main.cpp"
   "stb_image.cpp")
set(HEADERS
   "Camera.h"
   "Drawable.hpp"
   "FboRendererManager.h"
   "GlFuncs.h"
   "ImageRenderer.h"
   "Layer.h"
   "Shader.h"
   "ShaderProgram.h"
   "Texture.h"
   "Triangle.h")
if(NOT DEFINED HEADERS)
    file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}⁄*.h)
endif()
if(NOT DEFINED SOURCES)
    file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}⁄*.cpp)
endif()
source_group("Header Files" FILES ${HEADERS})

add_executable(${PROJECT} ${HEADERS} ${SOURCES} ${QT_RESOURCES})
target_link_libraries(${PROJECT} Qt5::Widgets Qt5::Qml Qt5::Quick glm)
