#pragma once

#include <QtCore/QObject>

namespace fse {
class ErrorsManager;
class TranslationsManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(const QString& current READ current WRITE setCurrent NOTIFY currentUpdated)

public:
	explicit TranslationsManager(QObject* parent = nullptr);
	~TranslationsManager() override;

	void init(ErrorsManager* manager);

	const QString& current() const;
	void setCurrent(const QString& current);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void currentUpdated();
};
} // namespace fse
