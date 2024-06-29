#include "SaveThread.hpp"

#include <filesystem>

#include "tools/Tools.hpp"

#include "Manager.hpp"

namespace fs = std::filesystem;

namespace fse {
SaveThread::SaveThread(Manager* manager)
	: QThread(manager)
	, _manager{ manager } {}

SaveThread::~SaveThread() {}

void SaveThread::init() {
	assert(!_fileManager);
	_fileManager = new fsd::FileManager(this);
	_fileManager->init(_manager->project(), fsd::FileManager::Type::Save, _manager->path());
}

void SaveThread::run() {
	_fileManager->start();
	while (_fileManager->isRunning()) {
		if (isInterruptionRequested()) {
			_fileManager->requestInterruption();
		}
		msleep(500);
	}

	// FIXME: Could be dangerous if too much files or symbolic links
	// Copy models
	for (auto* model : _manager->project()->models()) {
		if (isInterruptionRequested()) {
			break;
		}
		const auto& oldPath = Tools::modelPath(_manager->oldPath(), model);
		const auto& newPath = Tools::modelPath(_manager->path(), model);
		if (fs::exists(oldPath)) {
			fs::copy(oldPath, newPath, fs::copy_options::recursive);
		}
	}
}

} // namespace fse
