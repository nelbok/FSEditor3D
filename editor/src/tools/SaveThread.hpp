#pragma once

#include <QtCore/QThread>

#include <lh/io/FileManager.hpp>

namespace lhe {
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
	lh::FileManager* _fileManager{ nullptr };
	Manager* _manager{ nullptr };
};
} // namespace lhe
