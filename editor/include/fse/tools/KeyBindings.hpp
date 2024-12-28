#pragma once

#include <QtCore/QObject>

namespace fse {
class KeyBindings : public QObject {
	Q_OBJECT

	Q_PROPERTY(Qt::Key forward1 MEMBER forward1 NOTIFY updated)
	Q_PROPERTY(Qt::Key forward2 MEMBER forward2 NOTIFY updated)
	Q_PROPERTY(Qt::Key backward1 MEMBER backward1 NOTIFY updated)
	Q_PROPERTY(Qt::Key backward2 MEMBER backward2 NOTIFY updated)
	Q_PROPERTY(Qt::Key left1 MEMBER left1 NOTIFY updated)
	Q_PROPERTY(Qt::Key left2 MEMBER left2 NOTIFY updated)
	Q_PROPERTY(Qt::Key right1 MEMBER right1 NOTIFY updated)
	Q_PROPERTY(Qt::Key right2 MEMBER right2 NOTIFY updated)
	Q_PROPERTY(Qt::Key up1 MEMBER up1 NOTIFY updated)
	Q_PROPERTY(Qt::Key up2 MEMBER up2 NOTIFY updated)
	Q_PROPERTY(Qt::Key down1 MEMBER down1 NOTIFY updated)
	Q_PROPERTY(Qt::Key down2 MEMBER down2 NOTIFY updated)
	Q_PROPERTY(Qt::Key sprint MEMBER sprint NOTIFY updated)

public:
	explicit KeyBindings(QObject* parent = nullptr);
	~KeyBindings() override;

	bool operator==(const KeyBindings& other) const;

	Qt::Key forward1{ Qt::Key_unknown };
	Qt::Key forward2{ Qt::Key_unknown };
	Qt::Key backward1{ Qt::Key_unknown };
	Qt::Key backward2{ Qt::Key_unknown };
	Qt::Key left1{ Qt::Key_unknown };
	Qt::Key left2{ Qt::Key_unknown };
	Qt::Key right1{ Qt::Key_unknown };
	Qt::Key right2{ Qt::Key_unknown };
	Qt::Key up1{ Qt::Key_unknown };
	Qt::Key up2{ Qt::Key_unknown };
	Qt::Key down1{ Qt::Key_unknown };
	Qt::Key down2{ Qt::Key_unknown };
	Qt::Key sprint{ Qt::Key_unknown };

signals:
	void updated();
};
} // namespace fse
