#include <lh/data/UuidPointer.hpp>

#include <lh/data/Character.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lh {
void initPlacePointer(UuidPointer<Character>& ptr, Project* project) {
	assert(false);
	//ptr.init(project, &Project::characters, &Project::charactersUpdated);
}

void initPlacePointer(UuidPointer<Place>& ptr, Project* project) {
	ptr.init(project, &Project::places, &Project::placesUpdated);
}
} // namespace lh
