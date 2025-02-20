#pragma once

#include <QtCore/QObject>

namespace fse {
class Manager;
class Settings {
	Q_GADGET

public:
	void init(fse::Manager* manager);

	Q_INVOKABLE void save() const;
	Q_INVOKABLE void load();

private:
	fse::Manager* _manager{ nullptr };
};
} // namespace fse
