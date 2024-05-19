qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	TestAccessors.hpp
	TestCompare.hpp
	TestIO.hpp
	TestLists.hpp
	TestRefs.hpp
	TestSignals.hpp

	Tests.cpp
)

enable_testing()
qt_add_executable(Tests ${PROJECT_SOURCES})
add_test(NAME Tests COMMAND Tests)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(.)

target_link_libraries(Tests PRIVATE Qt6::Core Qt6::Gui Qt6::Test ${CLH_DATA})
if(WIN32)
        windeployqt(Tests)
endif()
if(APPLE)
        macdeployqt(Tests)
endif()
