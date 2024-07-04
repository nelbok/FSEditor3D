#pragma once

#include <QtCore/QObject>
#include <QtCore/QUrl>

#include <fsd/data/Project.hpp>
#include <fsd/io/FileManager.hpp>

#include "tools/About.hpp"
#include "tools/Balsam.hpp"
#include "tools/Style.hpp"

namespace fse {
class CommandsManager;
class ModelsManager;
class StylesManager;

class Manager : public QObject {
	Q_OBJECT
	Q_PROPERTY(const About& about READ about CONSTANT)
	Q_PROPERTY(Balsam* balsam READ balsam CONSTANT)
	Q_PROPERTY(fsd::Project* project READ project CONSTANT)
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)

public:
	Manager(QObject* parent = nullptr);
	virtual ~Manager();

	void init();

	Q_INVOKABLE void reset();
	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);
	Q_INVOKABLE void requestFileTransactionInterruption();

	const About& about() const;
	Balsam* balsam() const;
	fsd::Project* project() const;

	const QUrl& tmpPath() const;
	const QUrl& oldPath() const;
	const QUrl& path() const;
	void setPath(const QUrl& path);

	CommandsManager* commandsManager() const;
	ModelsManager* modelsManager() const;
	StylesManager* stylesManager() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void beginFileTransaction();
	void endFileTransaction(fsd::FileManager::Result result);
	void pathUpdated();
};
} // namespace fse
