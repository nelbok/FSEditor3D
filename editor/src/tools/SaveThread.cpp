#include "SaveThread.hpp"

#include <filesystem>

#include "managers/FileManager.hpp"
#include "tools/Tools.hpp"

namespace fs = std::filesystem;

namespace fse {
SaveThread::SaveThread(FileManager* manager, fsd::Project* project)
	: FileThread(manager, project) {
	_type = fsd::FileManager::Type::Save;
}

SaveThread::~SaveThread() {}

void SaveThread::run() {
	_fileManager->start();
	while (_fileManager->isRunning()) {
		if (isInterruptionRequested()) {
			_fileManager->requestInterruption();
		}
		msleep(500);
	}

	_result = _fileManager->result();
	if (_result != fsd::FileManager::Result::Success) {
		return;
	}

	if (Tools::projectPath(_manager->oldPath()) == Tools::projectPath(_manager->path())) {
		return;
	}

	// FIXME: Could be dangerous if too much files or symbolic links
	// Copy models
	for (auto* model : _project->models()) {
		if (isInterruptionRequested()) {
			_result = fsd::FileManager::Result::Canceled;
			break;
		}

		// No source, no copy
		if (model->qmlName() == "") {
			continue;
		}

		const auto& oldPath = Tools::modelPath(_manager->oldPath(), model);
		const auto& newPath = Tools::modelPath(_manager->path(), model);
		if (fs::exists(oldPath)) {
			try {
				fs::copy(oldPath, newPath, fs::copy_options::recursive);
			} catch (...) {
				_result = fsd::FileManager::Result::Error;
				break;
			}
		} else {
			_result = fsd::FileManager::Result::Error;
			break;
		}
	}
}

} // namespace fse
