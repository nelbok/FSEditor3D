# Foxxy Soft Editor 3D

## About

Create a project with multiple places and a starting place.
- Using Balsam to convert 3D models into QML file
- One model can be used for one of more places, objects or links
- Links are used to have a connection between places
- Objects can be anything put in a place
- JSON is the file format

## Requirements

- CMake 3.27+
- C++ 17
- Qt6 Quick 

## Compilation

- cmake -B build
- cmake --build build

If you need to specify Qt location, add this to the first call of CMake: -D "CMAKE_PREFIX_PATH=Path to Qt"