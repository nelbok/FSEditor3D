#pragma once

namespace fse::DefaultSettings {
// UI
constexpr auto uiKey = "ui";
constexpr auto uiStyleKey = "style";
constexpr auto uiStyleValue = "basic";
constexpr auto uiTranslationKey = "translation";
constexpr auto uiTranslationValue = "en";

// Preview
constexpr auto previewKey = "preview";
constexpr auto previewHeightKey = "height";
constexpr auto previewHeightValue = 160u;
constexpr auto previewAreEntryPointsVisibleKey = "areEntryPointsVisible";
constexpr auto previewAreEntryPointsVisibleValue = false;
constexpr auto previewAreLinksVisibleKey = "areLinksVisible";
constexpr auto previewAreLinksVisibleValue = true;
constexpr auto previewAreObjectsVisibleKey = "areObjectsVisible";
constexpr auto previewAreObjectsVisibleValue = true;
constexpr auto previewIsWorldModeKey = "isWorldMode";
constexpr auto previewIsWorldModeValue = false;
constexpr auto previewIsDebugModeKey = "isDebugMode";
constexpr auto previewIsDebugModeValue = false;

// KeyBinding
constexpr auto keyBindingsKey = "keybindings";
constexpr auto keyBindingsForward1Key = "forward1";
constexpr auto keyBindingsForward1Value = Qt::Key_W;
constexpr auto keyBindingsForward2Key = "forward2";
constexpr auto keyBindingsForward2Value = Qt::Key_Up;
constexpr auto keyBindingsBackward1Key = "backward1";
constexpr auto keyBindingsBackward1Value = Qt::Key_S;
constexpr auto keyBindingsBackward2Key = "backward2";
constexpr auto keyBindingsBackward2Value = Qt::Key_Down;
constexpr auto keyBindingsLeft1Key = "left1";
constexpr auto keyBindingsLeft1Value = Qt::Key_A;
constexpr auto keyBindingsLeft2Key = "left2";
constexpr auto keyBindingsLeft2Value = Qt::Key_Left;
constexpr auto keyBindingsRight1Key = "right1";
constexpr auto keyBindingsRight1Value = Qt::Key_D;
constexpr auto keyBindingsRight2Key = "right2";
constexpr auto keyBindingsRight2Value = Qt::Key_Right;
constexpr auto keyBindingsUp1Key = "up1";
constexpr auto keyBindingsUp1Value = Qt::Key_R;
constexpr auto keyBindingsUp2Key = "up2";
constexpr auto keyBindingsUp2Value = Qt::Key_PageUp;
constexpr auto keyBindingsDown1Key = "down1";
constexpr auto keyBindingsDown1Value = Qt::Key_F;
constexpr auto keyBindingsDown2Key = "down2";
constexpr auto keyBindingsDown2Value = Qt::Key_PageDown;
constexpr auto keyBindingsSprintKey = "sprint";
constexpr auto keyBindingsSprintValue = Qt::Key_Shift;

} // namespace fse::DefaultSettings
