# Foxxy Soft Editor 3D

## About

Create a project with multiple places and a starting place.
- Using Balsam to convert 3D models into QML files
- Using JSON as the file format
- One model can be used as many as places, objects or links
- Links are used to have a connection between places
- Objects are used inside places

## Requirements

- CMake 3.27+
- C++ 20
- Qt6 Quick 

## Compilation

- cmake -B build
- cmake --build build

If you need to specify Qt location, add this to the first call of CMake: -D "CMAKE_PREFIX_PATH=Path to Qt"
If you need to compile FSData as shared library, add this to the first call of CMake: -D FS_SHARED=ON
