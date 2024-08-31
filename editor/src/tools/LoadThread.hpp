#pragma once

#include "FileThread.hpp"

namespace fse {
class LoadThread : public FileThread {
	Q_OBJECT

public:
	LoadThread(FileManager* manager, fsd::Project* project);
	virtual ~LoadThread();

protected:
	virtual void run() override;
};
} // namespace fse
