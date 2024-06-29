#include "Manager.hpp"

#include <filesystem>

#include "Config.hpp"

#include "tools/SaveThread.hpp"

#include "CommandsManager.hpp"
#include "ModelsManager.hpp"

namespace fse {

struct Manager::Impl {
	About* about{ nullptr };
	Balsam* balsam{ nullptr };
	fsd::Project* project{ nullptr };

	QUrl tmpPath{};
	QUrl oldPath{};
	QUrl path{};
	fsd::FileManager* loadThread{ nullptr };
	fse::SaveThread* saveThread{ nullptr };

	CommandsManager* commandsManager{ nullptr };
	ModelsManager* modelsManager{ nullptr };
};

Manager::Manager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Manager::~Manager() {
	reset();
}

void Manager::init() {
	assert(!_impl->project);

	_impl->about = new About(this);
	_impl->balsam = new Balsam(this);
	_impl->project = new fsd::Project(this);

	_impl->commandsManager = new CommandsManager(this);
	_impl->modelsManager = new ModelsManager(this);

	_impl->balsam->init(this);

	_impl->commandsManager->init(_impl->project);
	_impl->modelsManager->init(_impl->project);

	reset();
}

void Manager::reset() {
	_impl->project->reset();
	_impl->commandsManager->reset();

	auto tmp = std::filesystem::temp_directory_path();
	tmp /= fsd::Config::name;
	tmp /= _impl->project->uuid().toString(QUuid::WithoutBraces).toStdString();
	tmp /= "";
	_impl->tmpPath = QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
	_impl->oldPath = _impl->tmpPath;
	_impl->path = QUrl();
}

void Manager::load(const QUrl& url) {
	reset();
	setPath(url);
	_impl->loadThread = new fsd::FileManager(this);
	_impl->loadThread->init(_impl->project, fsd::FileManager::Type::Load, url);
	emit beginFileTransaction();
	connect(_impl->loadThread, &fsd::FileManager::finished, this, [this]() {
		emit endFileTransaction(_impl->loadThread->result());
		_impl->loadThread->deleteLater();
	});
	_impl->loadThread->start();
}

void Manager::save(const QUrl& url) {
	setPath(url);
	_impl->saveThread = new fse::SaveThread(this);
	_impl->saveThread->init();
	emit beginFileTransaction();
	connect(_impl->saveThread, &fse::SaveThread::finished, this, [this]() {
		//emit endFileTransaction(_impl->saveThread->result());
		emit endFileTransaction(fsd::FileManager::Result::Success);
		_impl->saveThread->deleteLater();
		_impl->saveThread = nullptr;
	});
	_impl->saveThread->start();
}

void Manager::requestFileTransactionInterruption() {
	if (_impl->loadThread) {
		_impl->loadThread->requestInterruption();
	} else if (_impl->saveThread) {
		_impl->saveThread->requestInterruption();
	}
}

About* Manager::about() const {
	assert(_impl->about);
	return _impl->about;
}

Balsam* Manager::balsam() const {
	assert(_impl->balsam);
	return _impl->balsam;
}

fsd::Project* Manager::project() const {
	assert(_impl->project);
	return _impl->project;
}

const QUrl& Manager::tmpPath() const {
	return _impl->tmpPath;
}

const QUrl& Manager::oldPath() const {
	return _impl->oldPath;
}

const QUrl& Manager::path() const {
	return _impl->path;
}

void Manager::setPath(const QUrl& path) {
	if (_impl->path != path) {
		if (_impl->path.isValid()) {
			_impl->oldPath = _impl->path;
		}
		_impl->path = path;
		emit pathUpdated();
	}
}

CommandsManager* Manager::commandsManager() const {
	assert(_impl->commandsManager);
	return _impl->commandsManager;
}

ModelsManager* Manager::modelsManager() const {
	assert(_impl->modelsManager);
	return _impl->modelsManager;
}
} // namespace fse
