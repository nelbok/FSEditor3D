qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_DEBUG_POSTFIX _d)
set(PROJECT_SOURCES
	include/fsd/data/Entity.hpp
	include/fsd/data/Link.hpp
	include/fsd/data/Model.hpp
	include/fsd/data/Object.hpp
	include/fsd/data/Place.hpp
	include/fsd/data/Placement.hpp
	include/fsd/data/Project.hpp
	include/fsd/data/Shape.hpp
	include/fsd/data/UuidPointer.hpp
	include/fsd/io/FileManager.hpp
	include/fsd/io/Json.hpp

	src/common/Accessors.hpp
	src/data/Entity.cpp
	src/data/Link.cpp
	src/data/Model.cpp
	src/data/Object.cpp
	src/data/Place.cpp
	src/data/Placement.cpp
	src/data/Project.cpp
	src/data/Shape.cpp
	src/data/UuidPointer.cpp
	src/io/FileManager.cpp
	src/io/Json.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(src)
include_directories(.)

qt_add_library(${CFS_DATA} STATIC ${PROJECT_SOURCES})

target_include_directories(${CFS_DATA} PUBLIC include)
target_link_libraries(${CFS_DATA} PRIVATE Qt6::Core Qt6::Gui)