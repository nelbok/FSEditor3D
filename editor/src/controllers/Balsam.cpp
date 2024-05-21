#include "Balsam.hpp"

#include "Config.hpp"

namespace lhe {
Balsam::Balsam(QObject* parent)
	: QObject(parent) {}

Balsam::~Balsam() {}

void Balsam::init(lh::Project* project) {
	assert(!_project);
	assert(!_process);

	_project = project;
	_process = new QProcess(this);

	connect(_process, &QProcess::errorOccurred, this, &Balsam::finalize);
	connect(_process, &QProcess::finished, this, &Balsam::finalize);
}

void Balsam::generate(lh::Model* model, const QUrl& url) {
	assert(model);

	_current = model;

	//QStringList args;
	//args << "--outputPath";
	//args << MODEL_DIR;
	//args << SOURCE;

	//_process->start(lh::Config::balsam, args);
}

void Balsam::finalize() {
	if (_process->exitStatus() == QProcess::NormalExit && _process->exitCode() == 0) {
		// TODO: Inform model, inform View3D
	} else {
		emit errorOccurred();
	}
}
} // namespace lhe
