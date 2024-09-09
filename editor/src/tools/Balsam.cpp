#include <fse/tools/Balsam.hpp>

#include <filesystem>

#include <fse/managers/FileManager.hpp>
#include <fse/managers/CommandsManager.hpp>
#include <fse/tools/Tools.hpp>

#include "Config.hpp"

namespace fs = std::filesystem;

namespace fse {
namespace detail {
const QUrl& path(fse::FileManager* manager) {
	if (manager->path().isValid())
		return manager->path();
	if (manager->oldPath().isValid())
		return manager->oldPath();
	assert(manager->tmpPath().isValid());
	return manager->tmpPath();
}

fs::path searchQmlPath(fse::FileManager* manager, fsd::Model* model) {
	const auto& modelPath = Tools::modelPath(detail::path(manager), model);
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

fs::path searchQmlFile(fse::FileManager* manager, fsd::Model* model) {
	const auto& path = detail::searchQmlPath(manager, model);
	if (path.empty()) {
		return {};
	}
	return path.filename();
}
} // namespace detail

Balsam::Balsam(QObject* parent)
	: QObject(parent) {}

Balsam::~Balsam() {}

void Balsam::init(FileManager* manager, CommandsManager* commands) {
	assert(!_manager);
	assert(!_commands);
	assert(!_process);

	_manager = manager;
	_commands = commands;
	_process = new QProcess(this);

	QObject::connect(_process, &QProcess::errorOccurred, this, &Balsam::finalize);
	QObject::connect(_process, &QProcess::finished, this, &Balsam::finalize);
}

QUrl Balsam::balsamPath() const {
	return QUrl::fromLocalFile(fse::Config::balsam);
}

QUrl Balsam::qmlPath(fsd::Model* model) {
	assert(model);
	assert(model->qmlName() != "");

	auto tmp = Tools::modelPath(detail::path(_manager), model);
	tmp /= model->qmlName().toStdString();
	return QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

void Balsam::generate(fsd::Model* model, const QUrl& url, QStringList args) {
	assert(model);

	_current = model;
	_sourcePath = url;

	// Verify that there are no other qml file
	const auto& qmlFile = detail::searchQmlPath(_manager, _current);
	if (!qmlFile.empty() && fs::exists(qmlFile)) {
		fs::remove(qmlFile);
		_current->setQmlName("");
	}

	args << "--outputPath";
	args << QString::fromStdString(Tools::modelPath(detail::path(_manager), model).string());
	args << Tools::toPath(url);

	_process->start(fse::Config::balsam, args);
}

void Balsam::finalize() {
	if (_process->exitStatus() == QProcess::NormalExit && _process->exitCode() == 0) {
		const auto& mc = _commands->modelCommand();
		mc->setSourcePath(_current, _sourcePath);
		mc->setQmlName(_current, QString::fromStdString(detail::searchQmlFile(_manager, _current).string()));
	} else {
		emit errorOccurred();
	}
}

QProcess::ProcessError Balsam::error() const {
	assert(_process);
	return _process->error();
}

QProcess::ProcessState Balsam::state() const {
	assert(_process);
	return _process->state();
}
} // namespace fse
