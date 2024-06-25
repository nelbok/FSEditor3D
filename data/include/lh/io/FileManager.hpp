#pragma once

#include <QtCore/QDeadlineTimer>
#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace lh {
class Project;

class FileManager : public QObject {
	Q_OBJECT

public:
	enum class Type {
		Save,
		Load,
		NoType,
	};
	Q_ENUM(Type)

	enum class Result {
		Success,
		Canceled,
		Error,
		NoResult,
	};
	Q_ENUM(Result)


	FileManager(QObject* parent = nullptr);
	virtual ~FileManager() = default;

	Q_INVOKABLE void init(Project* project, Type type, const QUrl& url);
	Q_INVOKABLE void start();
	Q_INVOKABLE void wait(QDeadlineTimer deadline = QDeadlineTimer(QDeadlineTimer::Forever));
	Q_INVOKABLE bool isFinished();
	Q_INVOKABLE bool isRunning();
	Q_INVOKABLE Result result() const;
	Q_INVOKABLE void requestInterruption();

private:
	class Impl;
	Impl* _impl{ nullptr };

signals:
	void finished();
};
} // namespace lh
