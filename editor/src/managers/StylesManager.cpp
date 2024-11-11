#include <fse/managers/StylesManager.hpp>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QFile>

#include <fsd/io/JsonException.hpp>

#include <fse/managers/ErrorsManager.hpp>

#include "tools/DefaultSettings.hpp"

namespace fse {

struct StylesManager::Impl {
	Style style;
	QString current{ DefaultSettings::uiStyleValue };
	ErrorsManager* manager{ nullptr };

	void loadStyle() {
		QFile file(QString(":/styles/%1.json").arg(current));

		if (!file.open(QIODevice::ReadOnly)) {
			assert(!"Style not found");
		}

		try {
			const auto& document = QJsonDocument::fromJson(file.readAll());
			if (document.isNull()) {
				throw fsd::JsonException(fsd::JsonException::Error::InvalidDocument);
			}
			style.load(document.object());
		} catch (const fsd::JsonException&) {
			style = Style{};
			style.foreground.normal = { 0, 0, 0 };
			style.part.border.normal = { 0, 0, 0 };
			style.part.border.width = 1;
			manager->setType(ErrorsManager::Type::StyleError);
		}
	}
};

StylesManager::StylesManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

StylesManager::~StylesManager() = default;

void StylesManager::init(ErrorsManager* manager) {
	assert(!_impl->manager);
	_impl->manager = manager;
	_impl->loadStyle();
}

void StylesManager::createJson() const {
	QSaveFile file("style.json");
	if (!file.open(QIODevice::WriteOnly)) {
		return;
	}

	QJsonObject json;
	Style().save(json);
	file.write(QJsonDocument(json).toJson());
	file.commit();
}

const QString& StylesManager::current() const {
	return _impl->current;
}

void StylesManager::setCurrent(const QString& current) {
	if (_impl->current != current) {
		_impl->current = current;
		_impl->loadStyle();
		emit currentUpdated();
	}
}

const Style& StylesManager::style() const {
	return _impl->style;
}
} // namespace fse
