#pragma once

#include <QtCore/QObject>

#include <fsd/io/FileManager.hpp>

namespace fse {
class Manager;
class FileManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)
	Q_PROPERTY(fsd::FileManager::Result result READ result NOTIFY resultUpdated)
	Q_PROPERTY(Status status READ status NOTIFY statusUpdated)

public:
	enum class Status {
		None,
		BeginTransaction,
		Processing,
		EndTransaction,
		Stopped,
	};
	Q_ENUM(Status)

	explicit FileManager(QObject* parent = nullptr);
	~FileManager() override;

	void init(Manager* manager);
	void reset();

	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);
	Q_INVOKABLE void requestFileTransactionInterruption();

	const QUrl& tmpPath() const;
	const QUrl& oldPath() const;
	const QUrl& path() const;
	void setPath(const QUrl& path);

	fsd::FileManager::Result result() const;
	QString errorMessage() const;
	Status status() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void beginTransaction();
	void endTransaction();
	void pathUpdated();
	void resultUpdated();
	void statusUpdated();
};
} // namespace fse
