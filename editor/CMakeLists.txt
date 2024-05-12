qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	src/controllers/About.cpp
	src/controllers/About.hpp
	src/controllers/Controller.cpp
	src/controllers/Controller.hpp
	src/main.cpp

	src/Config.hpp.in

	resources/resource.h
	resources/logo.ico
	resources/resources.rc.in
	resources/resources.qrc
)
set(QML_SOURCES
	qml/common/LHEButton.qml
	qml/common/LHEColorField.qml
	qml/common/LHEComboBox.qml
	qml/common/LHEField.qml
	qml/common/LHEIconButton.qml
	qml/common/LHEList.qml
	qml/common/LHEMenuButton.qml
	qml/common/LHEModule.qml
	qml/common/LHERectangle.qml
	qml/common/LHESpinBox.qml
	qml/common/LHETextField.qml
	qml/common/LHEVector3DField.qml
	qml/data/LHEEntity.qml
	qml/data/LHEPlacement.qml
	qml/modules/LHECharacters.qml
	qml/modules/LHELinks.qml
	qml/modules/LHEMenu.qml
	qml/modules/LHEPlaces.qml
	qml/modules/LHEProject.qml
	qml/Main.qml
)
set(QML_SINGLETON
	qml/style/LHEStyle.qml
)
set_source_files_properties(${QML_SINGLETON} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

configure_file(resources/resources.rc.in resources/resources.rc)
configure_file(resources/resource.h resources/resource.h COPYONLY)
configure_file(resources/logo.ico resources/logo.ico COPYONLY)
set(OTHER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/resources/resources.rc
)

qt_add_executable(${CLH_EDITOR} ${PROJECT_SOURCES} ${OTHER_FILES})
qt_add_qml_module(${CLH_EDITOR} URI editor VERSION 1.0 QML_FILES ${QML_SOURCES} ${QML_SINGLETON})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES} ${QML_SOURCES} ${QML_SINGLETON})
include_directories(src)

configure_file(src/Config.hpp.in include/Config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${CLH_EDITOR} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER com.${FS_ORGANIZATION}.${CLH_EDITOR}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

target_link_libraries(${CLH_EDITOR} PRIVATE Qt6::Quick Qt6::Quick3D Qt6::Quick3DPhysics ${CLH_DATA})

include(GNUInstallDirs)
install(TARGETS ${CLH_EDITOR}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if(WIN32)
	windeployqt(${CLH_EDITOR} QMLDIR "${CMAKE_CURRENT_SOURCE_DIR}/qml")
endif()