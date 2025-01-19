#pragma once

#include <QtCore/QObject>

namespace fse {
class UpdateManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString version READ version NOTIFY versionUpdated)

public:
	enum class Status {
		None,
		Processing,
		Finished,
		Error,
	};
	Q_ENUM(Status)

	explicit UpdateManager(QObject* parent = nullptr);
	~UpdateManager() override;

	QString version() const;
	Status status() const;

	Q_INVOKABLE void checkForUpdates();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void versionUpdated();
	void newVersionAvailable();
};
} // namespace fse
