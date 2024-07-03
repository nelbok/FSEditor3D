#pragma once

#include <QtCore/QObject>

#include "tools/Style.hpp"

namespace fse {
class StylesManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(Style current READ current NOTIFY currentUpdated)

public:
	StylesManager(QObject* parent = nullptr);
	virtual ~StylesManager();

	void init();
	void createJson() const;

	const Style& current() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void currentUpdated();
};
} // namespace fse
