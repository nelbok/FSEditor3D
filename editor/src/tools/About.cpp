#include <fse/tools/About.hpp>

#include <QtCore/QCoreApplication>

#include <fse/Config.hpp>

namespace fse {
QString About::organization() const {
	return QCoreApplication::organizationName();
}

QString About::copyright() const {
	return fse::Config::copyright;
}

QString About::year() const {
	return fse::Config::year;
}

QString About::description() const {
	return fse::Config::description;
}

QString About::name() const {
	return QCoreApplication::applicationName();
}

QString About::version() const {
	return QCoreApplication::applicationVersion();
}

QString About::qtVersion() const {
	return qVersion();
}

QString About::github() const {
	return fse::Config::github;
}

QString About::discord() const {
	return fse::Config::discord;
}

QString About::twitter() const {
	return fse::Config::twitter;
}
} // namespace fse
