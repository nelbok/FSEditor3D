#include <fse/tools/FileThread.hpp>

#include <filesystem>

#include <fse/managers/FileManager.hpp>
#include <fse/tools/Tools.hpp>
#include <fse/Manager.hpp>

namespace fse {
FileThread::FileThread(FileManager* manager, fsd::Project* project)
	: QThread(manager)
	, _project(project)
	, _manager{ manager } {
	assert(_project);
	assert(_manager);
}

FileThread::~FileThread() = default;

void FileThread::init() {
	assert(!_fileManager);
	assert(_type != fsd::FileManager::Type::NoType);
	_fileManager = new fsd::FileManager(this);
	_fileManager->init(_project, _type, _manager->path());
}

fsd::FileManager::Result FileThread::result() const {
	return _result;
}

QString FileThread::errorMessage() const {
	return _errorMessage;
}

} // namespace fse
