#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include <QtCore/QUuid>
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

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

	int width{ 0 };
};

bool operator!=(const Border& l, const Border& r);
bool operator==(const Border& l, const Border& r);

class Rectangle : public Color {
	Q_GADGET
	Q_PROPERTY(const Border& border MEMBER border)
	Q_PROPERTY(int radius MEMBER radius)

public:
	Rectangle() = default;
	virtual ~Rectangle() = default;

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
	Q_PROPERTY(const Color& window MEMBER window)
	Q_PROPERTY(const Color& button MEMBER button)
	Q_PROPERTY(const Color& foreground MEMBER foreground)

	Q_PROPERTY(const Rectangle& textfield MEMBER textfield)
	Q_PROPERTY(const Rectangle& module MEMBER module)
	Q_PROPERTY(const Rectangle& list MEMBER list)

	// Fonts
	Q_PROPERTY(const Font& titleFont MEMBER titleFont)
	Q_PROPERTY(const Font& subTitleFont MEMBER subTitleFont)
	Q_PROPERTY(const Font& normalFont MEMBER normalFont)
	Q_PROPERTY(const Font& copyrightFont MEMBER copyrightFont)

	// Icons
	Q_PROPERTY(QString newFile MEMBER newFile)
	Q_PROPERTY(QString loadFile MEMBER loadFile)
	Q_PROPERTY(QString saveFile MEMBER saveFile)
	Q_PROPERTY(QString undo MEMBER undo)
	Q_PROPERTY(QString redo MEMBER redo)
	Q_PROPERTY(QString settings MEMBER settings)

	Q_PROPERTY(QString github MEMBER github)
	Q_PROPERTY(QString discord MEMBER discord)
	Q_PROPERTY(QString twitter MEMBER twitter)

public:
	Style() = default;
	virtual ~Style() = default;

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

	Color window;
	Color button;
	Color foreground;

	Rectangle textfield;
	Rectangle module;
	Rectangle list;

	// Fonts
	Font titleFont;
	Font subTitleFont;
	Font normalFont;
	Font copyrightFont;

	// Icons
	QString newFile;
	QString loadFile;
	QString saveFile;
	QString undo;
	QString redo;
	QString settings;

	QString github;
	QString discord;
	QString twitter;
};
} // namespace fse
