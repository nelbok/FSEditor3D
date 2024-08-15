qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	src/commands/BaseCommand.cpp
	src/commands/BaseCommand.hpp
	src/commands/Commands.cpp
	src/commands/Commands.hpp
	src/commands/CreateCommand.hpp
	src/commands/DuplicateCommand.hpp
	src/commands/EntityCommand.cpp
	src/commands/EntityCommand.hpp
	src/commands/GeometryCommand.cpp
	src/commands/GeometryCommand.hpp
	src/commands/LinkCommand.cpp
	src/commands/LinkCommand.hpp
	src/commands/ModelCommand.cpp
	src/commands/ModelCommand.hpp
	src/commands/ObjectCommand.cpp
	src/commands/ObjectCommand.hpp
	src/commands/PlaceCommand.cpp
	src/commands/PlaceCommand.hpp
	src/commands/PlacementCommand.cpp
	src/commands/PlacementCommand.hpp
	src/commands/ProjectCommand.cpp
	src/commands/ProjectCommand.hpp
	src/commands/RemoveCommand.hpp
	src/commands/ShapeCommand.cpp
	src/commands/ShapeCommand.hpp
	src/commands/ValueCommand.hpp

	src/managers/CommandsManager.cpp
	src/managers/CommandsManager.hpp
	src/managers/ModelsManager.cpp
	src/managers/ModelsManager.hpp
	src/managers/SelectionManager.cpp
	src/managers/SelectionManager.hpp
	src/managers/StylesManager.cpp
	src/managers/StylesManager.hpp
	src/managers/TranslationsManager.cpp
	src/managers/TranslationsManager.hpp

	src/models/EntityModel.cpp
	src/models/EntityModel.hpp
	src/models/LinkModel.cpp
	src/models/LinkModel.hpp
	src/models/ModelModel.cpp
	src/models/ModelModel.hpp
	src/models/ObjectModel.cpp
	src/models/ObjectModel.hpp
	src/models/PlaceModel.cpp
	src/models/PlaceModel.hpp
	src/models/ProxyModel.cpp
	src/models/ProxyModel.hpp
	src/models/SelectionWrapper.cpp
	src/models/SelectionWrapper.hpp

	src/tools/About.cpp
	src/tools/About.hpp
	src/tools/Balsam.cpp
	src/tools/Balsam.hpp
	src/tools/FileThread.cpp
	src/tools/FileThread.hpp
	src/tools/LoadThread.cpp
	src/tools/LoadThread.hpp
	src/tools/SaveThread.cpp
	src/tools/SaveThread.hpp
	src/tools/Style.cpp
	src/tools/Style.hpp
	src/tools/Tools.cpp
	src/tools/Tools.hpp

	src/Config.hpp.in
	src/main.cpp
	src/Manager.cpp
	src/Manager.hpp

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

	qml/modules/FSELinks.qml
	qml/modules/FSEMenu.qml
	qml/modules/FSEMessageBox.qml
	qml/modules/FSEModels.qml
	qml/modules/FSEObjects.qml
	qml/modules/FSEPlaces.qml
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