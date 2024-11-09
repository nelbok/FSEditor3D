#pragma once

#include <QtCore/QThread>

#include <fsd/data/Project.hpp>
#include <fsd/io/FileManager.hpp>

namespace fse {
class FileManager;

class FileThread : public QThread {
	Q_OBJECT

public:
	FileThread(FileManager* manager, fsd::Project* project);
	~FileThread() override;

	void init();

	fsd::FileManager::Result result() const;

protected:
	fsd::Project* _project{ nullptr };
	fsd::FileManager* _fileManager{ nullptr };
	fsd::FileManager::Result _result{ fsd::FileManager::Result::NoResult };
	fsd::FileManager::Type _type{ fsd::FileManager::Type::NoType };

	FileManager* _manager{ nullptr };
};
} // namespace fse
