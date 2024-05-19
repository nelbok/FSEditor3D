qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_DEBUG_POSTFIX _d)
set(PROJECT_SOURCES
	include/lh/data/Character.hpp
	include/lh/data/Entity.hpp
	include/lh/data/Link.hpp
	include/lh/data/Model.hpp
	include/lh/data/Place.hpp
	include/lh/data/Placement.hpp
	include/lh/data/Project.hpp
	include/lh/data/UuidPointer.hpp
	include/lh/io/Json.hpp

	src/common/Tools.cpp
	src/common/Tools.hpp
	src/data/Character.cpp
	src/data/Entity.cpp
	src/data/Link.cpp
	src/data/Model.cpp
	src/data/Place.cpp
	src/data/Placement.cpp
	src/data/Project.cpp
	src/data/UuidPointer.cpp
	src/io/Json.cpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(src)
include_directories(.)

qt_add_library(${CLH_DATA} STATIC ${PROJECT_SOURCES})

target_include_directories(${CLH_DATA} PUBLIC include)
target_link_libraries(${CLH_DATA} PRIVATE Qt6::Core Qt6::Gui)