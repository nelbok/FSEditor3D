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
qt_add_executable(tests ${PROJECT_SOURCES})
add_test(NAME tests COMMAND Tests)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(.)

target_link_libraries(tests PRIVATE Qt6::Core Qt6::Gui Qt6::Test ${CFS_EUI} ${CFS_DATA})
if(WIN32)
	# Win deploy qt
	get_target_property(DEPLOYQT Qt6::windeployqt IMPORTED_LOCATION)

	# Deploy Balsam
	add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BALSAM_LOCATION} $<TARGET_FILE_DIR:tests>)
	add_custom_command(TARGET tests POST_BUILD COMMAND ${DEPLOYQT} "$<TARGET_FILE_DIR:tests>/${FS_BALSAM}")

	# Deploy Tests
	add_custom_command(TARGET tests POST_BUILD COMMAND ${DEPLOYQT} "$<TARGET_FILE:tests>")
	add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:tests> $<TARGET_RUNTIME_DLLS:tests> COMMAND_EXPAND_LISTS)
endif()

# Deploy Tests resources
add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/resources/test.mtl" $<TARGET_FILE_DIR:tests>)
add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/resources/test.obj" $<TARGET_FILE_DIR:tests>)