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
	qmlRegisterSingletonInstance("eui", 1, 0, "MyProject", manager.project());

	qmlRegisterUncreatableType<fsd::Entity>("eui", 1, 0, "MyEntity", "Attempt to create an Entity");
	qmlRegisterUncreatableType<fsd::Geometry>("eui", 1, 0, "MyGeometry", "Attempt to create a Geometry");
	qmlRegisterUncreatableType<fsd::Placement>("eui", 1, 0, "MyPlacement", "Attempt to create a Placement");
	qmlRegisterUncreatableType<fsd::Shape>("eui", 1, 0, "MyShape", "Attempt to create a Shape");

	qmlRegisterType<fsd::EntryPoint>("eui", 1, 0, "MyEntryPoint");
	qmlRegisterType<fsd::Link>("eui", 1, 0, "MyLink");
	qmlRegisterType<fsd::Model>("eui", 1, 0, "MyModel");
	qmlRegisterType<fsd::Object>("eui", 1, 0, "MyObject");
	qmlRegisterType<fsd::Place>("eui", 1, 0, "MyPlace");

	qmlRegisterType<fsd::FileManager>("eui", 1, 0, "MyFileManager");

	// FSEditor
	qmlRegisterSingletonInstance("eui", 1, 0, "MyManager", &manager);
	qmlRegisterSingletonInstance("eui", 1, 0, "MyCommands", manager.commandsManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyErrors", manager.errorsManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyFile", manager.fileManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyKeyBindings", manager.keyboardsManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyModels", manager.modelsManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyPreview", manager.previewManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MySelection", manager.selectionManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyStyles", manager.stylesManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyTranslations", manager.translationsManager());
	qmlRegisterSingletonInstance("eui", 1, 0, "MyUpdate", manager.updateManager());
	qmlRegisterType<fse::ProxyModel>("eui", 1, 0, "MyProxyModel");
	qmlRegisterType<fse::SelectionWrapper>("eui", 1, 0, "MySelectionWrapper");
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
	engine.loadFromModule("eui", "Main");
}

} // namespace fse::Application
