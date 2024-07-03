#pragma once

#include "FileThread.hpp"

namespace fse {
class Manager;

class LoadThread : public FileThread {
	Q_OBJECT

public:
	LoadThread(Manager* manager);
	virtual ~LoadThread();

protected:
	virtual void run() override;
};
} // namespace fse
