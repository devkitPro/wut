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

/**
 * Called when the application needs to save.
 */
typedef void (*ProcUISaveCallback)(void);
/**
 * Called when the application needs to save.
 * void* argument is provided in ProcUIInitEx().
 */
typedef uint32_t (*ProcUISaveCallbackEx)(void *);
/**
 * Generic ProcUI callback.
 * void* argument is provided in ProcUIRegisterCallback().
 */
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

/**
 * Initialises the ProcUI library for use.
 *
 * \param saveCallback
 * A callback to be called when the application needs to save. The callback
 * cannot be NULL and it must call OSSavesDone_ReadyToRelease().
 *
 * \sa
 * - OSSavesDone_ReadyToRelease()
 */
void
ProcUIInit(ProcUISaveCallback saveCallback);

/**
 * Initialises the ProcUI library for use; using a save callback that takes
 * arguments.
 *
 * \param saveCallback
 * A callback to be called when the application needs to save. The callback
 * cannot be NULL and it must call OSSavesDone_ReadyToRelease().
 *
 * \param arg
 * An argument to pass into saveCallbackEx.
 *
 * \sa
 * - OSSavesDone_ReadyToRelease()
 */
void
ProcUIInitEx(ProcUISaveCallbackEx saveCallback,
             void *arg);

BOOL
ProcUIIsRunning();

/**
 * Main runloop for ProcUI. This function processes messages from the OS and
 * provides it an opportinity to take control (to open the HOME menu overlay,
 * for example). Returns the current state of the application.
 *
 * \param block
 * Determines whether the function should block before returning. If \c false,
 * the function returns immediately.
 *
 * \return
 * The current state of the program. See #ProcUIStatus.
 *
 * \warning
 * At this time, using ProcUI's non-blocking mode is not recommended as not much
 * is known about it. Instead, set block to \c true and examine the return
 * value.
 *
 * \note
 * This function should only be called from the main core. See OSIsMainCore().
 *
 * \if false
 * meta: what happens when block=false? is the return value trustworthy? how
 * does it interact with ProcUIRegisterCallback?
 * \endif
 */
ProcUIStatus
ProcUIProcessMessages(BOOL block);

/**
 * Register a callback for certain ProcUI events.
 *
 * \param type
 * The event to register a callback for. See #ProcUICallbackType.
 *
 * \param callback
 * Function pointer for the callback to call when the given event occurs.
 *
 * \param param
 * Argument for the callback. This will be passed in as the *second* argument.
 *
 * \param priority
 * The priority of the callback.
 *
 * \if false
 * higher-priority callbacks exec first? dunno
 * \endif
 */
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

/**
 * ProcUIProcessMessages(), but for secondary cores.
 *
 * \param block
 * Determines whether the function should block before returning. If \c false,
 * the function returns immediately.
 *
 * \warning
 * At this time, using ProcUI's non-blocking mode is not recommended as not much
 * is known about it. Instead, set block to \c true and examine the return
 * value.
 *
 * \if false
 * didn't know what this did, only seen it in the else{} from OSIsMainCore...
 * please research and correct!
 * \endif
 */
ProcUIStatus
ProcUISubProcessMessages(BOOL block);

#ifdef __cplusplus
}
#endif

/** @} */
