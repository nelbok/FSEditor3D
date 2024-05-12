#include "Controller.hpp"

namespace lhe {

Controller::Controller(QObject* parent)
	: QObject(parent) {}

Controller::~Controller() {}

void Controller::init() {
	assert(!_about);
	assert(!_project);

	_about = new About(this);
	_project = new lh::Project(this);

	_project->reset();
}

About* Controller::about() const {
	assert(_about);
	return _about;
}

lh::Project* Controller::project() const {
	assert(_project);
	return _project;
}
} // namespace lhe
