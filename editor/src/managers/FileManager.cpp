#include "FileManager.hpp"

#include <filesystem>

#include <fsd/data/Project.hpp>

#include "tools/LoadThread.hpp"
#include "tools/SaveThread.hpp"

#include "Config.hpp"
#include "Manager.hpp"

namespace fse {

struct FileManager::Impl {
	QUrl tmpPath{};
	QUrl oldPath{};
	QUrl path{};
	fse::FileThread* fileThread{ nullptr };
	Manager* manager{ nullptr };

	template<class T>
	void manageFile(FileManager* manager, fsd::Project* project, const QUrl& url) {
		static_assert(std::is_base_of<fse::FileThread, T>::value, "T must inherit from fse::FileThread");
		manager->setPath(url);
		fileThread = new T(manager, project);
		fileThread->init();
		emit manager->beginFileTransaction();
		manager->connect(fileThread, &T::finished, manager, [this, manager]() {
			emit manager->endFileTransaction(fileThread->result());
			fileThread->deleteLater();
			fileThread = nullptr;
		});
		fileThread->start();
	}
};

FileManager::FileManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

FileManager::~FileManager() {}

void FileManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->manager = manager;
}

void FileManager::reset() {
	auto tmp = std::filesystem::temp_directory_path();
	tmp /= fsd::Config::name;
	tmp /= _impl->manager->project()->uuid().toString(QUuid::WithoutBraces).toStdString();
	tmp /= "";
	_impl->tmpPath = QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
	_impl->oldPath = _impl->tmpPath;
	_impl->path = QUrl();
}

void FileManager::load(const QUrl& url) {
	_impl->manager->reset();
	_impl->manageFile<fse::LoadThread>(this, _impl->manager->project(), url);
}

void FileManager::save(const QUrl& url) {
	_impl->manageFile<fse::SaveThread>(this, _impl->manager->project(), url);
}

void FileManager::requestFileTransactionInterruption() {
	assert(_impl->fileThread);
	_impl->fileThread->requestInterruption();
}

const QUrl& FileManager::tmpPath() const {
	return _impl->tmpPath;
}

const QUrl& FileManager::oldPath() const {
	return _impl->oldPath;
}

const QUrl& FileManager::path() const {
	return _impl->path;
}

void FileManager::setPath(const QUrl& path) {
	if (_impl->path != path || _impl->oldPath != path) {
		if (_impl->path.isValid()) {
			_impl->oldPath = _impl->path;
		}
		_impl->path = path;
		emit pathUpdated();
	}
}
} // namespace fse
