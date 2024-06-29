#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QUrl>

#include <fsd/data/Model.hpp>

namespace fse {
class Manager;

class Balsam : public QObject {
	Q_OBJECT

public:
	Balsam(QObject* parent = nullptr);
	virtual ~Balsam();

	void init(Manager* manager);

	Q_INVOKABLE QUrl qmlPath(fsd::Model* model);
	Q_INVOKABLE void generate(fsd::Model* model, const QUrl& url);

private slots:
	void finalize();

private:
	Manager* _manager{ nullptr };
	fsd::Model* _current{ nullptr };
	QProcess* _process{ nullptr };
	QUrl _sourcePath{};

signals:
	void errorOccurred();
};
} // namespace fse
