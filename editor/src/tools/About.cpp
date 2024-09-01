#include "About.hpp"

#include "Config.hpp"

namespace fse {
QString About::organization() const {
	return fsd::Config::organization;
}

QString About::copyright() const {
	return fsd::Config::copyright;
}

QString About::year() const {
	return fsd::Config::year;
}

QString About::description() const {
	return fsd::Config::description;
}

QString About::name() const {
	return fsd::Config::name;
}

QString About::version() const {
	return fsd::Config::version;
}

QString About::qtVersion() const {
	return qVersion();
}

QString About::github() const {
	return fsd::Config::github;
}

QString About::discord() const {
	return fsd::Config::discord;
}

QString About::twitter() const {
	return fsd::Config::twitter;
}
} // namespace fse
