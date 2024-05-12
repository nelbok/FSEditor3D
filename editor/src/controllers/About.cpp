#include "About.hpp"

#include "Config.hpp"

namespace lhe {

About::About(QObject* parent)
	: QObject(parent) {}

About::~About() {}

QString About::organization() const {
	return lh::Config::organization;
}

QString About::copyright() const {
	return lh::Config::copyright;
}

QString About::year() const {
	return lh::Config::year;
}

QString About::name() const {
	return lh::Config::name;
}

QString About::version() const {
	return lh::Config::version;
}

QString About::github() const {
	return lh::Config::github;
}

QString About::discord() const {
	return lh::Config::discord;
}

QString About::twitter() const {
	return lh::Config::twitter;
}
} // namespace lhe
