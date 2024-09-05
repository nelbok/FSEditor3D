qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	data/TestAccessors.hpp
	data/TestCompare.hpp
	data/TestIO.hpp
	data/TestLists.hpp
	data/TestRefs.hpp

	editor/TestBalsam.hpp
	editor/TestStyles.hpp
	editor/TestTranslations.hpp

	Dummy.hpp
	Tests.cpp
)

enable_testing()
qt_add_executable(Tests ${PROJECT_SOURCES})
add_test(NAME Tests COMMAND Tests)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(.)

target_link_libraries(Tests PRIVATE Qt6::Core Qt6::Gui Qt6::Test ${CFS_EUI} ${CFS_DATA})
if(WIN32)
	get_target_property(DEPLOYQT Qt6::windeployqt IMPORTED_LOCATION)
	add_custom_command(TARGET Tests POST_BUILD COMMAND ${DEPLOYQT} "$<TARGET_FILE:Tests>")
endif()
