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
	bool operator==(const Color& other) const;

	QColor normal{ 90, 7, 90 };
	QColor alternative{ 90, 7, 90 };
	QColor selected{ 90, 7, 90 };
	QColor hovered{ 90, 7, 90 };
	QColor disabled{ 90, 7, 90 };
};

class Border : public Color {
	Q_GADGET
	Q_PROPERTY(int width MEMBER width)

public:
	Border() = default;
	~Border() override = default;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;
	bool operator==(const Border& other) const;

	int width{ 0 };
};

class Rectangle : public Color {
	Q_GADGET
	Q_PROPERTY(const Border& border MEMBER border)
	Q_PROPERTY(int radius MEMBER radius)

public:
	Rectangle() = default;
	~Rectangle() override = default;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;
	bool operator==(const Rectangle& other) const;

	Border border{};
	int radius{ 0 };
};

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
	bool operator==(const Font& other) const;

	bool bold{ false };
	bool italic{ false };
	int pointSize{ 10 };
};

class Icons {
	Q_GADGET
	Q_PROPERTY(QString newFile MEMBER newFile)
	Q_PROPERTY(QString loadFile MEMBER loadFile)
	Q_PROPERTY(QString saveFile MEMBER saveFile)
	Q_PROPERTY(QString undo MEMBER undo)
	Q_PROPERTY(QString redo MEMBER redo)
	Q_PROPERTY(QString settings MEMBER settings)

	Q_PROPERTY(QString centerOn MEMBER centerOn)
	Q_PROPERTY(QString originOff MEMBER originOff)
	Q_PROPERTY(QString originOn MEMBER originOn)
	Q_PROPERTY(QString othersOff MEMBER othersOff)
	Q_PROPERTY(QString othersOn MEMBER othersOn)
	Q_PROPERTY(QString worldMapOff MEMBER worldMapOff)
	Q_PROPERTY(QString worldMapOn MEMBER worldMapOn)

	Q_PROPERTY(QString github MEMBER github)
	Q_PROPERTY(QString discord MEMBER discord)
	Q_PROPERTY(QString twitter MEMBER twitter)

public:
	Icons() = default;
	virtual ~Icons() = default;

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;
	bool operator==(const Icons& other) const;

	QString newFile;
	QString loadFile;
	QString saveFile;
	QString undo;
	QString redo;
	QString settings;

	QString centerOn;
	QString originOff;
	QString originOn;
	QString othersOff;
	QString othersOn;
	QString worldMapOff;
	QString worldMapOn;

	QString github;
	QString discord;
	QString twitter;
};

class Style {
	Q_GADGET
	Q_PROPERTY(const Color& window MEMBER window)
	Q_PROPERTY(const Color& button MEMBER button)
	Q_PROPERTY(const Color& foreground MEMBER foreground)

	Q_PROPERTY(const Rectangle& textfield MEMBER textfield)
	Q_PROPERTY(const Rectangle& part MEMBER part)
	Q_PROPERTY(const Rectangle& list MEMBER list)

	// Fonts
	Q_PROPERTY(const Font& titleFont MEMBER titleFont)
	Q_PROPERTY(const Font& subTitleFont MEMBER subTitleFont)
	Q_PROPERTY(const Font& normalFont MEMBER normalFont)
	Q_PROPERTY(const Font& copyrightFont MEMBER copyrightFont)

	// Icons
	Q_PROPERTY(const Icons& icons MEMBER icons)

public:
	Style() = default;
	virtual ~Style() = default;

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;
	bool operator==(const Style& other) const;

	Color window;
	Color button;
	Color foreground;

	Rectangle textfield;
	Rectangle part;
	Rectangle list;

	// Fonts
	Font titleFont;
	Font subTitleFont;
	Font normalFont;
	Font copyrightFont;

	// Icons
	Icons icons;
};
} // namespace fse
