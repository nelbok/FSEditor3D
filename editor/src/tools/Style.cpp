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

Color& Color::operator=(const Color& other) {
	this->normal = other.normal;
	this->alternative = other.alternative;
	this->selected = other.selected;
	this->hovered = other.hovered;
	this->disabled = other.disabled;
	return *this;
}

constexpr auto lNormal = "normal";
constexpr auto lAlternative = "alternative";
constexpr auto lSelected = "selected";
constexpr auto lHovered = "hovered";
constexpr auto lDisabled = "disabled";

void Color::load(const QJsonObject& json) {
	normal = Json::toColor(Json::toObject(lNormal, json));
	alternative = Json::toColor(Json::toObject(lAlternative, json));
	selected = Json::toColor(Json::toObject(lSelected, json));
	hovered = Json::toColor(Json::toObject(lHovered, json));
	disabled = Json::toColor(Json::toObject(lDisabled, json));
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

Border& Border::operator=(const Border& other) {
	Color::operator=(other);
	this->width = other.width;
	return *this;
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

Rectangle& Rectangle::operator=(const Rectangle& other) {
	Color::operator=(other);
	this->border = other.border;
	this->radius = other.radius;
	return *this;
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

Font& Font::operator=(const Font& other) {
	this->bold = other.bold;
	this->italic = other.italic;
	this->pointSize = other.pointSize;
	return *this;
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

Style& Style::operator=(const Style& other) {
	this->window = other.window;
	this->button = other.button;
	this->foreground = other.foreground;

	this->textfield = other.textfield;
	this->module = other.module;
	this->list = other.list;

	this->titleFont = other.titleFont;
	this->subTitleFont = other.subTitleFont;
	this->normalFont = other.normalFont;
	this->copyrightFont = other.copyrightFont;

	return *this;
}

constexpr auto lWindow = "window";
constexpr auto lButton = "button";
constexpr auto lForeground = "foreground";

constexpr auto lTextfield = "textfield";
constexpr auto lModule = "module";
constexpr auto lList = "list";

constexpr auto lTitleFont = "titleFont";
constexpr auto lSubTitleFont = "subTitleFont";
constexpr auto lNormalFont = "normalFont";
constexpr auto lCopyrightFont = "copyrightFont";

void Style::load(const QJsonObject& json) {
	window.load(Json::toObject(lWindow, json));
	button.load(Json::toObject(lButton, json));
	foreground.load(Json::toObject(lForeground, json));

	textfield.load(Json::toObject(lTextfield, json));
	module.load(Json::toObject(lModule, json));
	list.load(Json::toObject(lList, json));

	titleFont.load(Json::toObject(lTitleFont, json));
	subTitleFont.load(Json::toObject(lSubTitleFont, json));
	normalFont.load(Json::toObject(lNormalFont, json));
	copyrightFont.load(Json::toObject(lCopyrightFont, json));
}

void Style::save(QJsonObject& json) const {
	json[lWindow] = detail::save(window);
	json[lButton] = detail::save(button);
	json[lForeground] = detail::save(foreground);

	json[lTextfield] = detail::save(textfield);
	json[lModule] = detail::save(module);
	json[lList] = detail::save(list);

	json[lTitleFont] = detail::save(titleFont);
	json[lSubTitleFont] = detail::save(subTitleFont);
	json[lNormalFont] = detail::save(normalFont);
	json[lCopyrightFont] = detail::save(copyrightFont);
}
} // namespace fse
