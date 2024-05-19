#include <lh/data/UuidPointer.hpp>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lh {
BasePointer::BasePointer(Project* project, void (Project::*signal)(), Entity* parent)
	: QObject(parent)
	, _project{ project }
	, _ref{ parent } {
	assert(project);
	assert(signal);
	assert(parent);

	QObject::connect(project, signal, this, &BasePointer::update);
}

BasePointer::~BasePointer() {}

bool BasePointer::setUuid(const QUuid& uuid) {
	assert(_project);
	bool changed = _uuid != uuid;
	if (changed) {
		_uuid = uuid;
		update();
	}
	return changed;
}

bool BasePointer::isNull() const {
	assert(_project);
	return _uuid.isNull();
}

const QUuid& BasePointer::uuid() const {
	assert(_project);
	return _uuid;
}

UuidPointer<Character>* makeCharacterPointer(Project* project, Entity* parent) {
	return new UuidPointer<Character>(project, &Project::characters, &Project::charactersUpdated, parent);
}

UuidPointer<Link>* makeLinkPointer(Project* project, Entity* parent) {
	return new UuidPointer<Link>(project, &Project::links, &Project::linksUpdated, parent);
}

UuidPointer<Place>* makePlacePointer(Project* project, Entity* parent) {
	return new UuidPointer<Place>(project, &Project::places, &Project::placesUpdated, parent);
}
} // namespace lh
