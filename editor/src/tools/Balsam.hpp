#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QUrl>

#include <lh/data/Model.hpp>

namespace lhe {
class Manager;

class Balsam : public QObject {
	Q_OBJECT

public:
	Balsam(QObject* parent = nullptr);
	virtual ~Balsam();

	void init(Manager* manager);

	Q_INVOKABLE QUrl qmlPath(lh::Model* model);
	Q_INVOKABLE void generate(lh::Model* model, const QUrl& url);

private slots:
	void finalize();

private:
	Manager* _manager{ nullptr };
	lh::Model* _current{ nullptr };
	QProcess* _process{ nullptr };
	QUrl _sourcePath{};

signals:
	void errorOccurred();
};
} // namespace lhe
