#pragma once

#include <QtCore/QObject>

#include "tools/Style.hpp"

namespace fse {
class ErrorsManager;
class StylesManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(const QString& current READ current WRITE setCurrent NOTIFY currentUpdated)
	Q_PROPERTY(const Style& style READ style NOTIFY currentUpdated)

public:
	StylesManager(QObject* parent = nullptr);
	virtual ~StylesManager();

	void init(ErrorsManager* manager);
	void createJson() const;

	const QString& current() const;
	void setCurrent(const QString& current);

	const Style& style() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void currentUpdated();
};
} // namespace fse
