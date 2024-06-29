#pragma once

#include <QtCore/QThread>

#include <fsd/io/FileManager.hpp>

namespace fse {
class Manager;

class SaveThread : public QThread {
	Q_OBJECT

public:
	SaveThread(Manager* manager);
	virtual ~SaveThread();

	void init();

	// Result method

protected:
	virtual void run() override;

private:
	fsd::FileManager* _fileManager{ nullptr };
	Manager* _manager{ nullptr };
};
} // namespace fse
