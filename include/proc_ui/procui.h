#pragma once
#include <wut.h>

/**
 * \defgroup proc_ui_procui ProcUI
 * \ingroup proc_ui
 *
 * The ProcUI group of functions provide an interface to manage transitions
 * between the different states of an application.
 *
 * After calling ProcUIInit() or ProcUIInitEx(), an application may call
 * ProcUIProcessMessages() to process and update its state. These states may
 * include:
 * - #PROCUI_STATUS_IN_FOREGROUND - The default state of an application. All
 *   system resources and hardware is available, and the application runs 
 *   without any serious restrictions.
 * - #PROCUI_STATUS_IN_BACKGROUND - When the user instructs the OS to switch
 *   to a secondary application (HOME menu overlay, Internet Browser, etc.) the
 *   application enters this background state. Background applications are
 *   heavily restricted - they get a small amount of CPU time on core 2 (all
 *   other threads are suspended), access to filesystems, and some network IO.
 *   They have no access to graphics, inputs or user interaction of any kind.
 * - #PROCUI_STATUS_RELEASE_FOREGROUND - The user has requested a foreground
 *   switch. The current application must release all foreground-only resources,
 *   calling ProcUIDrawDoneRelease() when it's ready to go into the background.
 * - #PROCUI_STATUS_EXITING - The application must release all resources, call
 *   ProcUIShutdown(), and exit.
 *
 * An application can determine its state by either examining
 * ProcUIProcessMessages()'s return value, or using callbacks via
 * ProcUIRegisterCallback().
 *
 * \if false
 * todo: flesh out exactly what is/isn't allowed in background
 * \endif
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
   //! Application acquires the foreground
   PROCUI_CALLBACK_ACQUIRE,
   //! Application must release the foreground
   PROCUI_CALLBACK_RELEASE,
   //! Application must exit
   PROCUI_CALLBACK_EXIT,
   //! Application may start using networking
   PROCUI_CALLBACK_NET_IO_START,
   //! Application must stop using networking
   PROCUI_CALLBACK_NET_IO_STOP,
   //! The user attempted to press the HOME button but was denied
   PROCUI_CALLBACK_HOME_BUTTON_DENIED,
} ProcUICallbackType;

typedef enum ProcUIStatus
{
   //! The application is in the foreground. All resources may be used.
   PROCUI_STATUS_IN_FOREGROUND,
   //! The application is in the background, only limited resources are usable.
   PROCUI_STATUS_IN_BACKGROUND,
   //! The application must release the foregound - see ProcUIDrawDoneRelease()
   PROCUI_STATUS_RELEASE_FOREGROUND,
   //! The application must release all resources (including ProcUI) and quit
   PROCUI_STATUS_EXITING,
} ProcUIStatus;

uint32_t
ProcUICalcMemorySize(uint32_t unk);

/**
 * Unregister all ProcUI callbacks.
 *
 * \sa
 * - ProcUIRegisterCallback()
 *
 * \if false
 * Would a currently executing async operation keep or lose the callbacks?
 * does this block?
 * \endif
 */
void
ProcUIClearCallbacks();

/**
 * Signifies to ProcUI that the current application has released all foreground
 * resources, drawn its last frame, and is ready to be moved into the
 * background. Should only be called when the application is in the 
 * #PROCUI_STATUS_RELEASE_FOREGROUND state.
 *
 * \note
 * After calling this function, the context will switch next time
 * ProcUIProcessMessages() is called. All user threads on core 0 and 1 will
 * be suspended once this happens.
 *
 * \warning
 * Do not attempt to use foreground-only resources after calling this function
 * and its accompanying ProcUIProcessMessages().
 * You should wait until ProcUI indicates #PROCUI_STATUS_IN_FOREGROUND.
 *
 * \if false
 * how does SubProcessMessages fit in?
 * doxy: how do you link to the description of coreinit/thread? would like to
 * note that threads can't be suspended immediately
 * \endif
 */
void
ProcUIDrawDoneRelease();

/**
 * Determines whether the application is in the foreground.
 *
 * \returns
 * \c true if the application status is #PROCUI_STATUS_IN_FOREGROUND.
 *
 * \sa
 * - #PROCUI_STATUS_IN_FOREGROUND
 * - ProcUIRegisterCallback()
 */
BOOL
ProcUIInForeground();

/**
 * Determines whether the application is in shutdown and should quit.
 *
 * \returns
 * \c true if the application status is #PROCUI_STATUS_EXITING.
 *
 * \sa
 * - #PROCUI_STATUS_EXITING
 * - ProcUIRegisterCallback()
 */
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
 * - ProcUISetSaveCallback()
 * - ProcUIShutdown()
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
 * - ProcUISetSaveCallback()
 * - ProcUIShutdown()
 */
void
ProcUIInitEx(ProcUISaveCallbackEx saveCallback,
             void *arg);

/**
 * Determines whether the application is running.
 *
 * \returns
 * \c true if the application is running.
 *
 * \if false
 * running? what does that actually mean? any state except exiting?
 * \endif
 */
BOOL
ProcUIIsRunning();

/**
 * Main runloop for ProcUI. This function processes messages from the OS and
 * provides it an opportinity to take control (to open the HOME menu overlay,
 * for example). Returns the current state of the application.
 *
 * \param block
 * Determines whether the function should block before returning. If \c false,
 * the function returns immediately and all messages and callbacks are processed
 * asynchronously.
 *
 * \return
 * The current state of the program. See #ProcUIStatus. If block is \c false,
 * this value is undefined and should be ignored.
 *
 * \warning
 * ProcUI's non-blocking mode is not widely used and may have undocumented
 * behaviour. Be careful with callbacks and the return value.
 *
 * \note
 * This function should only be called from the main core. See OSIsMainCore()
 * and ProcUISubProcessMessages().
 *
 * \if false
 * Assuming the note about core behaviour is true, based on homebrew
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
 * \sa
 * - ProcUIRegisterCallbackCore()
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

/**
 * Register a callback for certain ProcUI events, executed on the given core.
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
 * \param core
 * The core ID to run the callback on.
 *
 * \sa
 * - ProcUIRegisterCallback()
 */
void
ProcUIRegisterCallbackCore(ProcUICallbackType type,
                           ProcUICallback callback,
                           void *param,
                           uint32_t priority,
                           uint32_t core);

/**
 * Sets the save callback. Unlike ProcUIInitEx(), this function can be called
 * while ProcUI is already running.
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
 * - ProcUIInitEx()
 */
void
ProcUISetSaveCallback(ProcUISaveCallbackEx saveCallback,
                      void *arg);

/**
 * Shut down the ProcUI library for the current application. This should be
 * called before the app exits.
 *
 * \note
 * Do not attempt to use any ProcUI library functions after calling this
 * function, except for ProcUIInit() or ProcUIInitEx().
 */
void
ProcUIShutdown();

/**
 * ProcUIProcessMessages(), but for secondary cores.
 *
 * \param block
 * Determines whether the function should block before returning. If \c false,
 * the function returns immediately and all messages and callbacks are processed
 * asynchronously.
 *
 * \returns
 * The current state of the program - see #ProcUIStatus. If block is \c false,
 * this value is undefined and should be ignored.
 *
 * \warning
 * ProcUI's non-blocking mode is not widely used and may have undocumented
 * behaviour. Be careful with callbacks and the return value.
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
