qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	src/main.cpp

	resources/resource.h
	resources/logo.ico
	resources/resources.rc.in
)
set(OTHER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/resources/resources.rc
)

configure_file(resources/resources.rc.in resources/resources.rc)
configure_file(resources/resource.h resources/resource.h COPYONLY)
configure_file(resources/logo.ico resources/logo.ico COPYONLY)

qt_add_executable(${CFS_EDITOR} ${PROJECT_SOURCES} ${OTHER_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES})
include_directories(src)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${CFS_EDITOR} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER com.${FS_ORGANIZATION}.${CFS_EDITOR}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

target_link_libraries(${CFS_EDITOR} PRIVATE ${CFS_EUI} ${CFS_EUI}plugin ${CFS_DATA})

include(GNUInstallDirs)
install(TARGETS ${CFS_EDITOR}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
	# Win deploy qt
	get_target_property(DEPLOYQT Qt6::windeployqt IMPORTED_LOCATION)

	# Deploy Balsam
	add_custom_command(TARGET ${CFS_EDITOR} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BALSAM_LOCATION} $<TARGET_FILE_DIR:${CFS_EDITOR}>)
	add_custom_command(TARGET ${CFS_EDITOR} POST_BUILD COMMAND ${DEPLOYQT} "$<TARGET_FILE_DIR:${CFS_EDITOR}>/${FS_BALSAM}")

	# Deploy editor
	add_custom_command(TARGET ${CFS_EDITOR} POST_BUILD COMMAND ${DEPLOYQT} --qmldir "${CMAKE_CURRENT_SOURCE_DIR}/../editor/qml" "$<TARGET_FILE:${CFS_EDITOR}>")
endif()