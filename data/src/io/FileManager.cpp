#include <fsd/io/FileManager.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QThread>
#include <QtCore/QUrl>

#include <fsd/data/Project.hpp>

namespace fsd {

class FileManager::Impl : public QThread {
public:
	Impl(FileManager* parent)
		: QThread(parent)
		, _parent{ parent } {}

	void init(Project* project, Type type, const QUrl& url) {
		assert(project);
		_project = project;
		_type = type;
		_url = url;

		auto* parent = _project->parent();
		// Not thread safe!!!
		_project->setParent(nullptr);
		_project->moveToThread(this);

		connect(this, &QThread::finished, QCoreApplication::instance(), [this, parent]() {
			_project->setParent(parent);
			if (_type == Type::Load) {
				emit _project->nameUpdated();
				emit _project->defaultPlaceUpdated();
				emit _project->charactersUpdated();
				emit _project->linksUpdated();
				emit _project->modelsUpdated();
				emit _project->placesUpdated();
			}
			disconnect(this, &QThread::finished, QCoreApplication::instance(), nullptr);
			_project = nullptr;
			emit _parent->finished();
		});
	}

	Result result() const {
		return _result;
	}

protected:
	virtual void run() override {
		assert(_project);
		switch (_type) {
			case Type::Load:
				load();
				break;
			case Type::Save:
				save();
				break;
			default:
				assert(false);
				break;
		}
		// Not thread safe!!!
		_project->moveToThread(QCoreApplication::instance()->thread());
	}

private:
	QString toPath(const QUrl& url) {
		assert(url.isValid());
		if (url.isLocalFile())
			return url.toLocalFile();
		else
			return url.toString();
	}

	void save() {
		assert(_project);

		QSaveFile file(toPath(_url));
		if (!file.open(QIODevice::WriteOnly)) {
			_result = Result::Error;
			return;
		}

		// Write project
		QJsonObject json;
		_project->save(json);
		file.write(QJsonDocument(json).toJson());

		if (isInterruptionRequested()) {
			_result = Result::Canceled;
			return;
		}

		if (file.commit()) {
			_result = Result::Success;
		} else {
			_result = Result::Error;
		}
	}

	void load() {
		assert(_project);

		QFile file(toPath(_url));
		if (!file.open(QIODevice::ReadOnly)) {
			_result = Result::Error;
			return;
		}

		// Read project
		_project->blockSignals(true);
		_project->load(QJsonDocument::fromJson(file.readAll()).object());
		file.close();

		if (isInterruptionRequested()) {
			_project->reset();
			_result = Result::Canceled;
		}

		_project->blockSignals(false);
	}

private:
	FileManager* _parent{ nullptr };
	Project* _project{ nullptr };
	QUrl _url{};
	Type _type{ Type::NoType };
	Result _result{ Result::NoResult };
};

FileManager::FileManager(QObject* parent)
	: QObject(parent)
	, _impl{ new Impl(this) } {}

void FileManager::init(Project* project, Type type, const QUrl& url) {
	_impl->init(project, type, url);
}

void FileManager::start() {
	_impl->start();
}

void FileManager::wait(QDeadlineTimer deadline) {
	_impl->wait(std::move(deadline));
}

bool FileManager::isFinished() {
	return _impl->isFinished();
}

bool FileManager::isRunning() {
	return _impl->isRunning();
}

FileManager::Result FileManager::result() const {
	return _impl->result();
}

void FileManager::requestInterruption() {
	_impl->requestInterruption();
}
} // namespace fsd
