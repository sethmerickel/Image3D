cmake_minimum_required(VERSION 2.8)
# 3rd party tools
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
# Directory with source code
add_subdirectory(src)

# Add third_party include directories
set(THIRD_PARTY_INCLUDE "include")
