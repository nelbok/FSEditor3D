#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QUrl>

#include <lh/data/Model.hpp>
#include <lh/data/Project.hpp>

namespace lhe {
class Balsam : public QObject {
	Q_OBJECT

public:
	Balsam(QObject* parent = nullptr);
	virtual ~Balsam();

	void init(lh::Project* project);

	Q_INVOKABLE void generate(lh::Model* model, const QUrl& url);

private slots:
	void finalize();

private:
	lh::Project* _project{ nullptr };
	lh::Model* _current{ nullptr };
	QProcess* _process{ nullptr };

signals:
	void errorOccurred();
};
} // namespace lhe
