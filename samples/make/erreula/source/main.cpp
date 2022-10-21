#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <gx2/surface.h>
#include <nn/erreula.h>
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

   // Create FSClient for erreula
   FSClient *fsClient = (FSClient *)MEMAllocFromDefaultHeap(sizeof(FSClient));
   FSAddClient(fsClient, FS_ERROR_FLAG_NONE);

   // Create erreula
   nn::erreula::CreateArg createArg;
   createArg.region = nn::erreula::RegionType::Europe;
   createArg.language = nn::erreula::LangType::English;
   createArg.workMemory = MEMAllocFromDefaultHeap(nn::erreula::GetWorkMemorySize());
   createArg.fsClient = fsClient;
   if (!nn::erreula::Create(createArg)) {
      WHBLogPrintf("nn::erreula::Create failed");
      WHBProcShutdown();
      return -1;
   }

   // Show the error viewer
   nn::erreula::AppearArg appearArg;
   appearArg.errorArg.errorType = nn::erreula::ErrorType::Message2Button;
   appearArg.errorArg.renderTarget = nn::erreula::RenderTarget::Both;
   appearArg.errorArg.controllerType = nn::erreula::ControllerType::DrcGamepad;
   appearArg.errorArg.errorMessage = u"This is my error message";
   appearArg.errorArg.button1Label = u"Left Button";
   appearArg.errorArg.button2Label = u"Right Button";
   appearArg.errorArg.errorTitle = u"Title";
   
   nn::erreula::PlayAppearSE(true);
   
   nn::erreula::AppearErrorViewer(appearArg);

   // Grab our colour buffers for proper rendering
   GX2ColorBuffer *tvColourBuffer = WHBGfxGetTVColourBuffer();
   GX2ColorBuffer *drcColourBuffer = WHBGfxGetDRCColourBuffer();

   WHBLogPrintf("Begin rendering...");
   while (WHBProcIsRunning()) {
      // Read vpad for erreula::Calc
      VPADStatus vpadStatus;
      VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);
      VPADGetTPCalibratedPoint(VPAD_CHAN_0, &vpadStatus.tpNormal, &vpadStatus.tpNormal);

      // Update erreula
      nn::erreula::ControllerInfo controllerInfo;
      controllerInfo.vpad = &vpadStatus;
      controllerInfo.kpad[0] = nullptr;
      controllerInfo.kpad[1] = nullptr;
      controllerInfo.kpad[2] = nullptr;
      controllerInfo.kpad[3] = nullptr;
      nn::erreula::Calc(controllerInfo);

      if (nn::erreula::IsDecideSelectButtonError()) {
         nn::erreula::DisappearErrorViewer();
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

      nn::erreula::DrawTV();
      
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

      nn::erreula::DrawDRC();

      drcColourBuffer->surface.format = fDRC;
      GX2InitColorBufferRegs(drcColourBuffer);
      GX2SetColorBuffer(drcColourBuffer, GX2_RENDER_TARGET_0);

      WHBGfxFinishRenderDRC();

      WHBGfxFinishRender();
   }

   nn::erreula::ResultType resultType = nn::erreula::GetResultType();
   int32_t resultCode = nn::erreula::GetResultCode();
   WHBLogPrintf("Result type: %d, result code: %d",
                static_cast<int>(resultType), resultCode);

   // Cleanup
   WHBLogPrintf("Exiting...");
   nn::erreula::Destroy();
   MEMFreeToDefaultHeap(createArg.workMemory);

   FSDelClient(fsClient, FS_ERROR_FLAG_NONE);
   MEMFreeToDefaultHeap(fsClient);

   FSShutdown();
   AXQuit();

   WHBGfxShutdown();
   WHBLogUdpDeinit();
   return 0;
}
