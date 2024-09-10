#include <fse/tools/Settings.hpp>

#include <QtCore/QSettings>

#include <fse/managers/PreviewManager.hpp>
#include <fse/managers/StylesManager.hpp>
#include <fse/managers/TranslationsManager.hpp>
#include <fse/Manager.hpp>

#include "tools/DefaultSettings.hpp"

namespace fse {
void Settings::init(fse::Manager* manager) {
	assert(!_manager);
	_manager = manager;
}

void Settings::save() const {
	assert(_manager);

	QSettings settings;
	settings.clear();

	settings.beginGroup(DefaultSettings::uiKey);
	settings.setValue(DefaultSettings::uiStyleKey, _manager->stylesManager()->current());
	settings.setValue(DefaultSettings::uiTranslationKey, _manager->translationsManager()->current());
	settings.endGroup();

	settings.beginGroup(DefaultSettings::previewKey);
	settings.setValue(DefaultSettings::previewAreOtherDatasVisibleKey, _manager->previewManager()->areOtherDatasVisible());
	settings.setValue(DefaultSettings::previewAreOriginsVisibleKey, _manager->previewManager()->areOriginsVisible());
	settings.setValue(DefaultSettings::previewIsWorldMapVisibleKey, _manager->previewManager()->isWorldMapVisible());
	settings.endGroup();
}

void Settings::load() {
	assert(_manager);

	QSettings settings;

	settings.beginGroup(DefaultSettings::uiKey);
	_manager->stylesManager()->setCurrent(settings.value(DefaultSettings::uiStyleKey, DefaultSettings::uiStyleValue).toString());
	_manager->translationsManager()->setCurrent(settings.value(DefaultSettings::uiTranslationKey, DefaultSettings::uiTranslationValue).toString());
	settings.endGroup();

	settings.beginGroup(DefaultSettings::previewKey);
	_manager->previewManager()->setAreOtherDatasVisible(settings.value(DefaultSettings::previewAreOtherDatasVisibleKey, DefaultSettings::previewAreOtherDatasVisibleValue).toBool());
	_manager->previewManager()->setAreOriginsVisible(settings.value(DefaultSettings::previewAreOriginsVisibleKey, DefaultSettings::previewAreOriginsVisibleValue).toBool());
	_manager->previewManager()->setIsWorldMapVisible(settings.value(DefaultSettings::previewIsWorldMapVisibleKey, DefaultSettings::previewIsWorldMapVisibleValue).toBool());
	settings.endGroup();
}

} // namespace fse
