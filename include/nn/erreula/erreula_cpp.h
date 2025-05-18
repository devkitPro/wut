#pragma once
#include <wut.h>
#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <padscore/kpad.h>
#include <string.h>
#include <vpad/input.h>

/**
 * \defgroup nn_erreula_erreula Error Viewer
 * \ingroup nn_erreula
 * See \link nn::erreula \endlink.
 *
 * @{
 */


#ifdef __cplusplus

namespace nn
{
namespace erreula
{

enum class ControllerType
{
   WiiRemote0 = 0,
   WiiRemote1 = 1,
   WiiRemote2 = 2,
   WiiRemote3 = 3,
   DrcGamepad = 4,
};

enum class ErrorType
{
   Code           = 0,
   Message        = 1,
   Message1Button = 2,
   Message2Button = 3,
};

enum class LangType
{
   Japanese           = 0,
   English            = 1,
   French             = 2,
   German             = 3,
   Italian            = 4,
   Spanish            = 5,
   SimplifiedChinese  = 6,
   Korean             = 7,
   Dutch              = 8,
   Portuguese         = 9,
   Russian            = 10,
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

enum class ResultType
{
   None   = 0,

   //! The user exited the error viewer
   Exited = 1,

   // TODO: More result types
};

enum class RenderTarget
{
   //! Render only to TV
   Tv   = 0,

   //! Render only to DRC gamepad
   Drc  = 1,

   //! Render to both TV and Gamepad
   Both = 2,
};

enum class State
{
   //! The error viewer is completely hidden.
   Hidden  = 0,

   //! The error viewer is drawing the fade-in animation.
   FadeIn  = 1,

   //! The error viewer is done drawing the fade in animation and completely visible.
   Visible = 2,

   //! The error viewer is drawing the fade-out animation.
   FadeOut = 3,
};

struct ErrorArg
{
   ErrorArg() :
      errorType(ErrorType::Code),
      renderTarget(RenderTarget::Both),
      controllerType(ControllerType::DrcGamepad),
      unknown0x0C(0),
      errorCode(0),
      unknown0x14(1),
      errorMessage(nullptr),
      button1Label(nullptr),
      button2Label(nullptr),
      errorTitle(nullptr),
      unknown0x28(true)
   {
   }

   ErrorType errorType;
   RenderTarget renderTarget;
   ControllerType controllerType;
   uint32_t unknown0x0C;
   int32_t errorCode;
   uint32_t unknown0x14;
   const char16_t *errorMessage;
   const char16_t *button1Label;
   const char16_t *button2Label;
   const char16_t *errorTitle;
   bool unknown0x28;
   WUT_PADDING_BYTES(3);
};
WUT_CHECK_OFFSET(ErrorArg, 0x00, errorType);
WUT_CHECK_OFFSET(ErrorArg, 0x04, renderTarget);
WUT_CHECK_OFFSET(ErrorArg, 0x08, controllerType);
WUT_CHECK_OFFSET(ErrorArg, 0x0C, unknown0x0C);
WUT_CHECK_OFFSET(ErrorArg, 0x10, errorCode);
WUT_CHECK_OFFSET(ErrorArg, 0x14, unknown0x14);
WUT_CHECK_OFFSET(ErrorArg, 0x18, errorMessage);
WUT_CHECK_OFFSET(ErrorArg, 0x1C, button1Label);
WUT_CHECK_OFFSET(ErrorArg, 0x20, button2Label);
WUT_CHECK_OFFSET(ErrorArg, 0x24, errorTitle);
WUT_CHECK_OFFSET(ErrorArg, 0x28, unknown0x28);
WUT_CHECK_SIZE(ErrorArg, 0x2C);


struct AppearArg
{
   ErrorArg errorArg;
};
WUT_CHECK_OFFSET(AppearArg, 0x00, errorArg);
WUT_CHECK_SIZE(AppearArg, 0x2C);

//! Configuration options for the error
struct CreateArg
{
   CreateArg() :
      workMemory(nullptr),
      region(RegionType::Europe),
      language(LangType::English),
      fsClient(nullptr)
   {
   }

   void *workMemory;
   RegionType region;
   LangType language;
   FSClient *fsClient;
};
WUT_CHECK_OFFSET(CreateArg, 0x00, workMemory);
WUT_CHECK_OFFSET(CreateArg, 0x04, region);
WUT_CHECK_OFFSET(CreateArg, 0x08, language);
WUT_CHECK_OFFSET(CreateArg, 0x0C, fsClient);
WUT_CHECK_SIZE(CreateArg, 0x10);


struct ControllerInfo
{
   ControllerInfo()
   {
      memset(this, 0, sizeof(*this));
   }

   const VPADStatus *vpad;
   const KPADStatus *kpad[4];
};
WUT_CHECK_OFFSET(ControllerInfo, 0x00, vpad);
WUT_CHECK_OFFSET(ControllerInfo, 0x04, kpad);
WUT_CHECK_SIZE(ControllerInfo, 0x14);

struct HomeNixSignArg
{
   HomeNixSignArg() :
      unknown0x00(1)
   {
   }

   uint32_t unknown0x00;
};
WUT_CHECK_OFFSET(HomeNixSignArg, 0x00, unknown0x00);
WUT_CHECK_SIZE(HomeNixSignArg, 0x04);

void
AppearErrorViewer(const AppearArg &arg);

void
AppearHomeNixSign(const HomeNixSignArg &arg);

void
Calc(const ControllerInfo &controllerInfo);

void
ChangeLangError(LangType languageType);

bool
Create(const CreateArg &args);

void
Destroy();

void
DisappearErrorViewer();

void
DisappearHomeNixSign();

void
DrawDRC();

void
DrawTV();

int32_t
GetResultCode();

ResultType
GetResultType();

int32_t
GetSelectButtonNumError();

State
GetStateErrorViewer();

uint32_t
GetWorkMemorySize();

bool
IsAppearHomeNixSign();

bool
IsDecideSelectButtonError();

bool
IsDecideSelectLeftButtonError();

bool
IsDecideSelectRightButtonError();

bool
IsSelectCursorActive();

bool
Jump(const char *buffer, uint32_t bufferSize);

void
PlayAppearSE(bool playAppearSoundEffect);

void
SetControllerRemo(ControllerType controller);

} // namespace erreula
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
