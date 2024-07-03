#include "LoadThread.hpp"

#include <filesystem>

#include "tools/Tools.hpp"

#include "Manager.hpp"

namespace fs = std::filesystem;

namespace fse {
LoadThread::LoadThread(Manager* manager)
	: FileThread(manager) {
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
