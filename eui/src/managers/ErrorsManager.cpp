#include <fse/managers/ErrorsManager.hpp>

#include <QCoreApplication>

namespace fse {
ErrorsManager::ErrorsManager(QObject* parent)
	: QObject(parent) {}

ErrorsManager::~ErrorsManager() = default;

QString ErrorsManager::message() const {
	switch (_type) {
		case Type::BalsamError:
			return QCoreApplication::translate("ErrorsManager", "An error occured while parsing the model.");
		case Type::FileError:
			return QCoreApplication::translate("ErrorsManager", "An error occured while loading or saving a file:\n") + _message;
		case Type::StyleError:
			return QCoreApplication::translate("ErrorsManager", "An error occured while loading the styles.");
		case Type::TranslatorError:
			return QCoreApplication::translate("ErrorsManager", "An error occured while loading the translator.");
		default:
			return "";
	}
}

ErrorsManager::Type ErrorsManager::type() const {
	return _type;
}

void ErrorsManager::setType(Type type, const QString& message) {
	_type = type;
	_message = message;
	emit typeUpdated();
}
} // namespace fse
