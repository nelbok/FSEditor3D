#pragma once

#include <QtCore/QObject>

namespace lhe {
class BaseCommand;
class ListCommand;

class Commands : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool canUndo READ canUndo NOTIFY updated)
	Q_PROPERTY(bool canRedo READ canRedo NOTIFY updated)

public:
	Commands(QObject* parent = nullptr);
	virtual ~Commands() = default;

	void add(BaseCommand* command);

	bool canUndo() const;
	bool canRedo() const;
	Q_INVOKABLE void undo();
	Q_INVOKABLE void redo();

	void beginList();
	void endList();

	void reset();

private:
	void internalAdd(BaseCommand* command);
	void clear(QList<BaseCommand*>& commands);

	QList<BaseCommand*> _undoCommands{};
	QList<BaseCommand*> _redoCommands{};
	QList<ListCommand*> _list{};

signals:
	void updated();
};
} // namespace lhe
