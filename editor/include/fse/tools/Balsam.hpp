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
	explicit Balsam(QObject* parent = nullptr);
	~Balsam() override;

	void init(Manager* manager);

	QUrl balsamPath() const;

	Q_INVOKABLE QUrl qmlDir(const fsd::Model* model) const;
	Q_INVOKABLE QUrl qmlPath(const fsd::Model* model) const;
	Q_INVOKABLE void generate(fsd::Model* model, const QUrl& url, QStringList args = {});

	Q_INVOKABLE QProcess::ProcessError error() const;
	Q_INVOKABLE QProcess::ProcessState state() const;

private slots:
	void finalize();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void errorOccurred();
};
} // namespace fse
