#include "StylesManager.hpp"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QFile>

namespace fse {

struct StylesManager::Impl {
	QList<Style> styles;
};

StylesManager::StylesManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

StylesManager::~StylesManager() {}

void StylesManager::init() {
	QFile file(":/styles/basic.json");

	if (!file.open(QIODevice::ReadOnly)) {
		assert(!"Style not found");
	}

	const auto& document = QJsonDocument::fromJson(file.readAll());
	assert(!document.isNull());
	Style style;
	style.load(document.object());

	_impl->styles.append(style);
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

const Style& StylesManager::current() const {
	assert(_impl->styles.size() == 1);
	return _impl->styles.at(0);
}
} // namespace fse
