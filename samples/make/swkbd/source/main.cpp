#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <gx2/surface.h>
#include <nn/swkbd.h>
#include <vpad/input.h>
#include <sndcore2/core.h>
#include <sysapp/launch.h>

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
   AXInit();

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
   appearArg.inputFormArg.hintText = u"I'm a hint.";
   if (!nn::swkbd::AppearInputForm(appearArg)) {
      WHBLogPrintf("nn::swkbd::AppearInputForm failed");
      WHBProcShutdown();
      return -1;
   }

   // Grab our colour buffers for proper rendering
   GX2ColorBuffer *tvColourBuffer = WHBGfxGetTVColourBuffer();
   GX2ColorBuffer *drcColourBuffer = WHBGfxGetDRCColourBuffer();

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
         // Launch the Wii U Menu to quit
         SYSLaunchMenu();
      }

      WHBGfxBeginRender();

      WHBGfxBeginRenderTV();
      WHBGfxClearColor(0.0f, 0.0f, 1.0f, 1.0f);
      
      // Switch the format of the colour buffers to SRGB for proper rendering
      GX2SurfaceFormat fTV = tvColourBuffer->surface.format;
      tvColourBuffer->surface.format = GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8;
      GX2InitColorBufferRegs(tvColourBuffer);
      GX2SetColorBuffer(tvColourBuffer, GX2_RENDER_TARGET_0);

      nn::swkbd::DrawTV();

      // Switch the format of the colour buffers back to what they originally were
      tvColourBuffer->surface.format = fTV;
      GX2InitColorBufferRegs(tvColourBuffer);
      GX2SetColorBuffer(tvColourBuffer, GX2_RENDER_TARGET_0);
      
      WHBGfxFinishRenderTV();

      WHBGfxBeginRenderDRC();
      WHBGfxClearColor(1.0f, 0.0f, 1.0f, 1.0f);

      GX2SurfaceFormat fDRC = drcColourBuffer->surface.format;
      drcColourBuffer->surface.format = GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8;
      GX2InitColorBufferRegs(drcColourBuffer);
      GX2SetColorBuffer(drcColourBuffer, GX2_RENDER_TARGET_0);

      nn::swkbd::DrawDRC();

      drcColourBuffer->surface.format = fDRC;
      GX2InitColorBufferRegs(drcColourBuffer);
      GX2SetColorBuffer(drcColourBuffer, GX2_RENDER_TARGET_0);
      
      WHBGfxFinishRenderDRC();

      WHBGfxFinishRender();
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
   AXQuit();

   WHBGfxShutdown();
   WHBLogUdpDeinit();
   return 0;
}
