cmake_minimum_required(VERSION 3.27)

include(cmake/defines.cmake)

project(${CFS_EDITOR} VERSION ${FS_VERSION} LANGUAGES CXX)

include(cmake/common.cmake)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Quick Quick3D Quick3DPhysics Test LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Quick Quick3D Quick3DPhysics Test LinguistTools)

include(cmake/deployqt.cmake)

add_subdirectory(data)
add_subdirectory(editor)
add_subdirectory(tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CFS_EDITOR})