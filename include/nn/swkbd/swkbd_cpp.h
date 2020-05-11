#pragma once
#include <wut.h>
#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <padscore/kpad.h>
#include <vpad/input.h>
#include <string.h>

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
   Unknown0 = 0,
};

enum class LanguageType
{
   Japanese = 0,
   English  = 1,
};

enum class RegionType
{
   Japan    = 0,
   USA      = 1,
   Europe   = 2,
};

enum class State
{
   //! The input form / keyboard is completely hidden.
   Hidden   = 0,
   //! The input form / keyboard is drawing the fade in animation.
   FadeIn   = 1,
   //! The input form / keyboard is done drawing the fade in animation and completely visible.
   Visible  = 2,
   //! The input form / keyboard is drawing the fade out animation.
   FadeOut  = 3,
};

//! Configuration options for the virtual keyboard.
struct ConfigArg
{
   ConfigArg()
   {
      memset(this, 0, sizeof(*this));
      languageType = LanguageType::English;
      unk_0x04 = 4;
      unk_0x0C = 0x7FFFF;
      unk_0x10 = 19;
      unk_0x14 = -1;
      unk_0x9C = 1;
      unk_0xA4 = -1;
   }

   //! The language to use for input
   LanguageType languageType;
   uint32_t unk_0x04;
   uint32_t unk_0x08;
   uint32_t unk_0x0C;
   uint32_t unk_0x10;
   int32_t unk_0x14;
   WUT_UNKNOWN_BYTES(0x9C - 0x18);
   uint32_t unk_0x9C;
   WUT_UNKNOWN_BYTES(4);
   int32_t unk_0xA4;
};
WUT_CHECK_OFFSET(ConfigArg, 0x00, languageType);
WUT_CHECK_OFFSET(ConfigArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(ConfigArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(ConfigArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(ConfigArg, 0x10, unk_0x10);
WUT_CHECK_OFFSET(ConfigArg, 0x14, unk_0x14);
WUT_CHECK_OFFSET(ConfigArg, 0x9C, unk_0x9C);
WUT_CHECK_OFFSET(ConfigArg, 0xA4, unk_0xA4);
WUT_CHECK_SIZE(ConfigArg, 0xA8);

struct ReceiverArg
{
   uint32_t unk_0x00 = 0;
   uint32_t unk_0x04 = 0;
   uint32_t unk_0x08 = 0;
   int32_t unk_0x0C = -1;
   uint32_t unk_0x10 = 0;
   int32_t unk_0x14 = -1;
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
   uint32_t unk_0x00 = 1;
   int32_t unk_0x04 = -1;
   uint32_t unk_0x08 = 0;
   uint32_t unk_0x0C = 0;
   //! The maximum number of characters that can be entered, -1 for unlimited.
   int32_t maxTextLength = -1;
   uint32_t unk_0x14 = 0;
   uint32_t unk_0x18 = 0;
   bool unk_0x1C = false;
   bool unk_0x1D = false;
   bool unk_0x1E = false;
   WUT_PADDING_BYTES(1);
};
WUT_CHECK_OFFSET(InputFormArg, 0x00, unk_0x00);
WUT_CHECK_OFFSET(InputFormArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(InputFormArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(InputFormArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(InputFormArg, 0x10, maxTextLength);
WUT_CHECK_OFFSET(InputFormArg, 0x14, unk_0x14);
WUT_CHECK_OFFSET(InputFormArg, 0x18, unk_0x18);
WUT_CHECK_OFFSET(InputFormArg, 0x1C, unk_0x1C);
WUT_CHECK_OFFSET(InputFormArg, 0x1D, unk_0x1D);
WUT_CHECK_OFFSET(InputFormArg, 0x1E, unk_0x1E);
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
   void *workMemory = nullptr;
   //! The swkbd region to use.
   RegionType regionType = RegionType::Europe;
   uint32_t unk_0x08 = 0;
   //! An FSClient for swkbd to use while loading resources.
   FSClient *fsClient = nullptr;
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
   VPADStatus *vpad = nullptr;
   //! Wiimote and extension controller inputs, see \link KPADRead \endlink.
   KPADStatus *kpad[4] = { nullptr, nullptr, nullptr, nullptr };
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
   uint32_t unk_0x00 = 0;
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
AppearInputForm(const AppearArg& args);

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
AppearKeyboard(const KeyboardArg& args);

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
