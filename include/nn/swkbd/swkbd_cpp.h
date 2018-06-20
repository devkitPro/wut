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
 * @{
 */

#ifdef __cplusplus

namespace nn
{
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
   Unknown0 = 0,
};

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
WUT_CHECK_OFFSET(ConfigArg, languageType, 0x00);
WUT_CHECK_OFFSET(ConfigArg, unk_0x04, 0x04);
WUT_CHECK_OFFSET(ConfigArg, unk_0x08, 0x08);
WUT_CHECK_OFFSET(ConfigArg, unk_0x0C, 0x0C);
WUT_CHECK_OFFSET(ConfigArg, unk_0x10, 0x10);
WUT_CHECK_OFFSET(ConfigArg, unk_0x14, 0x14);
WUT_CHECK_OFFSET(ConfigArg, unk_0x9C, 0x9C);
WUT_CHECK_OFFSET(ConfigArg, unk_0xA4, 0xA4);
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
WUT_CHECK_OFFSET(ReceiverArg, unk_0x00, 0x00);
WUT_CHECK_OFFSET(ReceiverArg, unk_0x04, 0x04);
WUT_CHECK_OFFSET(ReceiverArg, unk_0x08, 0x08);
WUT_CHECK_OFFSET(ReceiverArg, unk_0x0C, 0x0C);
WUT_CHECK_OFFSET(ReceiverArg, unk_0x10, 0x10);
WUT_CHECK_OFFSET(ReceiverArg, unk_0x14, 0x14);
WUT_CHECK_SIZE(ReceiverArg, 0x18);

struct KeyboardArg
{
   ConfigArg configArg;
   ReceiverArg receiverArg;
};
WUT_CHECK_SIZE(KeyboardArg, 0xC0);

struct InputFormArg
{
   uint32_t unk_0x00 = 1;
   int32_t unk_0x04 = -1;
   uint32_t unk_0x08 = 0;
   uint32_t unk_0x0C = 0;
   int32_t maxTextLength = -1;
   uint32_t unk_0x14 = 0;
   uint32_t unk_0x18 = 0;
   bool unk_0x1C = false;
   bool unk_0x1D = false;
   bool unk_0x1E = false;
   WUT_PADDING_BYTES(1);
};
WUT_CHECK_OFFSET(InputFormArg, unk_0x00, 0x00);
WUT_CHECK_OFFSET(InputFormArg, unk_0x04, 0x04);
WUT_CHECK_OFFSET(InputFormArg, unk_0x08, 0x08);
WUT_CHECK_OFFSET(InputFormArg, unk_0x0C, 0x0C);
WUT_CHECK_OFFSET(InputFormArg, maxTextLength, 0x10);
WUT_CHECK_OFFSET(InputFormArg, unk_0x14, 0x14);
WUT_CHECK_OFFSET(InputFormArg, unk_0x18, 0x18);
WUT_CHECK_OFFSET(InputFormArg, unk_0x1C, 0x1C);
WUT_CHECK_OFFSET(InputFormArg, unk_0x1D, 0x1D);
WUT_CHECK_OFFSET(InputFormArg, unk_0x1E, 0x1E);
WUT_CHECK_SIZE(InputFormArg, 0x20);

struct AppearArg
{
   KeyboardArg keyboardArg;
   InputFormArg inputFormArg;
};
WUT_CHECK_SIZE(AppearArg, 0xE0);

struct CreateArg
{
   void *workMemory = nullptr;
   RegionType regionType = RegionType::Europe;
   uint32_t unk_0x08 = 0;
   FSClient *fsClient = nullptr;
};
WUT_CHECK_OFFSET(CreateArg, 0x00, workMemory);
WUT_CHECK_OFFSET(CreateArg, 0x04, regionType);
WUT_CHECK_OFFSET(CreateArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(CreateArg, 0x0C, fsClient);
WUT_CHECK_SIZE(CreateArg, 0x10);

struct ControllerInfo
{
   VPADStatus *vpad = nullptr;
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
WUT_CHECK_OFFSET(KeyboardCondition, unk_0x00, 0x00);
WUT_CHECK_OFFSET(KeyboardCondition, unk_0x04, 0x04);
WUT_CHECK_SIZE(KeyboardCondition, 0x8);

struct IEventReceiver;
struct IControllerEventObj;
struct ISoundObj;

bool
AppearInputForm(const AppearArg& args);

bool
AppearKeyboard(const KeyboardArg& args);

void
CalcSubThreadFont();

void
CalcSubThreadPredict();

void
Calc(const ControllerInfo &controllerInfo);

void
ConfirmUnfixAll();

bool
Create(const CreateArg &args);

void
Destroy();

bool
DisappearInputForm();

bool
DisappearKeyboard();

void
DrawDRC();

void
DrawTV();

void
GetDrawStringInfo(DrawStringInfo *drawStringInfo);

const char16_t *
GetInputFormString();

void
GetKeyboardCondition(KeyboardCondition *keyboardCondition);

State
GetStateInputForm();

State
GetStateKeyboard();

uint32_t
GetWorkMemorySize(uint32_t unk);

void
InactivateSelectCursor();


bool
InitLearnDic(void *dictionary);

bool
IsCoveredWithSubWindow();

bool
IsDecideCancelButton(bool *outIsSelected);

bool
IsDecideOkButton(bool *outIsSelected);

bool
IsKeyboardTarget(IEventReceiver *eventReceiver);

bool
IsNeedCalcSubThreadFont();

bool
IsNeedCalcSubThreadPredict();

bool
IsSelectCursorActive();

void
MuteAllSound(bool muted);

void
SetControllerRemo(ControllerType type);

void
SetCursorPos(int);

void
SetEnableOkButton(bool);

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
