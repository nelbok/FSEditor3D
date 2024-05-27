#include "Balsam.hpp"

#include <filesystem>

#include "Config.hpp"
#include "CommandsManager.hpp"
#include "Manager.hpp"

namespace fs = std::filesystem;

namespace lhe {
namespace detail {
QString toPath(const QUrl& url) {
	if (url.isLocalFile())
		return url.toLocalFile();
	else
		return url.toString();
}

fs::path modelPath(const QUrl& projectPath, lh::Model* model) {
	assert(model);

	auto tmp = fs::path(detail::toPath(projectPath).toStdString());
	if (tmp.has_filename()) {
		tmp = tmp.parent_path();
	}
	tmp /= model->uuid().toString(QUuid::WithoutBraces).split("-").at(4).toStdString();
	return tmp;
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

	connect(_manager, &Manager::pathUpdated, this, &Balsam::updateModelsPath);
	connect(_process, &QProcess::errorOccurred, this, &Balsam::finalize);
	connect(_process, &QProcess::finished, this, &Balsam::finalize);
}

void Balsam::reset() {
	auto tmp = fs::temp_directory_path();
	tmp /= lh::Config::name;
	tmp /= _manager->project()->uuid().toString(QUuid::WithoutBraces).toStdString();
	tmp /= "";
	_projectPath = QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

QUrl Balsam::qmlPath(lh::Model* model) {
	assert(model);
	assert(_projectPath.isValid());
	assert(model->qmlName() != "");

	auto tmp = detail::modelPath(_projectPath, model);
	tmp /= model->qmlName().toStdString();
	return QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
}

void Balsam::generate(lh::Model* model, const QUrl& url) {
	assert(model);

	_current = model;
	_sourcePath = url;

	QStringList args;
	args << "--outputPath";
	args << QString::fromStdString(detail::modelPath(_projectPath, model).string());
	args << detail::toPath(url);

	_process->start(lh::Config::balsam, args);
}

void Balsam::finalize() {
	if (_process->exitStatus() == QProcess::NormalExit && _process->exitCode() == 0) {
		const auto qmlName = fs::path(detail::toPath(_sourcePath).toStdString()).stem().string() + ".qml";
		const auto& mc = _manager->commandsManager()->modelCommand();
		mc->setSourcePath(_current, _sourcePath);
		mc->setQmlName(_current, QString::fromStdString(qmlName));
	} else {
		emit errorOccurred();
	}
}

void Balsam::updateModelsPath() {
	// Copy models
	for (auto* model : _manager->project()->models()) {
		const auto& oldPath = detail::modelPath(_projectPath, model);
		const auto& newPath = detail::modelPath(_manager->path(), model);
		if (fs::exists(oldPath)) {
			fs::copy(oldPath, newPath, fs::copy_options::recursive);
		}
	}

	_projectPath = _manager->path();
}
} // namespace lhe
