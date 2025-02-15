#include <fsd/data/UuidPointer.hpp>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

namespace fsd {
BasePointer::BasePointer(BaseContainer* datas, Entity* parent)
	: QObject(parent)
	, _ref{ parent } {
	assert(datas);
	assert(parent);

	QObject::connect(datas, &BaseContainer::updated, this, &BasePointer::update);
}

BasePointer::~BasePointer() = default;

bool BasePointer::setUuid(const QUuid& uuid) {
	bool changed = _uuid != uuid;
	if (changed) {
		_uuid = uuid;
		update();
	}
	return changed;
}

bool BasePointer::isNull() const {
	return _uuid.isNull();
}

const QUuid& BasePointer::uuid() const {
	return _uuid;
}

UuidPointer<Link>* makeLinkPointer(Project* project, Entity* parent) {
	return new UuidPointer(project->links(), parent);
}

UuidPointer<Model>* makeModelPointer(Project* project, Entity* parent) {
	return new UuidPointer(project->models(), parent);
}

UuidPointer<Object>* makeObjectPointer(Project* project, Entity* parent) {
	return new UuidPointer(project->objects(), parent);
}

UuidPointer<Place>* makePlacePointer(Project* project, Entity* parent) {
	return new UuidPointer(project->places(), parent);
}
} // namespace fsd
