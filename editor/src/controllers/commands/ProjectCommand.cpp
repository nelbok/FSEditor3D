#include "ProjectCommand.hpp"

#include "../Commands.hpp"
#include "../Controller.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ProjectCommand::ProjectCommand(Controller* controller)
	: QObject(controller)
	, _c{ controller->commands() }
	, _p{ controller->project() } {
	assert(_c);
	assert(_p);
}

ProjectCommand::~ProjectCommand() {}

void ProjectCommand::setDefaultPlace(lh::Place* newValue) {
	addValueCommand(_c, _p, &lh::Project::setDefaultPlace, &lh::Project::defaultPlace, newValue);
}

} // namespace lhe
