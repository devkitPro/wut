#pragma once
#include <wut.h>
#include <coreinit/filesystem.h>
#include <nn/erreula.h>

/**
 * \defgroup erreula_rpl RPL Interface
 * \ingroup erreula
 * C++ linkage for erreula, see \link nn::erreula \endlink for general use.
 * @{
 */

#ifdef __cplusplus

struct FSClient;

namespace Rpl
{

void ErrEulaSetVersion(int version);
bool ErrEulaJump(const char *buffer, uint32_t bufferSize);
void ErrEulaPlayAppearSE(bool playAppearSoundEffect);
bool ErrEulaIsSelectCursorActive();
void ErrEulaChangeLang(nn::erreula::LangType language);
void ErrEulaDisappearHomeNixSign();
bool ErrEulaIsAppearHomeNixSign();
void ErrEulaAppearHomeNixSign(const nn::erreula::HomeNixSignArg &arg);
void ErrEulaSetControllerRemo(nn::erreula::ControllerType controller);
int32_t ErrEulaGetSelectButtonNumError();
int32_t ErrEulaGetResultCode();
nn::erreula::ResultType ErrEulaGetResultType();
nn::erreula::State ErrEulaGetStateErrorViewer();
bool ErrEulaIsDecideSelectRightButtonError();
bool ErrEulaIsDecideSelectLeftButtonError();
bool ErrEulaIsDecideSelectButtonError();
void ErrEulaDisappearError();
void ErrEulaAppearError(const nn::erreula::AppearArg &arg);
void ErrEulaCalc(const nn::erreula::ControllerInfo &controllerInfo);
void ErrEulaDrawDRC();
void ErrEulaDrawTV();
void ErrEulaDestroy();
void ErrEulaCreate(void *workMemory, nn::erreula::RegionType region,
                   nn::erreula::LangType language, FSClient *fsClient);

} // namespace Rpl

#endif // ifdef __cplusplus

/** @} */
