#include <fse/tools/Settings.hpp>

#include <QtCore/QSettings>

#include <fse/managers/KeyBindingsManager.hpp>
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
	settings.setValue(DefaultSettings::previewHeightKey, _manager->previewManager()->height());
	settings.setValue(DefaultSettings::previewAreEntryPointsVisibleKey, _manager->previewManager()->areEntryPointsVisible());
	settings.setValue(DefaultSettings::previewAreLinksVisibleKey, _manager->previewManager()->areLinksVisible());
	settings.setValue(DefaultSettings::previewAreObjectsVisibleKey, _manager->previewManager()->areObjectsVisible());
	settings.setValue(DefaultSettings::previewIsWorldModeKey, _manager->previewManager()->isWorldMode());
	settings.setValue(DefaultSettings::previewIsDebugModeKey, _manager->previewManager()->isDebugMode());
	settings.endGroup();

	settings.beginGroup(DefaultSettings::keyBindingsKey);
	settings.setValue(DefaultSettings::keyBindingsForward1Key, _manager->keyboardsManager()->keyBindings()->forward1);
	settings.setValue(DefaultSettings::keyBindingsForward2Key, _manager->keyboardsManager()->keyBindings()->forward2);
	settings.setValue(DefaultSettings::keyBindingsBackward1Key, _manager->keyboardsManager()->keyBindings()->backward1);
	settings.setValue(DefaultSettings::keyBindingsBackward2Key, _manager->keyboardsManager()->keyBindings()->backward2);
	settings.setValue(DefaultSettings::keyBindingsLeft1Key, _manager->keyboardsManager()->keyBindings()->left1);
	settings.setValue(DefaultSettings::keyBindingsLeft2Key, _manager->keyboardsManager()->keyBindings()->left2);
	settings.setValue(DefaultSettings::keyBindingsRight1Key, _manager->keyboardsManager()->keyBindings()->right1);
	settings.setValue(DefaultSettings::keyBindingsRight2Key, _manager->keyboardsManager()->keyBindings()->right2);
	settings.setValue(DefaultSettings::keyBindingsUp1Key, _manager->keyboardsManager()->keyBindings()->up1);
	settings.setValue(DefaultSettings::keyBindingsUp2Key, _manager->keyboardsManager()->keyBindings()->up2);
	settings.setValue(DefaultSettings::keyBindingsDown1Key, _manager->keyboardsManager()->keyBindings()->down1);
	settings.setValue(DefaultSettings::keyBindingsDown2Key, _manager->keyboardsManager()->keyBindings()->down2);
	settings.setValue(DefaultSettings::keyBindingsSprintKey, _manager->keyboardsManager()->keyBindings()->sprint);
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
	_manager->previewManager()->setHeight(settings.value(DefaultSettings::previewHeightKey, DefaultSettings::previewHeightValue).toUInt());
	_manager->previewManager()->setAreEntryPointsVisible(settings.value(DefaultSettings::previewAreEntryPointsVisibleKey, DefaultSettings::previewAreEntryPointsVisibleValue).toBool());
	_manager->previewManager()->setAreLinksVisible(settings.value(DefaultSettings::previewAreLinksVisibleKey, DefaultSettings::previewAreLinksVisibleValue).toBool());
	_manager->previewManager()->setAreObjectsVisible(settings.value(DefaultSettings::previewAreObjectsVisibleKey, DefaultSettings::previewAreObjectsVisibleValue).toBool());
	_manager->previewManager()->setWorldMode(settings.value(DefaultSettings::previewIsWorldModeKey, DefaultSettings::previewIsWorldModeValue).toBool());
	_manager->previewManager()->setDebugMode(settings.value(DefaultSettings::previewIsDebugModeKey, DefaultSettings::previewIsDebugModeValue).toBool());
	settings.endGroup();

	settings.beginGroup(DefaultSettings::keyBindingsKey);
	_manager->keyboardsManager()->keyBindings()->forward1 = settings.value(DefaultSettings::keyBindingsForward1Key, DefaultSettings::keyBindingsForward1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->forward2 = settings.value(DefaultSettings::keyBindingsForward2Key, DefaultSettings::keyBindingsForward2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->backward1 = settings.value(DefaultSettings::keyBindingsBackward1Key, DefaultSettings::keyBindingsBackward1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->backward2 = settings.value(DefaultSettings::keyBindingsBackward2Key, DefaultSettings::keyBindingsBackward2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->left1 = settings.value(DefaultSettings::keyBindingsLeft1Key, DefaultSettings::keyBindingsLeft1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->left2 = settings.value(DefaultSettings::keyBindingsLeft2Key, DefaultSettings::keyBindingsLeft2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->right1 = settings.value(DefaultSettings::keyBindingsRight1Key, DefaultSettings::keyBindingsRight1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->right2 = settings.value(DefaultSettings::keyBindingsRight2Key, DefaultSettings::keyBindingsRight2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->up1 = settings.value(DefaultSettings::keyBindingsUp1Key, DefaultSettings::keyBindingsUp1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->up2 = settings.value(DefaultSettings::keyBindingsUp2Key, DefaultSettings::keyBindingsUp2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->down1 = settings.value(DefaultSettings::keyBindingsDown1Key, DefaultSettings::keyBindingsDown1Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->down2 = settings.value(DefaultSettings::keyBindingsDown2Key, DefaultSettings::keyBindingsDown2Value).value<Qt::Key>();
	_manager->keyboardsManager()->keyBindings()->sprint = settings.value(DefaultSettings::keyBindingsSprintKey, DefaultSettings::keyBindingsSprintValue).value<Qt::Key>();
	_manager->keyboardsManager()->updateCurrent();
	settings.endGroup();
}

} // namespace fse
