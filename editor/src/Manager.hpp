#pragma once

#include <QtCore/QObject>
#include <QtCore/QUrl>

#include <lh/data/Project.hpp>
#include <lh/io/FileManager.hpp>

#include "About.hpp"
#include "Balsam.hpp"

namespace lhe {
class CommandsManager;
class ModelsManager;

class Manager : public QObject {
	Q_OBJECT
	Q_PROPERTY(About* about READ about CONSTANT)
	Q_PROPERTY(Balsam* balsam READ balsam CONSTANT)
	Q_PROPERTY(lh::Project* project READ project CONSTANT)
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)

public:
	Manager(QObject* parent = nullptr);
	virtual ~Manager();

	void init();

	Q_INVOKABLE void reset();
	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);
	Q_INVOKABLE void requestFileTransactionInterruption();

	About* about() const;
	Balsam* balsam() const;
	lh::Project* project() const;

	const QUrl& path() const;
	void setPath(const QUrl& path);

	CommandsManager* commandsManager() const;
	ModelsManager* modelsManager() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void beginFileTransaction();
	void endFileTransaction(lh::FileManager::Result result);
	void pathUpdated();
};
} // namespace lhe
