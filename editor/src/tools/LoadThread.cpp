#include "LoadThread.hpp"

#include <filesystem>

#include "managers/FileManager.hpp"
#include "tools/Tools.hpp"

namespace fs = std::filesystem;

namespace fse {
LoadThread::LoadThread(FileManager* manager, fsd::Project* project)
	: FileThread(manager, project) {
	_type = fsd::FileManager::Type::Load;
}

LoadThread::~LoadThread() {}

void LoadThread::run() {
	_fileManager->start();
	while (_fileManager->isRunning()) {
		if (isInterruptionRequested()) {
			_fileManager->requestInterruption();
		}
		msleep(500);
	}

	_result = _fileManager->result();

	// TODO: Verify that the models are correct
}

} // namespace fse
