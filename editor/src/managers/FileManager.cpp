#include <fse/managers/FileManager.hpp>

#include <filesystem>

#include <fsd/data/Project.hpp>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/tools/LoadThread.hpp>
#include <fse/tools/SaveThread.hpp>
#include <fse/Config.hpp>
#include <fse/Manager.hpp>

namespace fse {

struct FileManager::Impl {
	QUrl tmpPath{};
	QUrl oldPath{};
	QUrl path{};
	fse::FileThread* fileThread{ nullptr };
	fsd::FileManager::Result result{ fsd::FileManager::Result::NoResult };
	QString errorMessage{ "" };
	FileManager::Status status{ FileManager::Status ::None };
	Manager* manager{ nullptr };

	template<class T>
	void manageFile(FileManager* mng, fsd::Project* project, const QUrl& url) {
		static_assert(std::is_base_of<fse::FileThread, T>::value, "T must inherit from fse::FileThread");
		mng->setPath(url);
		fileThread = new T(mng, project);
		fileThread->init();
		setResult(mng, fsd::FileManager::Result::NoResult);
		setStatus(mng, FileManager::Status::BeginTransaction);
		emit mng->beginTransaction();
		setStatus(mng, FileManager::Status::Processing);
		mng->connect(fileThread, &T::finished, mng, [this, mng]() {
			setResult(mng, fileThread->result(), fileThread->errorMessage());
			setStatus(mng, FileManager::Status::EndTransaction);
			emit mng->endTransaction();
			fileThread->deleteLater();
			fileThread = nullptr;
			setStatus(mng, FileManager::Status::Stopped);
		});
		fileThread->start();
	}

	void setResult(FileManager* mng, fsd::FileManager::Result r, const QString& e = "") {
		if (result != r) {
			result = r;
			errorMessage = e;
			if (this->result == fsd::FileManager::Result::Error) {
				manager->errorsManager()->setType(ErrorsManager::Type::FileError, errorMessage);
			}
			emit mng->resultUpdated();
		}
	}

	void setStatus(FileManager* mng, FileManager::Status s) {
		if (status != s) {
			status = s;
			emit mng->statusUpdated();
		}
	}
};

FileManager::FileManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

FileManager::~FileManager() = default;

void FileManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->manager = manager;
}

void FileManager::reset() {
	auto tmp = std::filesystem::temp_directory_path();
	tmp /= fse::Config::name;
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
	_impl->manager->commandsManager()->setIsModified(false);
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

fsd::FileManager::Result FileManager::result() const {
	return _impl->result;
}

QString FileManager::errorMessage() const {
	return _impl->errorMessage;
}

FileManager::Status FileManager::status() const {
	return _impl->status;
}
} // namespace fse
