#pragma once

#include <QtCore/QObject>

namespace fse {

class BaseCommand : public QObject {
	Q_OBJECT

public:
	BaseCommand(QObject* parent = nullptr);
	virtual ~BaseCommand() = default;

	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual void finalize() {}
	virtual void clean() {}
};
} // namespace fse
