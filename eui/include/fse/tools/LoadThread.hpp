#pragma once

#include <fse/tools/FileThread.hpp>

namespace fse {
class LoadThread : public FileThread {
	Q_OBJECT

public:
	LoadThread(FileManager* manager, fsd::Project* project);
	~LoadThread() override;

protected:
	void run() override;
};
} // namespace fse
