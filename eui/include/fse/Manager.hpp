#pragma once

#include <QtCore/QObject>
#include <QtCore/QUrl>

#include <fsd/data/Project.hpp>

#include <fse/tools/About.hpp>
#include <fse/tools/Balsam.hpp>
#include <fse/tools/Settings.hpp>

namespace fse {
class CommandsManager;
class ErrorsManager;
class FileManager;
class InterfaceManager;
class KeyBindingsManager;
class ModelsManager;
class PreviewManager;
class SelectionManager;
class StylesManager;
class TranslationsManager;
class UpdateManager;

class Manager : public QObject {
	Q_OBJECT
	Q_PROPERTY(const About& about READ about CONSTANT)
	Q_PROPERTY(Balsam* balsam READ balsam CONSTANT)
	Q_PROPERTY(const Settings& settings READ settings CONSTANT)
	Q_PROPERTY(fsd::Project* project READ project CONSTANT)

public:
	explicit Manager(QObject* parent = nullptr);
	~Manager() override;

	void init();
	void reset();

	const About& about() const;
	Balsam* balsam() const;
	const Settings& settings() const;
	fsd::Project* project() const;

	CommandsManager* commandsManager() const;
	ErrorsManager* errorsManager() const;
	FileManager* fileManager() const;
	InterfaceManager* interfaceManager() const;
	KeyBindingsManager* keyboardsManager() const;
	ModelsManager* modelsManager() const;
	PreviewManager* previewManager() const;
	SelectionManager* selectionManager() const;
	StylesManager* stylesManager() const;
	TranslationsManager* translationsManager() const;
	UpdateManager* updateManager() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fse
