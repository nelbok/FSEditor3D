#include <fsd/data/Container.hpp>

#include <fsd/data/Project.hpp>

namespace fsd {
BaseContainer::BaseContainer(Project* project)
	: QObject(project)
	, _project(project) {}

BaseContainer::~BaseContainer() = default;
} // namespace fsd
