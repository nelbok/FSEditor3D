#include <lh/data/UuidPointer.hpp>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lh {
void initCharacterPointer(UuidPointer<Character>& ptr, Project* project) {
	ptr.init(project, &Project::characters, &Project::charactersUpdated);
}

void initLinkPointer(UuidPointer<Link>& ptr, Project* link) {
	ptr.init(link, &Project::links, &Project::linksUpdated);
}

void initPlacePointer(UuidPointer<Place>& ptr, Project* project) {
	ptr.init(project, &Project::places, &Project::placesUpdated);
}
} // namespace lh
