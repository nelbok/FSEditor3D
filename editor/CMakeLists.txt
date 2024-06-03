qt_standard_project_setup(REQUIRES 6.5)

set(PROJECT_SOURCES
	src/commands/BaseCommand.cpp
	src/commands/BaseCommand.hpp
	src/commands/CharacterCommand.cpp
	src/commands/CharacterCommand.hpp
	src/commands/Commands.cpp
	src/commands/Commands.hpp
	src/commands/CreateCommand.hpp
	src/commands/DuplicateCommand.hpp
	src/commands/EntityCommand.cpp
	src/commands/EntityCommand.hpp
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
	src/commands/ValueCommand.hpp

	src/models/CharacterModel.cpp
	src/models/CharacterModel.hpp
	src/models/EntityModel.cpp
	src/models/EntityModel.hpp
	src/models/LinkModel.cpp
	src/models/LinkModel.hpp
	src/models/ModelModel.cpp
	src/models/ModelModel.hpp
	src/models/PlaceModel.cpp
	src/models/PlaceModel.hpp
	src/models/ProxyModel.cpp
	src/models/ProxyModel.hpp
	src/models/SelectionWrapper.cpp
	src/models/SelectionWrapper.hpp

	src/About.cpp
	src/About.hpp
	src/Balsam.cpp
	src/Balsam.hpp
	src/CommandsManager.cpp
	src/CommandsManager.hpp
	src/Manager.cpp
	src/Manager.hpp
	src/ModelsManager.cpp
	src/ModelsManager.hpp

	src/Config.hpp.in
	src/main.cpp

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
	qml/common/LHEText.qml
	qml/common/LHETextField.qml
	qml/common/LHEToolButton.qml
	qml/common/LHEVector3DField.qml

	qml/data/LHEEntity.qml
	qml/data/LHEObject.qml
	qml/data/LHEPlacement.qml

	qml/modules/LHECharacters.qml
	qml/modules/LHELinks.qml
	qml/modules/LHEMenu.qml
	qml/modules/LHEModels.qml
	qml/modules/LHEPlaces.qml
	qml/modules/LHEProject.qml
	qml/modules/LHEToolBar.qml
	qml/modules/LHEView3D.qml

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

# Balsam
get_target_property(BALSAM_LOCATION Qt6::balsam IMPORTED_LOCATION)
if(WIN32)
	get_filename_component(LH_BALSAM ${BALSAM_LOCATION} NAME)
elseif(LINUX)
	set(LH_BALSAM ${BALSAM_LOCATION})
endif()

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
	# Win deploy qt
	get_target_property(DEPLOYQT Qt6::windeployqt IMPORTED_LOCATION)

	# Deploy Balsam
	add_custom_command(TARGET ${CLH_EDITOR} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BALSAM_LOCATION} $<TARGET_FILE_DIR:${CLH_EDITOR}>)
	add_custom_command(TARGET ${CLH_EDITOR} POST_BUILD COMMAND ${DEPLOYQT} "$<TARGET_FILE_DIR:${CLH_EDITOR}>/${LH_BALSAM}")

	# Deploy editor
	add_custom_command(TARGET ${CLH_EDITOR} POST_BUILD COMMAND ${DEPLOYQT} --qmldir "${CMAKE_CURRENT_SOURCE_DIR}/qml" "$<TARGET_FILE:${CLH_EDITOR}>")
endif()