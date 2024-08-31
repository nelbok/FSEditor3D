#pragma once

#include <QtCore/QObject>
#include <QtCore/QUrl>

#include <fsd/data/Project.hpp>

#include "tools/About.hpp"
#include "tools/Balsam.hpp"

namespace fse {
class CommandsManager;
class FileManager;
class ModelsManager;
class PreviewManager;
class SelectionManager;
class StylesManager;
class TranslationsManager;

class Manager : public QObject {
	Q_OBJECT
	Q_PROPERTY(const About& about READ about CONSTANT)
	Q_PROPERTY(Balsam* balsam READ balsam CONSTANT)
	Q_PROPERTY(fsd::Project* project READ project CONSTANT)

public:
	Manager(QObject* parent = nullptr);
	virtual ~Manager();

	void init();

	Q_INVOKABLE void reset();
	Q_INVOKABLE void setClipboardText(const QString& text);

	const About& about() const;
	Balsam* balsam() const;
	fsd::Project* project() const;

	CommandsManager* commandsManager() const;
	FileManager* fileManager() const;
	ModelsManager* modelsManager() const;
	PreviewManager* previewManager() const;
	SelectionManager* selectionManager() const;
	StylesManager* stylesManager() const;
	TranslationsManager* translationsManager() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fse
