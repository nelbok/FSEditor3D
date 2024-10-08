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
	include/fse/tools/Settings.hpp
	include/fse/tools/Style.hpp
	include/fse/tools/Tools.hpp

	include/fse/Application.hpp
	include/fse/Manager.hpp

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

	src/tools/About.cpp
	src/tools/Balsam.cpp
	src/tools/DefaultSettings.hpp
	src/tools/FileThread.cpp
	src/tools/LoadThread.cpp
	src/tools/SaveThread.cpp
	src/tools/Settings.cpp
	src/tools/Style.cpp
	src/tools/Tools.cpp

	src/Application.cpp
	src/Manager.cpp

	src/Config.hpp.in

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

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${PROJECT_SOURCES} ${QML_SOURCES})
configure_file(src/Config.hpp.in include/Config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(src)
include_directories(.)

qt_add_library(${CFS_EUI} STATIC ${PROJECT_SOURCES})
qt_add_qml_module(${CFS_EUI} URI editor VERSION 1.0 QML_FILES ${QML_SOURCES})
qt_add_translations(${CFS_EUI} TS_FILES ${TRANSLATION_FILES} RESOURCE_PREFIX "/translations")

target_include_directories(${CFS_EUI} PUBLIC include)
target_link_libraries(${CFS_EUI} PRIVATE Qt6::Quick Qt6::Quick3D Qt6::Quick3DPhysics ${CFS_DATA})