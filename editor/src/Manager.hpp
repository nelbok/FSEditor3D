#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

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

public:
	Manager(QObject* parent = nullptr);
	virtual ~Manager();

	void init();

	Q_INVOKABLE void reset();
	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);

	About* about() const;
	Balsam* balsam() const;
	lh::Project* project() const;

	CommandsManager* commandsManager() const;
	ModelsManager* modelsManager() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace lhe
