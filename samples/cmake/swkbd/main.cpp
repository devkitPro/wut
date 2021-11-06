#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <nn/swkbd.h>
#include <vpad/input.h>

#include <whb/proc.h>
#include <whb/gfx.h>
#include <whb/log.h>
#include <whb/log_udp.h>

int main(int argc, char **argv)
{
   WHBLogUdpInit();
   WHBProcInit();
   WHBGfxInit();
   FSInit();
   VPADInit();

   // Create FSClient for swkbd
   FSClient *fsClient = (FSClient *)MEMAllocFromDefaultHeap(sizeof(FSClient));
   FSAddClient(fsClient, FS_ERROR_FLAG_NONE);

   // Create swkbd
   nn::swkbd::CreateArg createArg;
   createArg.regionType = nn::swkbd::RegionType::Europe;
   createArg.workMemory = MEMAllocFromDefaultHeap(nn::swkbd::GetWorkMemorySize(0));
   createArg.fsClient = fsClient;
   if (!nn::swkbd::Create(createArg)) {
      WHBLogPrintf("nn::swkbd::Create failed");
      WHBProcShutdown();
      return -1;
   }

   // Show the keyboard
   nn::swkbd::AppearArg appearArg;
   appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
   if (!nn::swkbd::AppearInputForm(appearArg)) {
      WHBLogPrintf("nn::swkbd::AppearInputForm failed");
      WHBProcShutdown();
      return -1;
   }

   WHBLogPrintf("Begin rendering...");
   while (WHBProcIsRunning()) {
      // Read vpad for swkbd::Calc
      VPADStatus vpadStatus;
      VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);
      VPADGetTPCalibratedPoint(VPAD_CHAN_0, &vpadStatus.tpNormal, &vpadStatus.tpNormal);

      // Update keyboard
      nn::swkbd::ControllerInfo controllerInfo;
      controllerInfo.vpad = &vpadStatus;
      controllerInfo.kpad[0] = nullptr;
      controllerInfo.kpad[1] = nullptr;
      controllerInfo.kpad[2] = nullptr;
      controllerInfo.kpad[3] = nullptr;
      nn::swkbd::Calc(controllerInfo);

      if (nn::swkbd::IsNeedCalcSubThreadFont()) {
         nn::swkbd::CalcSubThreadFont();
      }

      if (nn::swkbd::IsNeedCalcSubThreadPredict()) {
         nn::swkbd::CalcSubThreadPredict();
      }

      if (nn::swkbd::IsDecideOkButton(nullptr)) {
         nn::swkbd::DisappearInputForm();
         break;
      }

      WHBGfxMakeTVContextCurrent();
      {
         WHBGfxClearColorDepthStencil(0.0f, 0.0f, 1.0f, 1.0f);
         nn::swkbd::DrawTV();
      }

      WHBGfxMakeDRCContextCurrent();
      {
         WHBGfxClearColorDepthStencil(1.0f, 0.0f, 1.0f, 1.0f);
         nn::swkbd::DrawDRC();
      }

      WHBGfxCopyTVColorBufferToTVScanBuffer();
      WHBGfxCopyDRCColorBufferToDRCScanBuffer();
      WHBGfxSwapScanBuffers();
   }

   const char16_t *str = nn::swkbd::GetInputFormString();

   if (!str) {
      WHBLogPrint("nn::swkbd::GetInputFormString returned NULL");
   } else {
      // Quick hack to get from a char16_t str to char for our log function
      char logStr[128];
      logStr[0] = 0;

      for (int i = 0; i < 128; ++i) {
         if (!str[i]) {
            logStr[i] = 0;
            break;
         }

         if (str[i] > 0x7F) {
            logStr[i] = '?';
         } else {
            logStr[i] = str[i];
         }
      }

      WHBLogPrintf("Input string: %s", logStr);
   }

   // Cleanup
   WHBLogPrintf("Exiting...");
   nn::swkbd::Destroy();
   MEMFreeToDefaultHeap(createArg.workMemory);

   FSDelClient(fsClient, FS_ERROR_FLAG_NONE);
   MEMFreeToDefaultHeap(fsClient);

   FSShutdown();
   VPADShutdown();

   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}
