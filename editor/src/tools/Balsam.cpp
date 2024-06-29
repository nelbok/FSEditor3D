#include "Balsam.hpp"

#include <filesystem>

#include "tools/Tools.hpp"

#include "Config.hpp"
#include "CommandsManager.hpp"
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

	QStringList args;
	args << "--outputPath";
	args << QString::fromStdString(Tools::modelPath(detail::path(_manager), model).string());
	args << Tools::toPath(url);

	_process->start(fsd::Config::balsam, args);
}

void Balsam::finalize() {
	if (_process->exitStatus() == QProcess::NormalExit && _process->exitCode() == 0) {
		const auto qmlName = fs::path(Tools::toPath(_sourcePath).toStdString()).stem().string() + ".qml";
		const auto& mc = _manager->commandsManager()->modelCommand();
		mc->setSourcePath(_current, _sourcePath);
		mc->setQmlName(_current, QString::fromStdString(qmlName));
	} else {
		emit errorOccurred();
	}
}
} // namespace fse
