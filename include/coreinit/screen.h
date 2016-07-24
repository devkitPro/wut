#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_screen Screen
 * \ingroup coreinit
 * @{
 */
 
#ifdef __cplusplus
extern "C" {
#endif

void 
OSScreenInit();

unsigned int 
OSScreenGetBufferSizeEx(unsigned int bufferNum);

int 
OSScreenSetBufferEx(unsigned int bufferNum, void * addr);

int 
OSScreenClearBufferEx(unsigned int bufferNum, 
                      unsigned int temp);

int 
OSScreenFlipBuffersEx(unsigned int bufferNum);

int 
OSScreenPutFontEx(unsigned int bufferNum, 
                  unsigned int posX, 
                  unsigned int posY, 
                  const char * buffer);
                  
void 
OSScreenPutPixelEx(int bufferNum, 
                   uint32_t posX, 
                   uint32_t posY, 
                   uint32_t colour);

int 
OSScreenEnableEx(unsigned int bufferNum, 
                 int enable);

#ifdef __cplusplus
}
#endif

/** @} */
