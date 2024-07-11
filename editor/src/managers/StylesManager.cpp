#include "StylesManager.hpp"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QFile>

namespace fse {

struct StylesManager::Impl {
	qsizetype index{ -1 };
	QList<Style> styles;

	bool loadStyle(const QString& path) {
		QFile file(path);

		if (!file.open(QIODevice::ReadOnly)) {
			assert(!"Style not found");
		}

		try {
			const auto& document = QJsonDocument::fromJson(file.readAll());
			assert(!document.isNull());
			Style style;
			style.load(document.object());
			styles.append(std::move(style));
			return true;
		} catch (const std::exception& e) {
			return false;
		}
	}
};

StylesManager::StylesManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

StylesManager::~StylesManager() {}

void StylesManager::init() {
	// FIXME: Manage errors
	_impl->loadStyle(":/styles/basic.json");
	_impl->loadStyle(":/styles/dark.json");
	_impl->loadStyle(":/styles/light.json");

	// Default weird style
	if (_impl->styles.empty()) {
		_impl->styles.append(Style{});
	}

	setIndex(0);
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

int StylesManager::index() const {
	assert(_impl->index != -1);
	return _impl->index;
}
void StylesManager::setIndex(int index) {
	if (_impl->index != index) {
		_impl->index = index;
		emit indexUpdated();
		emit currentUpdated();
	}
}

const Style& StylesManager::current() const {
	assert(0 <= _impl->index && _impl->index < _impl->styles.count());
	return _impl->styles.at(_impl->index);
}

const QList<Style>& StylesManager::styles() const {
	assert(!_impl->styles.empty());
	return _impl->styles;
}
} // namespace fse
