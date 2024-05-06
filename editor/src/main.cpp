#include <QtGui/QFont>
#include <QtGui/QGuiApplication>
#include <QtGui/QIcon>
#include <QtQml/QQmlApplicationEngine>

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
	auto* p2 = project->createPlace();
	auto* p3 = project->createPlace();
	auto* p4 = project->createPlace();
	project->setDefaultPlace(p3);
	p2->setName("AA");
	p3->setName("BB");
	p4->setName("CC");

	QQmlApplicationEngine engine;

	qmlRegisterSingletonInstance("LHEditor", 1, 0, "MyProject", project.get());
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
