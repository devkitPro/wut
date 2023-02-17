#include <nn/erreula.h>
#include <erreula/rpl_interface.h>

#include <coreinit/debug.h>
#include <coreinit/dynload.h>
#include <coreinit/memexpheap.h>

namespace nn
{
namespace erreula
{

static const uint32_t kWorkMemorySize = 0x1F00000;
static const uint32_t kRplAcquireBufferSize = 0xC80000;

static MEMHeapHandle sHeapHandle = NULL;
static OSDynLoad_Module sModuleHandle = NULL;

static void *sAppearError = NULL;
static void *sAppearHomeNixSign = NULL;
static void *sCalc = NULL;
static void *sChangeLang = NULL;
static void *sCreate = NULL;
static void *sDestroy = NULL;
static void *sDisappearError = NULL;
static void *sDisappearHomeNixSign = NULL;
static void *sDrawDRC = NULL;
static void *sDrawTV = NULL;
static void *sGetResultCode = NULL;
static void *sGetResultType = NULL;
static void *sGetSelectButtonNumError = NULL;
static void *sGetStateErrorViewer = NULL;
static void *sIsAppearHomeNixSign = NULL;
static void *sIsDecideSelectButtonError = NULL;
static void *sIsDecideSelectLeftButtonError = NULL;
static void *sIsDecideSelectRightButtonError = NULL;
static void *sIsSelectCursorActive = NULL;
static void *sJump = NULL;
static void *sPlayAppearSE = NULL;
static void *sSetControllerRemo = NULL;
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
Create(void *workMemory,
       RegionType region,
       LangType language,
       FSClient *fsClient)
{

   return reinterpret_cast<decltype(&Rpl::ErrEulaCreate)>(sCreate)(
      workMemory, region, language, fsClient);
}

static void
SetVersion(int version)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaSetVersion)>(sSetVersion)(
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
      OSReport("ERREULA: Create failed. CreateArg.workMemory is NULL.");
      return false;
   }

   if (!args.fsClient) {
      OSReport("ERREULA: Create failed. CreateArg.fsClient is NULL.");
      return false;
   }

   sHeapHandle = MEMCreateExpHeapEx(args.workMemory, kWorkMemorySize, 0);
   OSDynLoad_GetAllocator(&prevDynLoadAlloc, &prevDynLoadFree);
   OSDynLoad_SetAllocator(allocForDynLoad, freeForDynLoad);

   if (OSDynLoad_Error error = OSDynLoad_Acquire("erreula.rpl", &sModuleHandle)) {
      OSReport("ERREULA: Create failed. OSDynLoad_Acquire() return error(%d).\n",
               error);
      result = false;
      goto out;
   }

   dynloadAcquireUseSize = kWorkMemorySize -
                           MEMGetAllocatableSizeForExpHeapEx(sHeapHandle, 4);
   OSReport("ERREULA: OSDynLoad_Acquire() use [%d/%d]\n",
            dynloadAcquireUseSize, kRplAcquireBufferSize);

   if (dynloadAcquireUseSize > kRplAcquireBufferSize) {
      OSReport("ERREULA: Create failed. dynload_acquire_use_size > kRplAcquireBufferSize.");
      result = false;
      goto out;
   }

   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaAppearError__3RplFRCQ3_2nn7erreula9AppearArg", &sAppearError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaCalc__3RplFRCQ3_2nn7erreula14ControllerInfo", &sCalc);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaCreate__3RplFPUcQ3_2nn7erreula10RegionTypeQ3_2nn7erreula8LangTypeP8FSClient", &sCreate);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaDestroy__3RplFv", &sDestroy);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaDisappearError__3RplFv", &sDisappearError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaDrawDRC__3RplFv", &sDrawDRC);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaDrawTV__3RplFv", &sDrawTV);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaGetStateErrorViewer__3RplFv", &sGetStateErrorViewer);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaIsDecideSelectButtonError__3RplFv", &sIsDecideSelectButtonError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaIsDecideSelectLeftButtonError__3RplFv", &sIsDecideSelectLeftButtonError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaIsDecideSelectRightButtonError__3RplFv", &sIsDecideSelectRightButtonError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaSetControllerRemo__3RplFQ3_2nn7erreula14ControllerType", &sSetControllerRemo);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaAppearHomeNixSign__3RplFRCQ3_2nn7erreula14HomeNixSignArg", &sAppearHomeNixSign);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaIsAppearHomeNixSign__3RplFv", &sIsAppearHomeNixSign);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaDisappearHomeNixSign__3RplFv", &sDisappearHomeNixSign);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaChangeLang__3RplFQ3_2nn7erreula8LangType", &sChangeLang);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaIsSelectCursorActive__3RplFv", &sIsSelectCursorActive);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaGetResultType__3RplFv", &sGetResultType);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaGetResultCode__3RplFv", &sGetResultCode);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaGetSelectButtonNumError__3RplFv", &sGetSelectButtonNumError);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaSetVersion__3RplFi", &sSetVersion);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaPlayAppearSE__3RplFb", &sPlayAppearSE);
   OSDynLoad_FindExport(sModuleHandle, OS_DYNLOAD_EXPORT_FUNC, "ErrEulaJump__3RplFPCcUi", &sJump);

   workMemory = MEMAllocFromExpHeapEx(sHeapHandle,
                                      kWorkMemorySize - kRplAcquireBufferSize,
                                      4);
   if (!workMemory) {
      OSReport("ERREULA: Create failed. framework_buffer == NULL.");
      result = false;
      goto out;
   } else {
      SetVersion(3);
      Create(workMemory, args.region, args.language, args.fsClient);
      result = true;
   }

out:
   if (!result) {
      if (sModuleHandle) {
         OSDynLoad_Release(sModuleHandle);
         sModuleHandle = NULL;
      }

      if (sHeapHandle) {
         MEMDestroyExpHeap(sHeapHandle);
         sHeapHandle = NULL;
      }
   }

   OSDynLoad_SetAllocator(prevDynLoadAlloc, prevDynLoadFree);
   return result;
}

void
AppearErrorViewer(const AppearArg &arg)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaAppearError)>
      (sAppearError)
      (arg);
}

void
AppearHomeNixSign(const HomeNixSignArg &arg)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaAppearHomeNixSign)>
      (sAppearHomeNixSign)
      (arg);
}

void
Calc(const ControllerInfo &controllerInfo)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaCalc)>
      (sCalc)
      (controllerInfo);
}

void
ChangeLangError(LangType language)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaChangeLang)>
      (sChangeLang)
      (language);
}

void
Destroy()
{
   reinterpret_cast<decltype(&Rpl::ErrEulaDestroy)>(sDestroy)();

   if (sModuleHandle) {
      OSDynLoad_Release(sModuleHandle);
      sModuleHandle = NULL;
   }

   if (sHeapHandle) {
      MEMDestroyExpHeap(sHeapHandle);
      sHeapHandle = NULL;
   }
}

void
DisappearErrorViewer()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaDisappearError)>
      (sDisappearError)
      ();
}

void
DisappearHomeNixSign()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaDisappearHomeNixSign)>
      (sDisappearHomeNixSign)
      ();
}

void
DrawDRC()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaDrawDRC)>
      (sDrawDRC)
      ();
}

void
DrawTV()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaDrawTV)>
      (sDrawTV)
      ();
}

int32_t
GetResultCode()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaGetResultCode)>
      (sGetResultCode)
      ();
}

ResultType
GetResultType()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaGetResultType)>
      (sGetResultType)
      ();
}

int32_t
GetSelectButtonNumError()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaGetSelectButtonNumError)>
      (sGetSelectButtonNumError)
      ();
}

State
GetStateErrorViewer()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaGetStateErrorViewer)>
      (sGetStateErrorViewer)
      ();
}

uint32_t
GetWorkMemorySize()
{
   return kWorkMemorySize;
}

bool
IsAppearHomeNixSign()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaIsAppearHomeNixSign)>
      (sIsAppearHomeNixSign)
      ();
}

bool
IsDecideSelectButtonError()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaIsDecideSelectButtonError)>
      (sIsDecideSelectButtonError)
      ();
}

bool
IsDecideSelectLeftButtonError()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaIsDecideSelectLeftButtonError)>
      (sIsDecideSelectLeftButtonError)
      ();
}

bool
IsDecideSelectRightButtonError()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaIsDecideSelectRightButtonError)>
      (sIsDecideSelectRightButtonError)
      ();
}

bool
IsSelectCursorActive()
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaIsSelectCursorActive)>
      (sIsSelectCursorActive)
      ();
}

bool
Jump(const char *buffer, uint32_t bufferSize)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaJump)>
      (sJump)
      (buffer, bufferSize);
}

void
PlayAppearSE(bool playAppearSoundEffect)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaPlayAppearSE)>
      (sPlayAppearSE)
      (playAppearSoundEffect);
}

void
SetControllerRemo(ControllerType controller)
{
   return reinterpret_cast<decltype(&Rpl::ErrEulaSetControllerRemo)>
      (sSetControllerRemo)
      (controller);
}

} // namespace erreula
} // namespace nn
