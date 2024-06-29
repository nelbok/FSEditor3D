#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <fsd/data/Character.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include "models/ProxyModel.hpp"
#include "models/SelectionWrapper.hpp"
#include "Config.hpp"
#include "CommandsManager.hpp"
#include "Manager.hpp"
#include "ModelsManager.hpp"

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	app.setOrganizationName(fsd::Config::organization);
	app.setApplicationName(fsd::Config::name);
	app.setApplicationVersion(fsd::Config::version);
	app.setWindowIcon(QIcon(":/logo/logo.png"));

	QQmlApplicationEngine engine;

	QScopedPointer<fse::Manager> manager(new fse::Manager);

	manager->init();

	// FSData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", manager->project());
	qmlRegisterType<fsd::Character>("editor", 1, 0, "MyCharacter");
	qmlRegisterType<fsd::Entity>("editor", 1, 0, "MyEntity");
	qmlRegisterType<fsd::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<fsd::Model>("editor", 1, 0, "MyModel");
	qmlRegisterType<fsd::Object>("editor", 1, 0, "MyObject");
	qmlRegisterType<fsd::Place>("editor", 1, 0, "MyPlace");
	qmlRegisterType<fsd::Placement>("editor", 1, 0, "MyPlacement");
	qmlRegisterType<fsd::FileManager>("editor", 1, 0, "MyFileManager");

	// FSEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyManager", manager.get());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyCommands", manager->commandsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyModels", manager->modelsManager());
	qmlRegisterType<fse::ProxyModel>("editor", 1, 0, "MyProxyModel");
	qmlRegisterType<fse::SelectionWrapper>("editor", 1, 0, "MySelectionWrapper");

	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.loadFromModule("editor", "Main");

	return app.exec();
}
