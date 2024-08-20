#include "Style.hpp"

#include <fsd/io/Json.hpp>

using namespace fsd;

namespace fse {

namespace detail {
template<class T>
QJsonObject save(const T& object) {
	QJsonObject json;
	object.save(json);
	return json;
}
} // namespace detail

constexpr auto lNormal = "normal";
constexpr auto lAlternative = "alternative";
constexpr auto lSelected = "selected";
constexpr auto lHovered = "hovered";
constexpr auto lDisabled = "disabled";

void Color::load(const QJsonObject& json) {
	normal = Json::toColor(Json::toValue(lNormal, json));
	alternative = Json::toColor(Json::toValue(lAlternative, json));
	selected = Json::toColor(Json::toValue(lSelected, json));
	hovered = Json::toColor(Json::toValue(lHovered, json));
	disabled = Json::toColor(Json::toValue(lDisabled, json));
}

void Color::save(QJsonObject& json) const {
	json[lNormal] = Json::fromColor(normal);
	json[lAlternative] = Json::fromColor(alternative);
	json[lSelected] = Json::fromColor(selected);
	json[lHovered] = Json::fromColor(hovered);
	json[lDisabled] = Json::fromColor(disabled);
}

bool operator!=(const Color& l, const Color& r) {
	return !(l == r);
}

bool operator==(const Color& l, const Color& r) {
	return l.normal == r.normal && l.alternative == r.alternative && l.selected == r.selected && l.hovered == r.hovered && l.disabled == r.disabled;
}

constexpr auto lWidth = "width";

void Border::load(const QJsonObject& json) {
	Color::load(json);
	width = Json::toInt(lWidth, json);
}

void Border::save(QJsonObject& json) const {
	Color::save(json);
	json[lWidth] = width;
}

bool operator!=(const Border& l, const Border& r) {
	return !(l == r);
}

bool operator==(const Border& l, const Border& r) {
	return *reinterpret_cast<const Color*>(&l) == *reinterpret_cast<const Color*>(&r) && l.width == r.width;
}

constexpr auto lBorder = "border";
constexpr auto lRadius = "radius";

void Rectangle::load(const QJsonObject& json) {
	Color::load(json);
	border.load(Json::toObject(lBorder, json));
	radius = Json::toInt(lRadius, json);
}

void Rectangle::save(QJsonObject& json) const {
	Color::save(json);
	json[lBorder] = detail::save(border);
	json[lRadius] = radius;
}

bool operator!=(const Rectangle& l, const Rectangle& r) {
	return !(l == r);
}

bool operator==(const Rectangle& l, const Rectangle& r) {
	return *reinterpret_cast<const Color*>(&l) == *reinterpret_cast<const Color*>(&r) && l.border == r.border && l.radius == r.radius;
}

bool operator!=(const Font& l, const Font& r) {
	return !(l == r);
}

bool operator==(const Font& l, const Font& r) {
	return l.bold == r.bold && l.italic == r.italic && l.pointSize == r.pointSize;
}

constexpr auto lBold = "bold";
constexpr auto lItalic = "italic";
constexpr auto lPointSize = "pointSize";

void Font::load(const QJsonObject& json) {
	bold = Json::toBool(lBold, json);
	italic = Json::toBool(lItalic, json);
	pointSize = Json::toInt(lPointSize, json);
}

void Font::save(QJsonObject& json) const {
	json[lBold] = bold;
	json[lItalic] = italic;
	json[lPointSize] = pointSize;
}

constexpr auto lWindow = "window";
constexpr auto lButton = "button";
constexpr auto lForeground = "foreground";

constexpr auto lTextfield = "textfield";
constexpr auto lModule = "module";
constexpr auto lList = "list";

// Fonts
constexpr auto lTitleFont = "titleFont";
constexpr auto lSubTitleFont = "subTitleFont";
constexpr auto lNormalFont = "normalFont";
constexpr auto lCopyrightFont = "copyrightFont";

// Icons
constexpr auto lNewFile = "newFile";
constexpr auto lLoadFile = "loadFile";
constexpr auto lSaveFile = "saveFile";
constexpr auto lUndo = "undo";
constexpr auto lRedo = "redo";
constexpr auto lSettings = "settings";

constexpr auto lCenterOn = "centerOn";
constexpr auto lOriginOff = "originOff";
constexpr auto lOriginOn = "originOn";
constexpr auto lOthersOff = "othersOff";
constexpr auto lOthersOn = "othersOn";

constexpr auto lGithub = "github";
constexpr auto lDiscord = "discord";
constexpr auto lTwitter = "twitter";

void Style::load(const QJsonObject& json) {
	window.load(Json::toObject(lWindow, json));
	button.load(Json::toObject(lButton, json));
	foreground.load(Json::toObject(lForeground, json));

	textfield.load(Json::toObject(lTextfield, json));
	module.load(Json::toObject(lModule, json));
	list.load(Json::toObject(lList, json));

	// Fonts
	titleFont.load(Json::toObject(lTitleFont, json));
	subTitleFont.load(Json::toObject(lSubTitleFont, json));
	normalFont.load(Json::toObject(lNormalFont, json));
	copyrightFont.load(Json::toObject(lCopyrightFont, json));

	// Icons
	newFile = Json::toString(lNewFile, json);
	loadFile = Json::toString(lLoadFile, json);
	saveFile = Json::toString(lSaveFile, json);
	undo = Json::toString(lUndo, json);
	redo = Json::toString(lRedo, json);
	settings = Json::toString(lSettings, json);

	centerOn = Json::toString(lCenterOn, json);
	originOff = Json::toString(lOriginOff, json);
	originOn = Json::toString(lOriginOn, json);
	othersOff = Json::toString(lOthersOff, json);
	othersOn = Json::toString(lOthersOn, json);

	github = Json::toString(lGithub, json);
	discord = Json::toString(lDiscord, json);
	twitter = Json::toString(lTwitter, json);
}

void Style::save(QJsonObject& json) const {
	json[lWindow] = detail::save(window);
	json[lButton] = detail::save(button);
	json[lForeground] = detail::save(foreground);

	json[lTextfield] = detail::save(textfield);
	json[lModule] = detail::save(module);
	json[lList] = detail::save(list);

	// Fonts
	json[lTitleFont] = detail::save(titleFont);
	json[lSubTitleFont] = detail::save(subTitleFont);
	json[lNormalFont] = detail::save(normalFont);
	json[lCopyrightFont] = detail::save(copyrightFont);

	// Icons
	json[lNewFile] = newFile;
	json[lLoadFile] = loadFile;
	json[lSaveFile] = saveFile;
	json[lUndo] = undo;
	json[lRedo] = redo;
	json[lSettings] = settings;

	json[lCenterOn] = centerOn;
	json[lOriginOff] = originOff;
	json[lOriginOn] = originOn;
	json[lOthersOff] = othersOff;
	json[lOthersOn] = othersOn;

	json[lGithub] = github;
	json[lDiscord] = discord;
	json[lTwitter] = twitter;
}
} // namespace fse
