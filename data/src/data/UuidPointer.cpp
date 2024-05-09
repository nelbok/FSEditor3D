#include <lh/data/UuidPointer.hpp>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lh {
void initCharacterPointer(UuidPointer<Character>& ptr, Project* project, QObject* parent) {
	ptr.init(project, &Project::characters, &Project::charactersUpdated, parent);
}

void initLinkPointer(UuidPointer<Link>& ptr, Project* link, QObject* parent) {
	ptr.init(link, &Project::links, &Project::linksUpdated, parent);
}

void initPlacePointer(UuidPointer<Place>& ptr, Project* project, QObject* parent) {
	ptr.init(project, &Project::places, &Project::placesUpdated, parent);
}
} // namespace lh
