#pragma once

#include <QtCore/QObject>

#include <fsd/io/FileManager.hpp>

namespace fse {
class Manager;
class FileManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)

public:
	FileManager(QObject* parent = nullptr);
	virtual ~FileManager();

	void init(Manager* manager);
	void reset();

	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);
	Q_INVOKABLE void requestFileTransactionInterruption();

	const QUrl& tmpPath() const;
	const QUrl& oldPath() const;
	const QUrl& path() const;
	void setPath(const QUrl& path);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void beginFileTransaction();
	void endFileTransaction(fsd::FileManager::Result result);
	void pathUpdated();
};
} // namespace fse
