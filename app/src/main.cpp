#include <fse/Application.hpp>

int main(int argc, char* argv[]) {
	fse::Application app(argc, argv);
	app.init();
	return app.exec();
}
