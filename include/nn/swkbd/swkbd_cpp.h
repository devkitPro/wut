#pragma once
#include <wut.h>
#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <padscore/kpad.h>
#include <string.h>
#include <vpad/input.h>

/**
 * \defgroup nn_swkbd_swkbd Software Keyboard
 * \ingroup nn_swkbd
 * See \link nn::swkbd \endlink.
 *
 * @{
 */

#ifdef __cplusplus

namespace nn
{

/**
 * Graphical software keyboard, supporting several languages and configurations.
 * Applications should first call \link Create \endlink to initialise the
 * library, followed by \link AppearInputForm \endlink to show a text area and
 * virtual keyboard. Input should be forwarded to the keyboard via
 * \link Calc \endlink, along with calls to \link CalcSubThreadFont \endlink and
 * \link CalcSubThreadPredict \endlink. Finally, the keyboard can be rendered
 * with \link DrawTV \endlink and \link DrawDRC \endlink. The user's interaction
 * with the keyboard can be tracked with \link GetInputFormString \endlink,
 * \link IsDecideOkButton \endlink and \link IsDecideCancelButton \endlink; and
 * once satisfied the application can dismiss the keyboard with
 * \link DisappearInputForm \endlink. Don't forget \link Destroy \endlink!
 */
namespace swkbd
{

enum class ControllerType
{
   WiiRemote0 = 0,
   WiiRemote1 = 1,
   WiiRemote2 = 2,
   WiiRemote3 = 3,
   DrcGamepad = 4,
};

//! If the LanguageType and RegionType are not compatible, the LanguageType will be set to English, unless the RegionType is set to "Japan," in which case the LanguageType will be set to Japanese.
enum class LanguageType
{
   //! Must be used in combination with RegionType::Japan
   Japanese           = 0,
   //! Must be used in combination with RegionType::USA or RegionType::Europe
   English            = 1,
   //! Must be used in combination with RegionType::USA or RegionType::Europe
   French             = 2,
   //! Must be used in combination with RegionType::Europe
   German             = 3,
   //! Must be used in combination with RegionType::Europe
   Italian            = 4,
   //! Must be used in combination with RegionType::USA or RegionType::Europe
   Spanish            = 5,
   //! Must be used in combination with RegionType::China
   SimplifiedChinese  = 6,
   //! Must be used in combination with RegionType::Korea
   Korean             = 7,
   //! Must be used in combination with RegionType::Europe
   Dutch              = 8,
   //! Must be used in combination with RegionType::USA or RegionType::Europe
   Portuguese         = 9,
   //! Must be used in combination with RegionType::Europe
   Russian            = 10,
   //! Must be used in combination with RegionType::Taiwan
   TraditionalChinese = 11,
   Invalid            = 12,
};

enum class RegionType
{
   Japan  = 0,
   USA    = 1,
   Europe = 2,
   China  = 3,
   Korea  = 4,
   Taiwan = 5,
};

enum class State
{
   //! The input form / keyboard is completely hidden.
   Hidden  = 0,
   //! The input form / keyboard is drawing the fade in animation.
   FadeIn  = 1,
   //! The input form / keyboard is done drawing the fade in animation and completely visible.
   Visible = 2,
   //! The input form / keyboard is drawing the fade out animation.
   FadeOut = 3,
};

enum class InputFormType
{
   //! Spaced boxes design with up to 40 characters
   Boxes = 0,
   //! The page design
   Page    = 1,
};

enum class KeyboardLayout
{
   JPN_JP_QWERTY      = 0,
   USA_EN_QWERTY      = 1,
   USA_FR_QWERTY      = 2,
   USA_ES_QWERTY      = 3,
   USA_PT_QWERTY      = 4,
   EUR_EN_QWERTY      = 5,
   EUR_FR_AZERTY      = 6,
   EUR_DE_QWERTZ      = 7,
   EUR_IT_QWERTY      = 8,
   EUR_ES_QWERTY      = 9,
   EUR_NL_QWERTY      = 10,
   EUR_PT_QWERTY      = 11,
   EUR_RU_JCUKEN      = 12,
   JPN_JP_Kana        = 13,
   JPN_JP_Phone       = 14,
   JPN_JP_Handwriting = 15,
   JPN_JP_Symbols     = 16,
   USA_Special        = 17,
   EUR_Special        = 17,
   USA_Symbols        = 18,
   EUR_Symbols        = 18,
   LanguageDefault    = 19,
};

enum class KeyboardMode
{
   //! The one that fully allows utf-16LE(char16_t) charaters
   Full   = 0,
   //! Numpad used for entering for example a DNS address
   Numpad = 1,
   //! ascii, possibly used for passwords ?
   Utf8   = 2,
   //! the one thats used for registering an nnid full alphabet, numbers, '_' and '-'
   NNID   = 3,
};

enum class PasswordMode
{
   //! Show clear text
   Clear = 0,
   //! Hides the text
   Hide  = 1,
   //! Hides the charater after a few seconds
   Fade  = 2,
};

//! Configuration options for the virtual keyboard.
struct ConfigArg
{
   ConfigArg()
   {
      memset(this, 0, sizeof(*this));
      languageType   = LanguageType::English;
      controllerType = ControllerType::DrcGamepad;
      keyboardMode   = KeyboardMode::Full;
      accessFlags    = 0x7FFFF;
      keyboardLayout = KeyboardLayout::LanguageDefault;
      keyboardTab    = -1;
      unk_0x9C       = 1;
      unk_0xA4       = -1;
   }

   //! The language to use for input
   LanguageType languageType;
   ControllerType controllerType;
   KeyboardMode keyboardMode;
   //! TODO: find all bit flags
   uint32_t accessFlags; // Bitmasked!
   KeyboardLayout keyboardLayout;
   int32_t keyboardTab;
   bool unk_0x18;
   //! Text that's displayed on the "OK" button
   const char16_t *okString;
   //! The left side button exclusive to the numpad keyboard mode
   char16_t numpadCharLeft;
   //! The right side button exclusive to the numpad keyboard mode
   char16_t numpadCharRight;
   //! Bool to either enable or disable word suggestions
   bool showWordSuggestions;
   WUT_PADDING_BYTES(3);
   uint8_t unk_0x28;
   uint8_t unk_0x29;
   uint8_t unk_0x2A;
   //! If true it'll disable the new Line character on the keyboard
   bool disableNewLine;
   WUT_UNKNOWN_BYTES(0x9C - 0x2C);
   uint32_t unk_0x9C;
   //! Draws the system Wii remote pointer.
   bool drawSysWiiPointer;
   int32_t unk_0xA4;
};
WUT_CHECK_OFFSET(ConfigArg, 0x00, languageType);
WUT_CHECK_OFFSET(ConfigArg, 0x04, controllerType);
WUT_CHECK_OFFSET(ConfigArg, 0x08, keyboardMode);
WUT_CHECK_OFFSET(ConfigArg, 0x0C, accessFlags);
WUT_CHECK_OFFSET(ConfigArg, 0x10, keyboardLayout);
WUT_CHECK_OFFSET(ConfigArg, 0x14, keyboardTab);
WUT_CHECK_OFFSET(ConfigArg, 0x18, unk_0x18);
WUT_CHECK_OFFSET(ConfigArg, 0x1C, okString);
WUT_CHECK_OFFSET(ConfigArg, 0x20, numpadCharLeft);
WUT_CHECK_OFFSET(ConfigArg, 0x22, numpadCharRight);
WUT_CHECK_OFFSET(ConfigArg, 0x24, showWordSuggestions);
WUT_CHECK_OFFSET(ConfigArg, 0x28, unk_0x28);
WUT_CHECK_OFFSET(ConfigArg, 0x29, unk_0x29);
WUT_CHECK_OFFSET(ConfigArg, 0x2A, unk_0x2A);
WUT_CHECK_OFFSET(ConfigArg, 0x2B, disableNewLine);
WUT_CHECK_OFFSET(ConfigArg, 0x9C, unk_0x9C);
WUT_CHECK_OFFSET(ConfigArg, 0xA0, drawSysWiiPointer);
WUT_CHECK_OFFSET(ConfigArg, 0xA4, unk_0xA4);
WUT_CHECK_SIZE(ConfigArg, 0xA8);

struct ReceiverArg
{
   uint32_t unk_0x00 = 0;
   uint32_t unk_0x04 = 0;
   uint32_t unk_0x08 = 0;
   int32_t unk_0x0C  = -1;
   uint32_t unk_0x10 = 0;
   int32_t unk_0x14  = -1;
};
WUT_CHECK_OFFSET(ReceiverArg, 0x00, unk_0x00);
WUT_CHECK_OFFSET(ReceiverArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(ReceiverArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(ReceiverArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(ReceiverArg, 0x10, unk_0x10);
WUT_CHECK_OFFSET(ReceiverArg, 0x14, unk_0x14);
WUT_CHECK_SIZE(ReceiverArg, 0x18);

//! Arguments for the swkbd keyboard
struct KeyboardArg
{
   //! Configuration for the keyboard itself
   ConfigArg configArg;
   ReceiverArg receiverArg;
};
WUT_CHECK_SIZE(KeyboardArg, 0xC0);

//! Arguments for swkbd the input form (text area).
struct InputFormArg
{
   //! The type of input form
   InputFormType type                   = InputFormType::Page;
   int32_t unk_0x04                     = -1;
   //! Initial string to open the keyboard with
   const char16_t *initialText          = nullptr;
   //! Hint string
   const char16_t *hintText             = nullptr;
   //! The maximum number of characters that can be entered, -1 for unlimited.
   int32_t maxTextLength                = -1;
   //! Which password inputting preset to use
   nn::swkbd::PasswordMode passwordMode = nn::swkbd::PasswordMode::Clear;
   uint32_t unk_0x18                    = 0;
   //! Whether or not to draw a cursor. Exclusive to the boxes input form type.
   bool drawCursorForBoxes              = true;
   //! Whether or not to highlight the initial string. Exclusive to the Default input form type.
   bool higlightInitialText             = false;
   //! Whether or not to show a copy and a paste button.
   bool showCopyPasteButtons            = false;
   WUT_PADDING_BYTES(1);
};
WUT_CHECK_OFFSET(InputFormArg, 0x00, type);
WUT_CHECK_OFFSET(InputFormArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(InputFormArg, 0x08, initialText);
WUT_CHECK_OFFSET(InputFormArg, 0x0C, hintText);
WUT_CHECK_OFFSET(InputFormArg, 0x10, maxTextLength);
WUT_CHECK_OFFSET(InputFormArg, 0x14, passwordMode);
WUT_CHECK_OFFSET(InputFormArg, 0x18, unk_0x18);
WUT_CHECK_OFFSET(InputFormArg, 0x1C, drawCursorForBoxes);
WUT_CHECK_OFFSET(InputFormArg, 0x1D, higlightInitialText);
WUT_CHECK_OFFSET(InputFormArg, 0x1E, showCopyPasteButtons);
WUT_CHECK_SIZE(InputFormArg, 0x20);

//! Arguments for the swkbd input form and keyboard.
struct AppearArg
{
   //! Arguments for the virtual keyboard
   KeyboardArg keyboardArg;
   //! Arguments for the input form (text area)
   InputFormArg inputFormArg;
};
WUT_CHECK_SIZE(AppearArg, 0xE0);

//!The arguments used to initialise swkbd and pass in its required resources.
struct CreateArg
{
   //! A pointer to a work memory buffer; see \link GetWorkMemorySize \endlink.
   void *workMemory      = nullptr;
   //! The swkbd region to use.
   RegionType regionType = RegionType::Europe;
   uint32_t unk_0x08     = 0;
   //! An FSClient for swkbd to use while loading resources.
   FSClient *fsClient    = nullptr;
};
WUT_CHECK_OFFSET(CreateArg, 0x00, workMemory);
WUT_CHECK_OFFSET(CreateArg, 0x04, regionType);
WUT_CHECK_OFFSET(CreateArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(CreateArg, 0x0C, fsClient);
WUT_CHECK_SIZE(CreateArg, 0x10);

//! Input and controller information for swkbd.
struct ControllerInfo
{
   //! DRC input information, see \link VPADRead \endlink.
   VPADStatus *vpad    = nullptr;
   //! Wiimote and extension controller inputs, see \link KPADRead \endlink.
   KPADStatus *kpad[4] = {nullptr, nullptr, nullptr, nullptr};
};
WUT_CHECK_OFFSET(ControllerInfo, 0x00, vpad);
WUT_CHECK_OFFSET(ControllerInfo, 0x04, kpad);
WUT_CHECK_SIZE(ControllerInfo, 0x14);

struct DrawStringInfo
{
   DrawStringInfo()
   {
      memset(this, 0, sizeof(*this));
   }

   WUT_UNKNOWN_BYTES(0x1C);
};
WUT_CHECK_SIZE(DrawStringInfo, 0x1C);

struct KeyboardCondition
{
   //! Selected Language
   uint32_t unk_0x00 = 0;
   //! Selected Character menu
   uint32_t unk_0x04 = 0;
};
WUT_CHECK_OFFSET(KeyboardCondition, 0x00, unk_0x00);
WUT_CHECK_OFFSET(KeyboardCondition, 0x04, unk_0x04);
WUT_CHECK_SIZE(KeyboardCondition, 0x8);

struct IEventReceiver;
struct IControllerEventObj;
struct ISoundObj;

/**
 * Show an input form (keyboard with text area) with the given configuration.
 *
 * \param args
 * An \link nn::swkbd::AppearArg AppearArg \endlink struct with the desired
 * configuration for the keyboard and input form.
 *
 * \return
 * \c true on success, or \c false on error.
 *
 * \sa
 * - \link DisappearInputForm \endlink
 * - \link GetInputFormString \endlink
 * - \link IsDecideOkButton \endlink
 * - \link IsDecideCancelButton \endlink
 */
bool
AppearInputForm(const AppearArg &args);

/**
 * Show a keyboard with the given configuration.
 *
 * \param args
 * An \link nn::swkbd::KeyboardArg KeyboardArg \endlink struct with the desired
 * configuration for the keyboard.
 *
 * \return
 * \c true on success, or \c false on error.
 *
 * \sa
 * - \link DisappearKeyboard \endlink
 * - \link IsDecideOkButton \endlink
 * - \link IsDecideCancelButton \endlink
 */
bool
AppearKeyboard(const KeyboardArg &args);

/**
 * Calculate font data. Call in response to
 * \link IsNeedCalcSubThreadFont \endlink.
 *
 * \sa
 * - \link CalcSubThreadPredict \endlink
 * - \link Calc \endlink
 */
void
CalcSubThreadFont();

/**
 * Calculate word prediction data. Call in response to
 * \link IsNeedCalcSubThreadPredict \endlink.
 *
 * \sa
 * - \link CalcSubThreadFont \endlink
 * - \link Calc \endlink
 */
void
CalcSubThreadPredict();

/**
 * Respond to user inputs and calculate the state of input buffers and graphics.
 *
 * \param controllerInfo
 * A \link nn::swkbd::ControllerInfo ControllerInfo \endlink structure
 * containing fresh data from the controllers (see \link VPADRead \endlink
 * and \link KPADRead \endlink). Each controller can also be \c nullptr if data
 * is not available.
 *
 * \sa
 * - \link CalcSubThreadFont \endlink
 * - \link CalcSubThreadPredict \endlink
 */
void
Calc(const ControllerInfo &controllerInfo);

void
ConfirmUnfixAll();

/**
 * Initialise the swkbd library and create the keyboard and input form.
 *
 * \param args
 * A \link nn::swkbd::CreateArg CreateArg \endlink structure containing the
 * desired keyboard region, a pointer to work memory, and an
 * \link FSClient \endlink. See \link nn::swkbd::CreateArg CreateArg\endlink.
 *
 * \return
 * \c true on success, \c false otherwise.
 *
 * \sa
 * - \link Destroy \endlink
 * - \link GetWorkMemorySize \endlink
 */
bool
Create(const CreateArg &args);

/**
 * Clean up and shut down the swkbd library.
 *
 * \note
 * Resources passed into \link Create \endlink (work memory, filesystem client)
 * must be manually freed by the application <em>after</em> calling this
 * function.
 *
 * \sa
 * - \link Create \endlink
 */
void
Destroy();

/**
 * Hide a previously shown input form.
 *
 * \return
 * \c true on success, \c false otherwise.
 *
 * \sa
 * - \link AppearInputForm \endlink
 * - \link GetInputFormString \endlink
 */
bool
DisappearInputForm();

/**
 * Hide a previously shown keyboard.
 *
 * \return
 * \c true on success, \c false otherwise.
 *
 * \sa
 * - \link AppearKeyboard \endlink
 */
bool
DisappearKeyboard();

/**
 * Draw the keyboard to the DRC. Must be called inside a valid GX2 rendering
 * context, after rendering all other DRC graphics (to appear under the
 * keyboard)
 */
void
DrawDRC();

/**
 * Draw the keyboard to the TV. Must be called inside a valid GX2 rendering
 * context, after rendering all other TV graphics (to appear under the
 * keyboard)
 */
void
DrawTV();

void
GetDrawStringInfo(DrawStringInfo *drawStringInfo);

/**
 * Get the string the user typed into the input form.
 *
 * \returns
 * The user's text, as a null-terminated UTF-16 string.
 *
 * \sa
 * - \link SetInputFormString \endlink
 */
const char16_t *
GetInputFormString();

void
GetKeyboardCondition(KeyboardCondition *keyboardCondition);

/**
 * Get the current state of the input form.
 *
 * \returns
 * The current \link nn::swkbd::State State \endlink of the input form.
 */
State
GetStateInputForm();

State
GetStateKeyboard();

/**
 * Get the required size for swkbd's work memory buffer. The application must
 * allocate a buffer of this size and pass it into \link Create \endlink.
 *
 * \param unk
 * Unknown. A value of 0 seems to work.
 *
 * \return
 * The required size of the work buffer, in bytes.
 *
 * \sa
 * - \link Create \endlink
 */
uint32_t
GetWorkMemorySize(uint32_t unk);

void
InactivateSelectCursor();

bool
InitLearnDic(void *dictionary);

bool
IsCoveredWithSubWindow();

/**
 * Gets the current status of the Cancel button on the keyboard.
 *
 * \param outIsSelected
 * Pointer to a boolean to write the button status to, or \c nullptr if the
 * return value is enough.
 *
 * \return
 * \c true if the Cancel button has been pressed, or \c false otherwise.
 *
 * \sa
 * - \link IsDecideOkButton \endlink
 */
bool
IsDecideCancelButton(bool *outIsSelected);

/**
 * Gets the current status of the OK button on the keyboard.
 *
 * \param outIsSelected
 * Pointer to a boolean to write the button status to, or \c nullptr if the
 * return value is enough.
 *
 * \return
 * \c true if the OK button has been pressed, or \c false otherwise.
 *
 * \sa
 * - \link IsDecideCancelButton \endlink
 */
bool
IsDecideOkButton(bool *outIsSelected);

bool
IsKeyboardTarget(IEventReceiver *eventReceiver);

/**
 * Determines whether the font data needs calculating. If it does, a call to
 * \link CalcSubThreadFont \endlink is required.
 *
 * \return
 * \c true if the font data needs calculating, \c false otherwise.
 *
 * \sa
 * - \link IsNeedCalcSubThreadPredict \endlink
 */
bool
IsNeedCalcSubThreadFont();

/**
 * Determines whether the prediction data needs calculating. If it does, a call
 * to \link CalcSubThreadPredict \endlink is required.
 *
 * \return
 * \c true if the prediction data needs calculating, \c false otherwise.
 *
 * \sa
 * - \link IsNeedCalcSubThreadFont \endlink
 */
bool
IsNeedCalcSubThreadPredict();

/**
 * Determines whether the selection cursor is active.
 *
 * \return
 * \c true if the selection cursor is active, \c false otherwise.
 */
bool
IsSelectCursorActive();

/**
 * Mutes or unmutes the sounds generated by the keyboard.
 * Must be called inside a valid AX sound context, after AXInit and before AXQuit.
 *
 * \param muted
 * \c true to disable all sounds, or \c false to enable them.
 */
void
MuteAllSound(bool muted);

void
SetControllerRemo(ControllerType type);

/**
 * Set the character at which the cursor is positioned.
 *
 * \param pos
 * The position at which to move the cursor, with 0 corresponding to the start
 * of the string (before the first character).
 *
 * <!--
 *     TODO: check factual accuracy?
 *     Does one need to account for multiword UTF-16 characters?
 * -->
 */
void
SetCursorPos(int pos);

/**
 * Enables and disables the OK button on the keyboard. When disabled, the button
 * cannot be pressed.
 *
 * \param enable
 * \c true to enable the button, or \c false to disable it.
 */
void
SetEnableOkButton(bool enable);

/**
 * Sets the text in the input form.
 *
 * \param str
 * The UTF-16 string to set the input form to.
 *
 * \sa
 * - \link GetInputFormString \endlink
 */
void
SetInputFormString(const char16_t *str);

void
SetReceiver(const ReceiverArg &receiver);

void
SetSelectFrom(int);

void
SetUserControllerEventObj(IControllerEventObj *controllerEventObj);

void
SetUserSoundObj(ISoundObj *soundObj);

} // namespace swkbd
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
