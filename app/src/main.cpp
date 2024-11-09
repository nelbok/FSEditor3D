#include <fse/Application.hpp>

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);
	fse::Application::initApp();

	fse::Manager manager;
	manager.init();

	if (!fse::Application::initParser(app, manager)) {
		return 0;
	}

	QQmlApplicationEngine engine;

	fse::Application::initRegister(manager);
	fse::Application::initEngine(app, engine, manager);

	return QGuiApplication::exec();
}
