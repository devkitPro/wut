#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <gx2/surface.h>
#include <nn/erreula.h>
#include <sndcore2/core.h>
#include <sysapp/launch.h>
#include <vpad/input.h>

#include <whb/gfx.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/proc.h>

int
main(int argc, char **argv)
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
   createArg.region     = nn::erreula::RegionType::Europe;
   createArg.language   = nn::erreula::LangType::English;
   createArg.workMemory = MEMAllocFromDefaultHeap(nn::erreula::GetWorkMemorySize());
   createArg.fsClient   = fsClient;
   if (!nn::erreula::Create(createArg)) {
      WHBLogPrintf("nn::erreula::Create failed");
      WHBProcShutdown();
      return -1;
   }

   // Play a sound effect that will play when erreula appears on screen
   nn::erreula::PlayAppearSE(true);

   // Show the error viewer
   nn::erreula::AppearArg appearArg;
   appearArg.errorArg.errorType      = nn::erreula::ErrorType::Message2Button;
   appearArg.errorArg.renderTarget   = nn::erreula::RenderTarget::Both;
   appearArg.errorArg.controllerType = nn::erreula::ControllerType::DrcGamepad;
   appearArg.errorArg.errorMessage   = u"This is my error message";
   appearArg.errorArg.button1Label   = u"Left Button";
   appearArg.errorArg.button2Label   = u"Right Button";
   appearArg.errorArg.errorTitle     = u"Title";
   nn::erreula::AppearErrorViewer(appearArg);

   // Get WHBGfx's colour buffers for proper erreula rendering
   GX2ColorBuffer *cbTV = WHBGfxGetTVColourBuffer();
   GX2ColorBuffer *cbDRC = WHBGfxGetDRCColourBuffer();     

   WHBLogPrintf("Begin rendering...");
   while (WHBProcIsRunning()) {
      // Read vpad for erreula::Calc
      VPADStatus vpadStatus;
      VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);
      VPADGetTPCalibratedPoint(VPAD_CHAN_0, &vpadStatus.tpNormal, &vpadStatus.tpNormal);

      // Update erreula
      nn::erreula::ControllerInfo controllerInfo;
      controllerInfo.vpad    = &vpadStatus;
      controllerInfo.kpad[0] = nullptr;
      controllerInfo.kpad[1] = nullptr;
      controllerInfo.kpad[2] = nullptr;
      controllerInfo.kpad[3] = nullptr;
      nn::erreula::Calc(controllerInfo);

      if (nn::erreula::IsDecideSelectButtonError()) {
         nn::erreula::DisappearErrorViewer();
         SYSLaunchMenu();
      }

      WHBGfxBeginRender();

      WHBGfxBeginRenderTV();
      WHBGfxClearColor(0.0f, 0.0f, 1.0f, 1.0f);
      // Set our colour buffer's surface format to SRGB for correct rendering of erreula
      GX2SurfaceFormat fTV = cbTV->surface.format;
      cbTV->surface.format = GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8;
      GX2InitColorBufferRegs(cbTV);
      GX2SetColorBuffer(cbTV, GX2_RENDER_TARGET_0);
      
      nn::erreula::DrawTV();

      // Set our colour buffer's surface format back to what it was before.
      cbTV->surface.format = fTV;
      GX2InitColorBufferRegs(cbTV);
      GX2SetColorBuffer(cbTV, GX2_RENDER_TARGET_0);
      WHBGfxFinishRenderTV();

      WHBGfxBeginRenderDRC();
      WHBGfxClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      GX2SurfaceFormat fDRC = cbDRC->surface.format;
      cbDRC->surface.format = GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8;
      GX2InitColorBufferRegs(cbDRC);
      GX2SetColorBuffer(cbDRC, GX2_RENDER_TARGET_0);

      nn::erreula::DrawDRC();

      cbDRC->surface.format = fDRC;
      GX2InitColorBufferRegs(cbDRC);
      GX2SetColorBuffer(cbDRC, GX2_RENDER_TARGET_0);
      WHBGfxFinishRenderDRC();

      WHBGfxFinishRender();
   }

   nn::erreula::ResultType resultType = nn::erreula::GetResultType();
   int32_t resultCode                 = nn::erreula::GetResultCode();
   WHBLogPrintf("Result type: %d, result code: %d",
                static_cast<int>(resultType), resultCode);

   // Cleanup
   WHBLogPrintf("Exiting...");
   nn::erreula::Destroy();
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
