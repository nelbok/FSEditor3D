#include <QtCore/QCommandLineParser>
#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include "managers/CommandsManager.hpp"
#include "managers/ModelsManager.hpp"
#include "managers/StylesManager.hpp"
#include "managers/TranslationsManager.hpp"
#include "models/ProxyModel.hpp"
#include "models/SelectionWrapper.hpp"
#include "Config.hpp"
#include "Manager.hpp"

void initApp(QGuiApplication& app) {
	app.setOrganizationName(fsd::Config::organization);
	app.setApplicationName(fsd::Config::name);
	app.setApplicationVersion(fsd::Config::version);
	app.setWindowIcon(QIcon(":/logo/logo.png"));
}

bool initParser(const QGuiApplication& app, fse::Manager* manager) {
	QCommandLineParser parser;
	parser.setApplicationDescription(fsd::Config::name);
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption generateStyleOption({ "s", "generate-style" }, "Generate an empty style json file");
	parser.addOption(generateStyleOption);

	// Process the actual command line arguments given by the user
	parser.process(app);

	if (parser.isSet(generateStyleOption)) {
		manager->stylesManager()->createJson();
		return false;
	}

	return true;
}

void initRegister(fse::Manager* manager) {
	// FSData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", manager->project());
	qmlRegisterType<fsd::Entity>("editor", 1, 0, "MyEntity");
	qmlRegisterType<fsd::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<fsd::Model>("editor", 1, 0, "MyModel");
	qmlRegisterType<fsd::Object>("editor", 1, 0, "MyObject");
	qmlRegisterType<fsd::Place>("editor", 1, 0, "MyPlace");
	qmlRegisterType<fsd::Placement>("editor", 1, 0, "MyPlacement");
	qmlRegisterType<fsd::Shape>("editor", 1, 0, "MyShape");
	qmlRegisterType<fsd::FileManager>("editor", 1, 0, "MyFileManager");

	// FSEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyManager", manager);
	qmlRegisterSingletonInstance("editor", 1, 0, "MyCommands", manager->commandsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyModels", manager->modelsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyStyles", manager->stylesManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyTranslations", manager->translationsManager());
	qmlRegisterType<fse::ProxyModel>("editor", 1, 0, "MyProxyModel");
	qmlRegisterType<fse::SelectionWrapper>("editor", 1, 0, "MySelectionWrapper");
}

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	initApp(app);

	QScopedPointer<fse::Manager> manager(new fse::Manager);
	manager->init();

	if (!initParser(app, manager.get())) {
		return 0;
	}

	QQmlApplicationEngine engine;

	initRegister(manager.get());

	// Translations
	QObject::connect(manager->translationsManager(), &fse::TranslationsManager::currentUpdated, &engine, &QQmlApplicationEngine::retranslate);

	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.loadFromModule("editor", "Main");

	return app.exec();
}
