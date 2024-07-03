#pragma once

#include <QtCore/QThread>

#include <fsd/io/FileManager.hpp>

namespace fse {
class Manager;

class FileThread : public QThread {
	Q_OBJECT

public:
	FileThread(Manager* manager);
	virtual ~FileThread();

	void init();

	fsd::FileManager::Result result() const;

protected:
	fsd::FileManager* _fileManager{ nullptr };
	Manager* _manager{ nullptr };
	fsd::FileManager::Result _result{ fsd::FileManager::Result::NoResult };
	fsd::FileManager::Type _type{ fsd::FileManager::Type::NoType };
};
} // namespace fse
