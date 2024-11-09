#pragma once

#include <fse/tools/FileThread.hpp>

namespace fse {
class SaveThread : public FileThread {
	Q_OBJECT

public:
	SaveThread(FileManager* manager, fsd::Project* project);
	~SaveThread() override;

protected:
	void run() override;
};
} // namespace fse
