#include <lh/data/UuidPointer.hpp>

#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lh {
UuidPointer<Place> makePlacePointer(Project* project) {
	return UuidPointer<Place>(project, &Project::places, &Project::placesUpdated);
}
} // namespace lh
