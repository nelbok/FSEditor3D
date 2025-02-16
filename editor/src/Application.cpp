#include <fse/Application.hpp>

#include <QtCore/QCommandLineParser>
#include <QtGui/QIcon>

#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/FileManager.hpp>
#include <fse/managers/KeyBindingsManager.hpp>
#include <fse/managers/ModelsManager.hpp>
#include <fse/managers/PreviewManager.hpp>
#include <fse/managers/SelectionManager.hpp>
#include <fse/managers/StylesManager.hpp>
#include <fse/managers/TranslationsManager.hpp>
#include <fse/managers/UpdateManager.hpp>
#include <fse/models/ProxyModel.hpp>
#include <fse/models/SelectionWrapper.hpp>
#include <fse/Config.hpp>

// Q_INIT_RESOURCE must be called outside a namespace
void initResources() {
	Q_INIT_RESOURCE(resources);
}

namespace fse::Application {

void initApp() {
	::initResources();

	QCoreApplication::setOrganizationName(fse::Config::organization);
	QCoreApplication::setApplicationName(fse::Config::name);
	QCoreApplication::setApplicationVersion(fse::Config::version);
	QGuiApplication::setWindowIcon(QIcon(":/logo/logo.png"));
}

bool initParser(const QGuiApplication& app, const Manager& manager) {
	QCommandLineParser parser;
	parser.setApplicationDescription(fse::Config::description);
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption generateStyleOption({ "s", "generate-style" }, "Generate an empty style json file");
	parser.addOption(generateStyleOption);

	// Process the actual command line arguments given by the user
	parser.process(app);

	if (parser.isSet(generateStyleOption)) {
		manager.stylesManager()->createJson();
		return false;
	}

	return true;
}

void initRegister(Manager& manager) {
	// FSData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", manager.project());

	qmlRegisterUncreatableType<fsd::Entity>("editor", 1, 0, "MyEntity", "Attempt to create an Entity");
	qmlRegisterUncreatableType<fsd::Geometry>("editor", 1, 0, "MyGeometry", "Attempt to create a Geometry");
	qmlRegisterUncreatableType<fsd::Placement>("editor", 1, 0, "MyPlacement", "Attempt to create a Placement");
	qmlRegisterUncreatableType<fsd::Shape>("editor", 1, 0, "MyShape", "Attempt to create a Shape");

	qmlRegisterType<fsd::EntryPoint>("editor", 1, 0, "MyEntryPoint");
	qmlRegisterType<fsd::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<fsd::Model>("editor", 1, 0, "MyModel");
	qmlRegisterType<fsd::Object>("editor", 1, 0, "MyObject");
	qmlRegisterType<fsd::Place>("editor", 1, 0, "MyPlace");

	qmlRegisterType<fsd::FileManager>("editor", 1, 0, "MyFileManager");

	// FSEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyManager", &manager);
	qmlRegisterSingletonInstance("editor", 1, 0, "MyCommands", manager.commandsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyErrors", manager.errorsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyFile", manager.fileManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyKeyBindings", manager.keyboardsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyModels", manager.modelsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyPreview", manager.previewManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MySelection", manager.selectionManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyStyles", manager.stylesManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyTranslations", manager.translationsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyUpdate", manager.updateManager());
	qmlRegisterType<fse::ProxyModel>("editor", 1, 0, "MyProxyModel");
	qmlRegisterType<fse::SelectionWrapper>("editor", 1, 0, "MySelectionWrapper");
}

void initEngine(const QGuiApplication& app, QQmlApplicationEngine& engine, const Manager& manager) {
	// Translations
	QObject::connect(manager.translationsManager(), &fse::TranslationsManager::currentUpdated, &engine, &QQmlApplicationEngine::retranslate);

	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.loadFromModule("editor", "Main");
}

} // namespace fse::Application
