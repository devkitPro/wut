#include <coreinit/debug.h>
#include <coreinit/dynload.h>
#include <coreinit/memexpheap.h>
#include <nn/swkbd.h>
#include <swkbd/rpl_interface.h>

namespace nn
{
namespace swkbd
{

static const uint32_t sRplAcquireBufferSize = 0x380000;

static MEMHeapHandle sHeapHandle = NULL;
static OSDynLoad_Module sModuleHandle = NULL;

static void *sAppearInputForm = NULL;
static void *sAppearKeyboard = NULL;
static void *sCalcSubThreadFont = NULL;
static void *sCalcSubThreadPredict = NULL;
static void *sCalc = NULL;
static void *sConfirmUnfixAll = NULL;
static void *sCreate = NULL;
static void *sDestroy = NULL;
static void *sDisappearInputForm = NULL;
static void *sDisappearKeyboard = NULL;
static void *sDrawDRC = NULL;
static void *sDrawTV = NULL;
static void *sGetDrawStringInfo = NULL;
static void *sGetInputFormString = NULL;
static void *sGetKeyboardCondition = NULL;
static void *sGetStateInputForm = NULL;
static void *sGetStateKeyboard = NULL;
static void *sInactivateSelectCursor = NULL;
static void *sInitLearnDic = NULL;
static void *sIsCoveredWithSubWindow = NULL;
static void *sIsDecideCancelButton = NULL;
static void *sIsDecideOkButton = NULL;
static void *sIsKeyboardTarget = NULL;
static void *sIsNeedCalcSubThreadFont = NULL;
static void *sIsNeedCalcSubThreadPredict = NULL;
static void *sIsSelectCursorActive = NULL;
static void *sMuteAllSound = NULL;
static void *sSetControllerRemo = NULL;
static void *sSetCursorPos = NULL;
static void *sSetEnableOkButton = NULL;
static void *sSetInputFormString = NULL;
static void *sSetReceiver = NULL;
static void *sSetSelectFrom = NULL;
static void *sSetUserControllerEventObj = NULL;
static void *sSetUserSoundObj = NULL;
static void *sSetVersion = NULL;

static OSDynLoad_Error
allocForDynLoad(int32_t size,
                int32_t align,
                void **outAddr)
{
   void *addr = MEMAllocFromExpHeapEx(sHeapHandle, size, align);
   if (!addr) {
      return OS_DYNLOAD_OUT_OF_MEMORY;
   }

   *outAddr = addr;
   return OS_DYNLOAD_OK;
}

static void
freeForDynLoad(void *addr)
{
   MEMFreeToExpHeap(sHeapHandle, addr);
}

static void
Create(void *buffer,
       nn::swkbd::RegionType regionType,
       uint32_t unk,
       FSClient *fsClient)
{

   return reinterpret_cast<decltype(&Rpl::SwkbdCreate)>(sCreate)(
      buffer, regionType, unk, fsClient);
}

static void
SetVersion(int version)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetVersion)>(sSetVersion)(
      version);
}

bool
Create(const CreateArg &args)
{
   OSDynLoadAllocFn prevDynLoadAlloc = NULL;
   OSDynLoadFreeFn prevDynLoadFree = NULL;
   uint32_t dynloadAcquireUseSize = 0;
   void *workMemory = NULL;
   bool result = true;

   if (!args.workMemory) {
      OSReport("SWKBD: Create failed. CreateArg.workMemory is NULL.");
      return false;
   }

   if (!args.fsClient) {
      OSReport("SWKBD: Create failed. CreateArg.fsClient is NULL.");
      return false;
   }

   // Create work memory heap
   sHeapHandle = MEMCreateExpHeapEx(args.workMemory,
                                    GetWorkMemorySize(args.unk_0x08),
                                    0);

   // Save the old DynLoad allocator functions
   OSDynLoad_GetAllocator(&prevDynLoadAlloc, &prevDynLoadFree);

   // Set new DynLoad allocator functions
   OSDynLoad_SetAllocator(allocForDynLoad, freeForDynLoad);

   if (OSDynLoad_Error error = OSDynLoad_Acquire("swkbd.rpl", &sModuleHandle)) {
      OSReport("SWKBD: Create failed. OSDynLoad_Acquire() return error(%d).\n",
               error);
      result = false;
      goto out;
   }

   dynloadAcquireUseSize = GetWorkMemorySize(args.unk_0x08) -
                           MEMGetAllocatableSizeForExpHeapEx(sHeapHandle, 4);
   OSReport("SWKBD: OSDynLoad_Acquire() use [%d/%d]\n",
            dynloadAcquireUseSize, sRplAcquireBufferSize);

   if (dynloadAcquireUseSize > sRplAcquireBufferSize) {
      OSReport("SWKBD: Create failed. dynload_acquire_use_size > sRplAcquireBufferSize.");
      result = false;
      goto out;
   }

   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdAppearInputForm__3RplFRCQ3_2nn5swkbd9AppearArg", &sAppearInputForm);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdAppearKeyboard__3RplFRCQ3_2nn5swkbd11KeyboardArg", &sAppearKeyboard);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdCalcSubThreadFont__3RplFv", &sCalcSubThreadFont);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdCalcSubThreadPredict__3RplFv", &sCalcSubThreadPredict);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdCalc__3RplFRCQ3_2nn5swkbd14ControllerInfo", &sCalc);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdConfirmUnfixAll__3RplFv", &sConfirmUnfixAll);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdCreate__3RplFPUcQ3_2nn5swkbd10RegionTypeUiP8FSClient", &sCreate);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdDestroy__3RplFv", &sDestroy);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdDisappearInputForm__3RplFv", &sDisappearInputForm);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdDisappearKeyboard__3RplFv", &sDisappearKeyboard);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdDrawDRC__3RplFv", &sDrawDRC);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdDrawTV__3RplFv", &sDrawTV);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdGetDrawStringInfo__3RplFPQ3_2nn5swkbd14DrawStringInfo", &sGetDrawStringInfo);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdGetInputFormString__3RplFv", &sGetInputFormString);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdGetKeyboardCondition__3RplFPQ3_2nn5swkbd17KeyboardCondition", &sGetKeyboardCondition);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdGetStateInputForm__3RplFv", &sGetStateInputForm);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdGetStateKeyboard__3RplFv", &sGetStateKeyboard);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdInactivateSelectCursor__3RplFv", &sInactivateSelectCursor);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdInitLearnDic__3RplFPv", &sInitLearnDic);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsCoveredWithSubWindow__3RplFv", &sIsCoveredWithSubWindow);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsDecideCancelButton__3RplFPb", &sIsDecideCancelButton);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsDecideOkButton__3RplFPb", &sIsDecideOkButton);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsKeyboardTarget__3RplFPQ3_2nn5swkbd14IEventReceiver", &sIsKeyboardTarget);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsNeedCalcSubThreadFont__3RplFv", &sIsNeedCalcSubThreadFont);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsNeedCalcSubThreadPredict__3RplFv", &sIsNeedCalcSubThreadPredict);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdIsSelectCursorActive__3RplFv", &sIsSelectCursorActive);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdMuteAllSound__3RplFb", &sMuteAllSound);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetControllerRemo__3RplFQ3_2nn5swkbd14ControllerType", &sSetControllerRemo);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetCursorPos__3RplFi", &sSetCursorPos);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetEnableOkButton__3RplFb", &sSetEnableOkButton);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetInputFormString__3RplFPCw", &sSetInputFormString);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetReceiver__3RplFRCQ3_2nn5swkbd11ReceiverArg", &sSetReceiver);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetSelectFrom__3RplFi", &sSetSelectFrom);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetUserControllerEventObj__3RplFPQ3_2nn5swkbd19IControllerEventObj", &sSetUserControllerEventObj);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetUserSoundObj__3RplFPQ3_2nn5swkbd9ISoundObj", &sSetUserSoundObj);
   OSDynLoad_FindExport(sModuleHandle, FALSE, "SwkbdSetVersion__3RplFi", &sSetVersion);

   workMemory = MEMAllocFromExpHeapEx(sHeapHandle,
                                      GetWorkMemorySize(args.unk_0x08) - sRplAcquireBufferSize,
                                      4);
   if (!workMemory) {
      OSReport("SWKBD: Create failed. framework_buffer == NULL.");
      result = false;
      goto out;
   } else {
      SetVersion(3);
      Create(workMemory, args.regionType, args.unk_0x08, args.fsClient);
      result = true;
   }

out:
   if (!result) {
      MEMDestroyExpHeap(sHeapHandle);
   }

   OSDynLoad_SetAllocator(prevDynLoadAlloc, prevDynLoadFree);
   return result;
}

bool
AppearInputForm(const AppearArg& args)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdAppearInputForm)>
      (sAppearInputForm)
      (args);
}

bool
AppearKeyboard(const KeyboardArg& args)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdAppearKeyboard)>
      (sAppearKeyboard)
      (args);
}

void
CalcSubThreadFont()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdCalcSubThreadFont)>
      (sCalcSubThreadFont)
      ();
}

void
CalcSubThreadPredict()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdCalcSubThreadPredict)>
      (sCalcSubThreadPredict)
      ();
}

void
Calc(const ControllerInfo &controllerInfo)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdCalc)>
      (sCalc)
      (controllerInfo);
}

void
ConfirmUnfixAll()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdConfirmUnfixAll)>
      (sConfirmUnfixAll)
      ();
}

void
Destroy()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdDestroy)>
      (sDestroy)
      ();
}

bool
DisappearInputForm()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdDisappearInputForm)>
      (sDisappearInputForm)
      ();
}

bool
DisappearKeyboard()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdDisappearKeyboard)>
      (sDisappearKeyboard)
      ();
}

void
DrawDRC()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdDrawDRC)>
      (sDrawDRC)
      ();
}

void
DrawTV()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdDrawTV)>
      (sDrawTV)
      ();
}

void
GetDrawStringInfo(DrawStringInfo *drawStringInfo)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdGetDrawStringInfo)>
      (sGetDrawStringInfo)
      (drawStringInfo);
}

const char16_t *
GetInputFormString()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdGetInputFormString)>
      (sGetInputFormString)
      ();
}

void
GetKeyboardCondition(KeyboardCondition *keyboardCondition)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdGetKeyboardCondition)>
      (sGetKeyboardCondition)
      (keyboardCondition);
}

State
GetStateInputForm()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdGetStateInputForm)>
      (sGetStateInputForm)
      ();
}

State
GetStateKeyboard()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdGetStateKeyboard)>
      (sGetStateKeyboard)
      ();
}

uint32_t
GetWorkMemorySize(uint32_t unk)
{
   uint32_t size = 0;

   if (size & 1) {
      size = 0xA0000;
   }

   if (size & 2) {
      size += 0x120000;
   }

   return 0x1980000 - size;
}

void
InactivateSelectCursor()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdInactivateSelectCursor)>
      (sInactivateSelectCursor)
      ();
}

bool
InitLearnDic(void *dictionary)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdInitLearnDic)>
      (sInitLearnDic)
      (dictionary);
}

bool
IsCoveredWithSubWindow()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsCoveredWithSubWindow)>
      (sIsCoveredWithSubWindow)
      ();
}

bool
IsDecideCancelButton(bool *outIsSelected)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsDecideCancelButton)>
      (sIsDecideCancelButton)
      (outIsSelected);
}

bool
IsDecideOkButton(bool *outIsSelected)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsDecideOkButton)>
      (sIsDecideOkButton)
      (outIsSelected);
}

bool
IsKeyboardTarget(IEventReceiver *eventReceiver)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsKeyboardTarget)>
      (sIsKeyboardTarget)
      (eventReceiver);
}

bool
IsNeedCalcSubThreadFont()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsNeedCalcSubThreadFont)>
      (sIsNeedCalcSubThreadFont)
      ();
}

bool
IsNeedCalcSubThreadPredict()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsNeedCalcSubThreadPredict)>
      (sIsNeedCalcSubThreadPredict)
      ();
}

bool
IsSelectCursorActive()
{
   return reinterpret_cast<decltype(&Rpl::SwkbdIsSelectCursorActive)>
      (sIsSelectCursorActive)
      ();
}

void
MuteAllSound(bool muted)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdMuteAllSound)>
      (sMuteAllSound)
      (muted);
}

void
SetControllerRemo(ControllerType type)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetControllerRemo)>
      (sSetControllerRemo)
      (type);
}

void
SetCursorPos(int pos)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetCursorPos)>
      (sSetCursorPos)
      (pos);
}

void
SetEnableOkButton(bool enable)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetEnableOkButton)>
      (sSetEnableOkButton)
      (enable);
}

void
SetInputFormString(const char16_t *str)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetInputFormString)>
      (sSetInputFormString)
      (str);
}

void
SetReceiver(const ReceiverArg &receiver)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetReceiver)>
      (sSetReceiver)
      (receiver);
}

void
SetSelectFrom(int from)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetSelectFrom)>
      (sSetSelectFrom)
      (from);
}

void
SetUserControllerEventObj(IControllerEventObj *controllerEventObj)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetUserControllerEventObj)>
      (sSetUserControllerEventObj)
      (controllerEventObj);
}

void
SetUserSoundObj(ISoundObj *soundObj)
{
   return reinterpret_cast<decltype(&Rpl::SwkbdSetUserSoundObj)>
      (sSetUserSoundObj)
      (soundObj);
}

} // namespace swkbd
} // namespace nn
