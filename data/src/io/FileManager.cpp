#include <fsd/io/FileManager.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QThread>
#include <QtCore/QUrl>

#include <fsd/data/Project.hpp>
#include <fsd/io/JsonException.hpp>

namespace fsd {

class FileManager::Impl : public QThread {
public:
	explicit Impl(FileManager* parent)
		: QThread(parent)
		, _parent{ parent } {}

	void init(Project* project, Type type, const QUrl& url) {
		assert(project);
		_project = project;
		_type = type;
		_url = url;
		_errorMessage = "";

		auto* parent = _project->parent();
		// Not thread safe!!!
		_project->setParent(nullptr);
		_project->moveToThread(this);

		QObject::connect(this, &QThread::finished, QCoreApplication::instance(), [this, parent]() {
			_project->setParent(parent);
			if (_type == Type::Load) {
				assert(_project->metaObject()->propertyCount() == 19);

				// Entity
				emit _project->uuidUpdated();
				emit _project->isAliveUpdated();
				emit _project->nameUpdated();
				emit _project->hasRefUpdated();

				// Geometry
				emit _project->localPositionUpdated();
				emit _project->localRotationUpdated();
				emit _project->localScaleUpdated();
				emit _project->globalPositionUpdated();
				emit _project->globalRotationUpdated();
				emit _project->globalScaleUpdated();

				// Project
				emit _project->defaultPlaceUpdated();
				emit _project->heightUpdated();
				emit _project->linksUpdated();
				emit _project->modelsUpdated();
				emit _project->objectsUpdated();
				emit _project->placesUpdated();
				emit _project->entitiesUpdated();
			}
			QObject::disconnect(this, &QThread::finished, QCoreApplication::instance(), nullptr);
			_project = nullptr;
			emit _parent->finished();
		});
	}

	Result result() const {
		return _result;
	}

	QString errorMessage() const {
		return _errorMessage;
	}

protected:
	void run() override {
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
	QString toPath(const QUrl& url) const {
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
		try {
			const auto& document = QJsonDocument::fromJson(file.readAll());
			if (document.isNull()) {
				throw JsonException("FileManager", "load", JsonException::Error::InvalidDocument);
			}
			_project->load(document.object());
		} catch (const JsonException& e) {
			_project->reset();
			_result = Result::Error;
			_errorMessage = e.what();
		}
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
	QString _errorMessage{ "" };
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

bool FileManager::isFinished() const {
	return _impl->isFinished();
}

bool FileManager::isRunning() const {
	return _impl->isRunning();
}

FileManager::Result FileManager::result() const {
	return _impl->result();
}

QString FileManager::errorMessage() const {
	return _impl->errorMessage();
}

void FileManager::requestInterruption() {
	_impl->requestInterruption();
}
} // namespace fsd
