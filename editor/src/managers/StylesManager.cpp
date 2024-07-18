#include "StylesManager.hpp"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QFile>

namespace fse {

struct StylesManager::Impl {
	Style style;
	QString current{ "basic" };

	void loadStyle() {
		QFile file(QString(":/styles/%1.json").arg(current));

		if (!file.open(QIODevice::ReadOnly)) {
			assert(!"Style not found");
		}

		try {
			const auto& document = QJsonDocument::fromJson(file.readAll());
			assert(!document.isNull());
			style.load(document.object());
		} catch (const std::exception&) {
			style = Style{};
		}
	}
};

StylesManager::StylesManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

StylesManager::~StylesManager() {}

void StylesManager::init() {
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
