#include "Balsam.hpp"

#include <filesystem>

#include "tools/Tools.hpp"

#include "Config.hpp"
#include "managers/CommandsManager.hpp"
#include "Manager.hpp"

namespace fs = std::filesystem;

namespace fse {
namespace detail {
const QUrl& path(fse::Manager* manager) {
	if (manager->path().isValid())
		return manager->path();
	if (manager->oldPath().isValid())
		return manager->oldPath();
	assert(manager->tmpPath().isValid());
	return manager->tmpPath();
}

fs::path searchQmlPath(fse::Manager* manager, fsd::Model* model) {
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

fs::path searchQmlFile(fse::Manager* manager, fsd::Model* model) {
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

void Balsam::init(Manager* manager) {
	assert(!_manager);
	assert(!_process);

	_manager = manager;
	_process = new QProcess(this);

	connect(_process, &QProcess::errorOccurred, this, &Balsam::finalize);
	connect(_process, &QProcess::finished, this, &Balsam::finalize);
}

QUrl Balsam::qmlPath(fsd::Model* model) {
	assert(model);
	assert(model->qmlName() != "");

	auto tmp = Tools::modelPath(detail::path(_manager), model);
	tmp /= model->qmlName().toStdString();
	return QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

void Balsam::generate(fsd::Model* model, const QUrl& url) {
	assert(model);

	_current = model;
	_sourcePath = url;

	// Verify that there are no other qml file
	const auto& qmlFile = detail::searchQmlPath(_manager, _current);
	if (!qmlFile.empty() && fs::exists(qmlFile)) {
		fs::remove(qmlFile);
		_current->setQmlName("");
	}

	QStringList args;
	args << "--outputPath";
	args << QString::fromStdString(Tools::modelPath(detail::path(_manager), model).string());
	args << Tools::toPath(url);

	_process->start(fsd::Config::balsam, args);
}

void Balsam::finalize() {
	if (_process->exitStatus() == QProcess::NormalExit && _process->exitCode() == 0) {
		const auto& mc = _manager->commandsManager()->modelCommand();
		mc->setSourcePath(_current, _sourcePath);
		mc->setQmlName(_current, QString::fromStdString(detail::searchQmlFile(_manager, _current).string()));
	} else {
		emit errorOccurred();
	}
}
} // namespace fse
