#pragma once
#include <wut.h>

/**
 * \defgroup proc_ui_procui ProcUI
 * \ingroup proc_ui
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ProcUISaveCallback)(void);
typedef uint32_t (*ProcUISaveCallbackEx)(void *);
typedef uint32_t (*ProcUICallback)(void *);

typedef enum ProcUICallbackType
{
   PROCUI_CALLBACK_ACQUIRE,
   PROCUI_CALLBACK_RELEASE,
   PROCUI_CALLBACK_EXIT,
   PROCUI_CALLBACK_NET_IO_START,
   PROCUI_CALLBACK_NET_IO_STOP,
   PROCUI_CALLBACK_HOME_BUTTON_DENIED,
} ProcUICallbackType;

typedef enum ProcUIStatus
{
   PROCUI_STATUS_IN_FOREGROUND,
   PROCUI_STATUS_IN_BACKGROUND,
   PROCUI_STATUS_RELEASE_FOREGROUND,
   PROCUI_STATUS_EXITING,
} ProcUIStatus;

uint32_t
ProcUICalcMemorySize(uint32_t unk);

void
ProcUIClearCallbacks();

void
ProcUIDrawDoneRelease();

BOOL
ProcUIInForeground();

BOOL
ProcUIInShutdown();

void
ProcUIInit(ProcUISaveCallback saveCallback);

void
ProcUIInitEx(ProcUISaveCallbackEx saveCallback,
             void *arg);

BOOL
ProcUIIsRunning();

ProcUIStatus
ProcUIProcessMessages(BOOL block);

void
ProcUIRegisterCallback(ProcUICallbackType type,
                       ProcUICallback callback,
                       void *param,
                       uint32_t priority);

void
ProcUIRegisterCallbackCore(ProcUICallbackType type,
                           ProcUICallback callback,
                           void *param,
                           uint32_t priority,
                           uint32_t core);

void
ProcUISetSaveCallback(ProcUISaveCallbackEx saveCallback,
                      void *arg);

void
ProcUIShutdown();

ProcUIStatus
ProcUISubProcessMessages(BOOL block);

#ifdef __cplusplus
}
#endif

/** @} */
