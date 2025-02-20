#include <fse/tools/Style.hpp>

#include <fsd/io/Json.hpp>

using namespace fsd;

namespace fse {

namespace detail {
constexpr auto objectName = "Style";

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
	normal = Json::toColor(detail::objectName, lNormal, json);
	alternative = Json::toColor(detail::objectName, lAlternative, json);
	selected = Json::toColor(detail::objectName, lSelected, json);
	hovered = Json::toColor(detail::objectName, lHovered, json);
	disabled = Json::toColor(detail::objectName, lDisabled, json);
}

void Color::save(QJsonObject& json) const {
	json[lNormal] = Json::fromColor(normal);
	json[lAlternative] = Json::fromColor(alternative);
	json[lSelected] = Json::fromColor(selected);
	json[lHovered] = Json::fromColor(hovered);
	json[lDisabled] = Json::fromColor(disabled);
}

bool Color::operator==(const Color& other) const {
	bool ret = true;

	ret &= this->normal == other.normal;
	ret &= this->alternative == other.alternative;
	ret &= this->selected == other.selected;
	ret &= this->hovered == other.hovered;
	ret &= this->disabled == other.disabled;

	return ret;
}

constexpr auto lWidth = "width";

void Border::load(const QJsonObject& json) {
	Color::load(json);
	width = Json::toInt(detail::objectName, lWidth, json);
}

void Border::save(QJsonObject& json) const {
	Color::save(json);
	json[lWidth] = width;
}

bool Border::operator==(const Border& other) const {
	bool ret = true;

	ret &= Color::operator==(other);
	ret &= this->width == other.width;

	return ret;
}

constexpr auto lBorder = "border";
constexpr auto lRadius = "radius";

void Rectangle::load(const QJsonObject& json) {
	Color::load(json);
	border.load(Json::toObject(detail::objectName, lBorder, json));
	radius = Json::toInt(detail::objectName, lRadius, json);
}

void Rectangle::save(QJsonObject& json) const {
	Color::save(json);
	json[lBorder] = detail::save(border);
	json[lRadius] = radius;
}

bool Rectangle::operator==(const Rectangle& other) const {
	bool ret = true;

	ret &= Color::operator==(other);
	ret &= this->border == other.border;
	ret &= this->radius == other.radius;

	return ret;
}

constexpr auto lBold = "bold";
constexpr auto lItalic = "italic";
constexpr auto lPointSize = "pointSize";

void Font::load(const QJsonObject& json) {
	bold = Json::toBool(detail::objectName, lBold, json);
	italic = Json::toBool(detail::objectName, lItalic, json);
	pointSize = Json::toInt(detail::objectName, lPointSize, json);
}

void Font::save(QJsonObject& json) const {
	json[lBold] = bold;
	json[lItalic] = italic;
	json[lPointSize] = pointSize;
}

bool Font::operator==(const Font& other) const {
	bool ret = true;

	ret &= this->bold == other.bold;
	ret &= this->italic == other.italic;
	ret &= this->pointSize == other.pointSize;

	return ret;
}

constexpr auto lNewFile = "newFile";
constexpr auto lLoadFile = "loadFile";
constexpr auto lSaveFile = "saveFile";
constexpr auto lUndo = "undo";
constexpr auto lRedo = "redo";
constexpr auto lSettings = "settings";

constexpr auto lGithub = "github";
constexpr auto lDiscord = "discord";
constexpr auto lTwitter = "twitter";

void Icons::load(const QJsonObject& json) {
	newFile = Json::toString(detail::objectName, lNewFile, json);
	loadFile = Json::toString(detail::objectName, lLoadFile, json);
	saveFile = Json::toString(detail::objectName, lSaveFile, json);
	undo = Json::toString(detail::objectName, lUndo, json);
	redo = Json::toString(detail::objectName, lRedo, json);
	settings = Json::toString(detail::objectName, lSettings, json);

	github = Json::toString(detail::objectName, lGithub, json);
	discord = Json::toString(detail::objectName, lDiscord, json);
	twitter = Json::toString(detail::objectName, lTwitter, json);
}

void Icons::save(QJsonObject& json) const {
	json[lNewFile] = newFile;
	json[lLoadFile] = loadFile;
	json[lSaveFile] = saveFile;
	json[lUndo] = undo;
	json[lRedo] = redo;
	json[lSettings] = settings;

	json[lGithub] = github;
	json[lDiscord] = discord;
	json[lTwitter] = twitter;
}

bool Icons::operator==(const Icons& other) const {
	bool ret = true;

	ret &= this->newFile == other.newFile;
	ret &= this->loadFile == other.loadFile;
	ret &= this->saveFile == other.saveFile;
	ret &= this->undo == other.undo;
	ret &= this->redo == other.redo;
	ret &= this->settings == other.settings;

	ret &= this->github == other.github;
	ret &= this->discord == other.discord;
	ret &= this->twitter == other.twitter;

	return ret;
}

constexpr auto lWindow = "window";
constexpr auto lButton = "button";
constexpr auto lForeground = "foreground";

constexpr auto lTextfield = "textfield";
constexpr auto lPart = "part";
constexpr auto lList = "list";

// Fonts
constexpr auto lTitleFont = "titleFont";
constexpr auto lSubTitleFont = "subTitleFont";
constexpr auto lNormalFont = "normalFont";
constexpr auto lCopyrightFont = "copyrightFont";

// Icons
constexpr auto lIcons = "icons";

void Style::load(const QJsonObject& json) {
	window.load(Json::toObject(detail::objectName, lWindow, json));
	button.load(Json::toObject(detail::objectName, lButton, json));
	foreground.load(Json::toObject(detail::objectName, lForeground, json));

	textfield.load(Json::toObject(detail::objectName, lTextfield, json));
	part.load(Json::toObject(detail::objectName, lPart, json));
	list.load(Json::toObject(detail::objectName, lList, json));

	// Fonts
	titleFont.load(Json::toObject(detail::objectName, lTitleFont, json));
	subTitleFont.load(Json::toObject(detail::objectName, lSubTitleFont, json));
	normalFont.load(Json::toObject(detail::objectName, lNormalFont, json));
	copyrightFont.load(Json::toObject(detail::objectName, lCopyrightFont, json));

	// Icons
	icons.load(Json::toObject(detail::objectName, lIcons, json));
}

void Style::save(QJsonObject& json) const {
	json[lWindow] = detail::save(window);
	json[lButton] = detail::save(button);
	json[lForeground] = detail::save(foreground);

	json[lTextfield] = detail::save(textfield);
	json[lPart] = detail::save(part);
	json[lList] = detail::save(list);

	// Fonts
	json[lTitleFont] = detail::save(titleFont);
	json[lSubTitleFont] = detail::save(subTitleFont);
	json[lNormalFont] = detail::save(normalFont);
	json[lCopyrightFont] = detail::save(copyrightFont);

	// Icons
	json[lIcons] = detail::save(icons);
}

bool Style::operator==(const Style& other) const {
	bool ret = true;

	ret &= this->window == other.window;
	ret &= this->button == other.button;
	ret &= this->foreground == other.foreground;

	ret &= this->textfield == other.textfield;
	ret &= this->part == other.part;
	ret &= this->list == other.list;

	ret &= this->titleFont == other.titleFont;
	ret &= this->subTitleFont == other.subTitleFont;
	ret &= this->normalFont == other.normalFont;
	ret &= this->copyrightFont == other.copyrightFont;

	ret &= this->icons == other.icons;

	return ret;
}
} // namespace fse
