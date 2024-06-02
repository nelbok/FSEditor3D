#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Model.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

#include "Config.hpp"
#include "CommandsManager.hpp"
#include "Manager.hpp"
#include "ModelsManager.hpp"
#include "SelectionManager.hpp"

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	app.setOrganizationName(lh::Config::organization);
	app.setApplicationName(lh::Config::name);
	app.setApplicationVersion(lh::Config::version);
	app.setWindowIcon(QIcon(":/logo/logo.png"));

	QQmlApplicationEngine engine;

	QScopedPointer<lhe::Manager> manager(new lhe::Manager);

	manager->init();

	// LHData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", manager->project());
	qmlRegisterType<lh::Character>("editor", 1, 0, "MyCharacter");
	qmlRegisterType<lh::Entity>("editor", 1, 0, "MyEntity");
	qmlRegisterType<lh::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<lh::Model>("editor", 1, 0, "MyModel");
	qmlRegisterType<lh::Object>("editor", 1, 0, "MyObject");
	qmlRegisterType<lh::Place>("editor", 1, 0, "MyPlace");
	qmlRegisterType<lh::Placement>("editor", 1, 0, "MyPlacement");

	// LHEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyManager", manager.get());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyCommands", manager->commandsManager());
	qmlRegisterSingletonInstance("editor", 1, 0, "MyModels", manager->modelsManager());
	qmlRegisterType<lhe::SelectionManager>("editor", 1, 0, "MySelectionManager");

	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.loadFromModule("editor", "Main");

	return app.exec();
}
