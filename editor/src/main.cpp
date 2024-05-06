#include <QtGui/QFont>
#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

#include "Config.hpp"

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	app.setOrganizationName(lh::Config::organization);
	app.setApplicationName(lh::Config::name);
	app.setApplicationVersion(lh::Config::version);
	app.setWindowIcon(QIcon(":/logo/logo.png"));

	// FIXME: Style
	auto font = app.font();
	font.setPointSize(11);
	app.setFont(font);

	QScopedPointer<lh::Project> project(new lh::Project);

	project->reset();

	// TMP for TEST
	project->createCharacter()->setName("Character 1");
	project->createCharacter()->setName("Character 2");

	auto* l1 = project->createCharacter();
	auto* l2 = project->createCharacter();
	l1->setName("Link 1");
	l2->setName("Link 2");

	auto* p1 = project->createPlace();
	auto* p2 = project->createPlace();
	auto* p3 = project->createPlace();
	p1->setName("Place 1");
	p2->setName("Place 2");
	p3->setName("Place3");

	project->setDefaultPlace(p2);


	QQmlApplicationEngine engine;

	qmlRegisterSingletonInstance("LHEditor", 1, 0, "MyProject", project.get());
	qmlRegisterType<lh::Character>("LHEditor", 1, 0, "MyCharacter");
	qmlRegisterType<lh::Link>("LHEditor", 1, 0, "MyLink");
	qmlRegisterType<lh::Place>("LHEditor", 1, 0, "MyPlace");

	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
		[]() {
			QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.loadFromModule("LHEditor", "Main");

	return app.exec();
}
