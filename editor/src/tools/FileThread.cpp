#include "FileThread.hpp"

#include <filesystem>

#include "tools/Tools.hpp"

#include "Manager.hpp"

namespace fse {
FileThread::FileThread(Manager* manager)
	: QThread(manager)
	, _manager{ manager } {
assert(_manager);
}

FileThread::~FileThread() {}

void FileThread::init() {
	assert(!_fileManager);
	assert(_type != fsd::FileManager::Type::NoType);
	_fileManager = new fsd::FileManager(this);
	_fileManager->init(_manager->project(), _type, _manager->path());
}

fsd::FileManager::Result FileThread::result() const {
	return _result;
}

} // namespace fse
