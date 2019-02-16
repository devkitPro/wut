#pragma once
#include <wut.h>
#include <nn/swkbd.h>

/**
 * \defgroup swkbd_rpl RPL Interface
 * \ingroup swkbd
 * C++ linkage for swkbd, see \link nn::swkbd \endlink for general use.
 * @{
 */

#ifdef __cplusplus

namespace Rpl
{

bool SwkbdAppearInputForm(const nn::swkbd::AppearArg &appearArg);
bool SwkbdAppearKeyboard(const nn::swkbd::KeyboardArg &keyboardArg);
void SwkbdCalcSubThreadFont();
void SwkbdCalcSubThreadPredict();
void SwkbdCalc(const nn::swkbd::ControllerInfo &controllerInfo);
void SwkbdConfirmUnfixAll();
void SwkbdCreate(void *buffer, nn::swkbd::RegionType regionType,
                 uint32_t unk, FSClient *fsClient);
void SwkbdDestroy();
bool SwkbdDisappearInputForm();
bool SwkbdDisappearKeyboard();
void SwkbdDrawDRC();
void SwkbdDrawTV();
void SwkbdGetDrawStringInfo(nn::swkbd::DrawStringInfo *drawStringInfo);
const char16_t *SwkbdGetInputFormString();
void SwkbdGetKeyboardCondition(nn::swkbd::KeyboardCondition *keyboardCondition);
nn::swkbd::State SwkbdGetStateInputForm();
nn::swkbd::State SwkbdGetStateKeyboard();
void SwkbdInactivateSelectCursor();
bool SwkbdInitLearnDic(void *buffer);
bool SwkbdIsCoveredWithSubWindow();
bool SwkbdIsDecideCancelButton(bool *outIsSelectCursor);
bool SwkbdIsDecideOkButton(bool *outIsSelectCursor);
bool SwkbdIsKeyboardTarget(nn::swkbd::IEventReceiver *eventReceiver);
bool SwkbdIsNeedCalcSubThreadFont();
bool SwkbdIsNeedCalcSubThreadPredict();
bool SwkbdIsSelectCursorActive();
void SwkbdMuteAllSound(bool muted);
void SwkbdSetControllerRemo(nn::swkbd::ControllerType type);
void SwkbdSetCursorPos(int pos);
void SwkbdSetEnableOkButton(bool enable);
void SwkbdSetInputFormString(const char16_t *str);
void SwkbdSetReceiver(const nn::swkbd::ReceiverArg &receiver);
void SwkbdSetSelectFrom(int from);
void SwkbdSetUserControllerEventObj(nn::swkbd::IControllerEventObj *userControllerEventObj);
void SwkbdSetUserSoundObj(nn::swkbd::ISoundObj *userSoundObj);
void SwkbdSetVersion(int version);

}

#endif // ifdef __cplusplus

/** @} */
