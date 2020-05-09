/*
 * Copyright (C) 2015-2020 exjam <james.benton2@gmail.com>
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
   FSAddClient(fsClient, 0);

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

      WHBGfxBeginRender();

      WHBGfxBeginRenderTV();
      WHBGfxClearColor(0.0f, 0.0f, 1.0f, 1.0f);
      nn::swkbd::DrawTV();
      WHBGfxFinishRenderTV();

      WHBGfxBeginRenderDRC();
      WHBGfxClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      nn::swkbd::DrawDRC();
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

   FSDelClient(fsClient, 0);
   MEMFreeToDefaultHeap(fsClient);

   FSShutdown();
   VPADShutdown();

   WHBGfxShutdown();
   WHBProcShutdown();
   WHBLogUdpDeinit();
   return 0;
}
