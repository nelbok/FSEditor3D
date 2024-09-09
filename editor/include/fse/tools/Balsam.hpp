#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QUrl>

#include <fsd/data/Model.hpp>

namespace fse {
class CommandsManager;
class FileManager;

class Balsam : public QObject {
	Q_OBJECT

public:
	Balsam(QObject* parent = nullptr);
	virtual ~Balsam();

	void init(FileManager* manager, CommandsManager* commands);

	QUrl balsamPath() const;

	Q_INVOKABLE QUrl qmlPath(fsd::Model* model);
	Q_INVOKABLE void generate(fsd::Model* model, const QUrl& url, QStringList args = {});

	Q_INVOKABLE QProcess::ProcessError error() const;
	Q_INVOKABLE QProcess::ProcessState state() const;

private slots:
	void finalize();

private:
	FileManager* _manager{ nullptr };
	CommandsManager* _commands{ nullptr };
	fsd::Model* _current{ nullptr };
	QProcess* _process{ nullptr };
	QUrl _sourcePath{};

signals:
	void errorOccurred();
};
} // namespace fse
