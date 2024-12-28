#pragma once

#include <QtCore/QObject>

#include <fse/tools/KeyBindings.hpp>

namespace fse {
class KeyBindingsManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(KeyBindingsType current READ current WRITE setCurrent NOTIFY currentUpdated)
	Q_PROPERTY(KeyBindings* keyBindings READ keyBindings NOTIFY currentUpdated)

public:
	enum class KeyBindingsType {
		Custom,
		Qwerty,
		Azerty,
	};
	Q_ENUM(KeyBindingsType)

	explicit KeyBindingsManager(QObject* parent = nullptr);
	~KeyBindingsManager() override;

	void init();

	KeyBindingsType current() const;
	void setCurrent(KeyBindingsType current);

	KeyBindings* keyBindings() const;

	Q_INVOKABLE QString toString(Qt::Key key) const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void currentUpdated();
};
} // namespace fse
