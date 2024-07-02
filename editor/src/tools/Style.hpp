#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include <QtGui/QColor>

namespace fse {

class Color {
	Q_GADGET
	Q_PROPERTY(QColor normal MEMBER normal)
	Q_PROPERTY(QColor alternative MEMBER alternative)
	Q_PROPERTY(QColor selected MEMBER selected)
	Q_PROPERTY(QColor hovered MEMBER hovered)
	Q_PROPERTY(QColor disabled MEMBER disabled)

public:
	Color() = default;
	virtual ~Color() = default;

	Color& operator=(const Color& other);

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

	QColor normal{ 90, 7, 90 };
	QColor alternative{ 90, 7, 90 };
	QColor selected{ 90, 7, 90 };
	QColor hovered{ 90, 7, 90 };
	QColor disabled{ 90, 7, 90 };
};

bool operator!=(const Color& l, const Color& r);
bool operator==(const Color& l, const Color& r);

class Border : public Color {
	Q_GADGET
	Q_PROPERTY(int width MEMBER width)

public:
	Border() = default;
	virtual ~Border() = default;

	Border& operator=(const Border& other);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

	int width{ 0 };
};

bool operator!=(const Border& l, const Border& r);
bool operator==(const Border& l, const Border& r);

class Rectangle : public Color {
	Q_GADGET
	Q_PROPERTY(Border border MEMBER border)
	Q_PROPERTY(int radius MEMBER radius)

public:
	Rectangle() = default;
	virtual ~Rectangle() = default;

	Rectangle& operator=(const Rectangle& other);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

	Border border{};
	int radius{ 0 };
};

bool operator!=(const Rectangle& l, const Rectangle& r);
bool operator==(const Rectangle& l, const Rectangle& r);

class Font {
	Q_GADGET
	Q_PROPERTY(bool bold MEMBER bold)
	Q_PROPERTY(bool italic MEMBER italic)
	Q_PROPERTY(int pointSize MEMBER pointSize)

public:
	Font() = default;
	virtual ~Font() = default;

	Font& operator=(const Font& other);

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

	bool bold{ false };
	bool italic{ false };
	int pointSize{ 10 };
};

bool operator!=(const Font& l, const Font& r);
bool operator==(const Font& l, const Font& r);

class Style {
	Q_GADGET
	Q_PROPERTY(Color window MEMBER window)
	Q_PROPERTY(Color button MEMBER button)
	Q_PROPERTY(Color foreground MEMBER button)

	Q_PROPERTY(Rectangle textfield MEMBER textfield)
	Q_PROPERTY(Rectangle module MEMBER module)
	Q_PROPERTY(Rectangle list MEMBER list)

	Q_PROPERTY(Font titleFont MEMBER titleFont)
	Q_PROPERTY(Font subTitleFont MEMBER subTitleFont)
	Q_PROPERTY(Font normalFont MEMBER normalFont)
	Q_PROPERTY(Font copyrightFont MEMBER copyrightFont)

public:
	Style() = default;
	virtual ~Style() = default;

	Style& operator=(const Style& other);

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

	Color window;
	Color button;
	Color foreground;

	Rectangle textfield;
	Rectangle module;
	Rectangle list;

	Font titleFont;
	Font subTitleFont;
	Font normalFont;
	Font copyrightFont;
};
} // namespace fse
