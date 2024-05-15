#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

#include "controllers/Controller.hpp"
#include "controllers/SelectionManager.hpp"
#include "Config.hpp"

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	app.setOrganizationName(lh::Config::organization);
	app.setApplicationName(lh::Config::name);
	app.setApplicationVersion(lh::Config::version);
	app.setWindowIcon(QIcon(":/logo/logo.png"));

	QQmlApplicationEngine engine;

	QScopedPointer<lhe::Controller> controller(new lhe::Controller);

	controller->init();

	//-- TMP for TEST
	auto* project = controller->project();

	auto* p1 = project->createPlace();
	auto* p2 = project->createPlace();
	auto* p3 = project->createPlace();
	p1->setName("Place 1");
	p2->setName("Place 2");
	p3->setName("Place 3");

	auto* c1 = project->createCharacter();
	auto* c2 = project->createCharacter();
	c1->setName("Character 1");
	c2->setName("Character 2");
	c1->setPlace(p2);
	c2->setPlace(p3);

	auto* l1 = project->createLink();
	auto* l2 = project->createLink();
	l1->setName("Link 1");
	l2->setName("Link 2");
	l1->setLink(l2);
	l2->setLink(l1);
	l1->setPlace(p2);
	l2->setPlace(p3);

	project->setDefaultPlace(p2);
	//-- TMP for TEST

	// LHData
	qmlRegisterSingletonInstance("editor", 1, 0, "MyProject", controller->project());
	qmlRegisterType<lh::Character>("editor", 1, 0, "MyCharacter");
	qmlRegisterType<lh::Entity>("editor", 1, 0, "MyEntity");
	qmlRegisterType<lh::Link>("editor", 1, 0, "MyLink");
	qmlRegisterType<lh::Place>("editor", 1, 0, "MyPlace");
	qmlRegisterType<lh::Placement>("editor", 1, 0, "MyPlacement");

	// LHEditor
	qmlRegisterSingletonInstance("editor", 1, 0, "MyController", controller.get());
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
