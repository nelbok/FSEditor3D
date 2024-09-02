qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	include/fse/commands/BaseCommand.hpp
	include/fse/commands/Commands.hpp
	include/fse/commands/CreateCommand.hpp
	include/fse/commands/DuplicateCommand.hpp
	include/fse/commands/EntityCommand.hpp
	include/fse/commands/GeometryCommand.hpp
	include/fse/commands/LinkCommand.hpp
	include/fse/commands/ModelCommand.hpp
	include/fse/commands/ObjectCommand.hpp
	include/fse/commands/PlaceCommand.hpp
	include/fse/commands/PlacementCommand.hpp
	include/fse/commands/ProjectCommand.hpp
	include/fse/commands/RemoveCommand.hpp
	include/fse/commands/ShapeCommand.hpp
	include/fse/commands/ValueCommand.hpp

	include/fse/managers/CommandsManager.hpp
	include/fse/managers/ErrorsManager.hpp
	include/fse/managers/FileManager.hpp
	include/fse/managers/ModelsManager.hpp
	include/fse/managers/PreviewManager.hpp
	include/fse/managers/SelectionManager.hpp
	include/fse/managers/StylesManager.hpp
	include/fse/managers/TranslationsManager.hpp

	include/fse/models/EntityModel.hpp
	include/fse/models/LinkModel.hpp
	include/fse/models/ModelModel.hpp
	include/fse/models/ObjectModel.hpp
	include/fse/models/PlaceModel.hpp
	include/fse/models/ProxyModel.hpp
	include/fse/models/SelectionWrapper.hpp

	include/fse/tools/About.hpp
	include/fse/tools/Balsam.hpp
	include/fse/tools/FileThread.hpp
	include/fse/tools/LoadThread.hpp
	include/fse/tools/SaveThread.hpp
	include/fse/tools/Style.hpp
	include/fse/tools/Tools.hpp

	include/fse/Manager.hpp

	src/tools/About.cpp
	src/tools/Balsam.cpp
	src/tools/FileThread.cpp
	src/tools/LoadThread.cpp
	src/tools/SaveThread.cpp
	src/tools/Style.cpp
	src/tools/Tools.cpp

	src/commands/BaseCommand.cpp
	src/commands/Commands.cpp
	src/commands/EntityCommand.cpp
	src/commands/GeometryCommand.cpp
	src/commands/LinkCommand.cpp
	src/commands/ModelCommand.cpp
	src/commands/ObjectCommand.cpp
	src/commands/PlaceCommand.cpp
	src/commands/PlacementCommand.cpp
	src/commands/ProjectCommand.cpp
	src/commands/ShapeCommand.cpp

	src/managers/CommandsManager.cpp
	src/managers/ErrorsManager.cpp
	src/managers/FileManager.cpp
	src/managers/ModelsManager.cpp
	src/managers/PreviewManager.cpp
	src/managers/SelectionManager.cpp
	src/managers/StylesManager.cpp
	src/managers/TranslationsManager.cpp

	src/models/EntityModel.cpp
	src/models/LinkModel.cpp
	src/models/ModelModel.cpp
	src/models/ObjectModel.cpp
	src/models/PlaceModel.cpp
	src/models/ProxyModel.cpp
	src/models/SelectionWrapper.cpp

	src/Config.hpp.in
	src/main.cpp
	src/Manager.cpp

	resources/resource.h
	resources/logo.ico
	resources/resources.rc.in
	resources/resources.qrc
)
set(QML_SOURCES
	qml/3d/FSETransformNode.qml
	qml/3d/FSEView3D.qml
	qml/3d/ModelLoader.js

	qml/common/FSEButton.qml
	qml/common/FSEColorField.qml
	qml/common/FSEComboBox.qml
	qml/common/FSEField.qml
	qml/common/FSEIconButton.qml
	qml/common/FSEList.qml
	qml/common/FSEMenuButton.qml
	qml/common/FSEModule.qml
	qml/common/FSERectangle.qml
	qml/common/FSESpinBox.qml
	qml/common/FSEText.qml
	qml/common/FSETextField.qml
	qml/common/FSEToolButton.qml
	qml/common/FSEVector3DField.qml

	qml/data/FSEEntity.qml
	qml/data/FSEGeometry.qml
	qml/data/FSEPlacement.qml
	qml/data/FSEShape.qml

	qml/modules/settings/FSESettingsAbout.qml
	qml/modules/settings/FSESettingsInterface.qml

	qml/modules/FSELinks.qml
	qml/modules/FSEMenu.qml
	qml/modules/FSEMessageBox.qml
	qml/modules/FSEModels.qml
	qml/modules/FSEObjects.qml
	qml/modules/FSEPlaces.qml
	qml/modules/FSEPreviewBar.qml
	qml/modules/FSEProgressBox.qml
	qml/modules/FSEProject.qml
	qml/modules/FSESettings.qml
	qml/modules/FSEToolBar.qml

	qml/Main.qml
)

set(TRANSLATION_FILES
    translations/app_en.ts
    translations/app_fr.ts
)

configure_file(resources/resources.rc.in resources/resources.rc)
configure_file(resources/resource.h resources/resource.h COPYONLY)
configure_file(resources/logo.ico resources/logo.ico COPYONLY)

set(OTHER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/resources/resources.rc
)

qt_add_executable(${CFS_EDITOR} ${PROJECT_SOURCES} ${OTHER_FILES})
qt_add_qml_module(${CFS_EDITOR} URI editor VERSION 1.0 QML_FILES ${QML_SOURCES})
qt_add_translations(${CFS_EDITOR} TS_FILES ${TRANSLATION_FILES} RESOURCE_PREFIX "/translations")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES} ${QML_SOURCES} ${QML_SINGLETON})
include_directories(src)

# Balsam
get_target_property(BALSAM_LOCATION Qt6::balsam IMPORTED_LOCATION)
if(WIN32)
	get_filename_component(FS_BALSAM ${BALSAM_LOCATION} NAME)
elseif(LINUX)
	set(FS_BALSAM ${BALSAM_LOCATION})
endif()

configure_file(src/Config.hpp.in include/Config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

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

target_include_directories(${CFS_EDITOR} PUBLIC include)
target_link_libraries(${CFS_EDITOR} PRIVATE Qt6::Quick Qt6::Quick3D Qt6::Quick3DPhysics ${CFS_DATA})

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
	add_custom_command(TARGET ${CFS_EDITOR} POST_BUILD COMMAND ${DEPLOYQT} --qmldir "${CMAKE_CURRENT_SOURCE_DIR}/qml" "$<TARGET_FILE:${CFS_EDITOR}>")
endif()