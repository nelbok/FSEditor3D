#include <fse/tools/Balsam.hpp>

#include <filesystem>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/FileManager.hpp>
#include <fse/tools/Tools.hpp>
#include <fse/Config.hpp>
#include <fse/Manager.hpp>

namespace fs = std::filesystem;

namespace fse {
struct Balsam::Impl {
	QProcess* process{ nullptr };
	QUrl sourcePath{};
	fsd::Model* current{ nullptr };
	CommandsManager* commands{ nullptr };
	ErrorsManager* errors{ nullptr };
	FileManager* file{ nullptr };

	QUrl path() const {
		if (file->path().isValid())
			return file->path();
		if (file->oldPath().isValid())
			return file->oldPath();
		assert(file->tmpPath().isValid());
		return file->tmpPath();
	}

	fs::path searchQmlPath(const fsd::Model* model) const {
		const auto& modelPath = Tools::modelPath(path(), model);
		if (!fs::exists(modelPath))
			return {};

		for (const auto& dir_entry : fs::directory_iterator(modelPath)) {
			if (dir_entry.is_regular_file()) {
				const auto& path = dir_entry.path();
				if (path.extension() == ".qml") {
					return path;
				}
			}
		}
		return {};
	}

	fs::path searchQmlFile(const fsd::Model* model) const {
		const auto& path = searchQmlPath(model);
		if (path.empty()) {
			return {};
		}
		return path.filename();
	}
};

Balsam::Balsam(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Balsam::~Balsam() = default;

void Balsam::init(Manager* manager) {
	assert(!_impl->process);

	_impl->commands = manager->commandsManager();
	_impl->errors = manager->errorsManager();
	_impl->file = manager->fileManager();
	_impl->process = new QProcess(this);

	QObject::connect(_impl->process, &QProcess::errorOccurred, this, &Balsam::finalize);
	QObject::connect(_impl->process, &QProcess::finished, this, &Balsam::finalize);
}

QUrl Balsam::balsamPath() const {
	return QUrl::fromLocalFile(fse::Config::balsam);
}

QUrl Balsam::qmlDir(const fsd::Model* model) const {
	assert(model);
	auto tmp = Tools::modelPath(_impl->path(), model);
	return QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

QUrl Balsam::qmlPath(const fsd::Model* model) const {
	assert(model);
	assert(model->qmlName() != "");

	auto tmp = Tools::modelPath(_impl->path(), model);
	tmp /= model->qmlName().toStdString();
	return QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

void Balsam::generate(fsd::Model* model, const QUrl& url, QStringList args) {
	assert(model);

	_impl->current = model;
	_impl->sourcePath = url;

	// Verify that there are no other qml file
	if (const auto& qmlFile = _impl->searchQmlPath(_impl->current); !qmlFile.empty() && fs::exists(qmlFile)) {
		fs::remove(qmlFile);
		_impl->current->setQmlName("");
	}

	args << "--outputPath";
	args << QString::fromStdString(Tools::modelPath(_impl->path(), model).string());
	args << Tools::toPath(url);

	_impl->process->start(fse::Config::balsam, args);
}

void Balsam::finalize() {
	if (_impl->process->exitStatus() == QProcess::NormalExit && _impl->process->exitCode() == 0) {
		const auto& mc = _impl->commands->modelCommand();
		mc->setSourcePath(_impl->current, _impl->sourcePath);
		mc->setQmlName(_impl->current, QString::fromStdString(_impl->searchQmlFile(_impl->current).string()));
	} else {
		_impl->errors->setType(ErrorsManager::Type::BalsamError);
		emit errorOccurred();
	}
}

QProcess::ProcessError Balsam::error() const {
	assert(_impl->process);
	return _impl->process->error();
}

QProcess::ProcessState Balsam::state() const {
	assert(_impl->process);
	return _impl->process->state();
}
} // namespace fse
