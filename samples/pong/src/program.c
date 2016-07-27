#include "program.h"

#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/internal.h>
#include <coreinit/screen.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>
#include <vpad/input.h>
#include "memory.h"

char log_buf[0x400];

bool isAppRunning = true;
bool initialized = false;

void screenInit()
{
	//Grab the buffer size for each screen (TV and gamepad)
	int buf0_size = OSScreenGetBufferSizeEx(0);
	int buf1_size = OSScreenGetBufferSizeEx(1);
	__os_snprintf(log_buf, 0x400, "Screen sizes %x, %x\n", buf0_size, buf1_size);
	OSReport(log_buf);
	
	//Set the buffer area.
	screenBuffer = MEM1_alloc(buf0_size + buf1_size, 0x40);
	__os_snprintf(log_buf, 0x400, "Allocated screen buffers at %x\n", screenBuffer);
	OSReport(log_buf);

    OSScreenSetBufferEx(0, screenBuffer);
    OSScreenSetBufferEx(1, (screenBuffer + buf0_size));
    OSReport("Set screen buffers\n");

    OSScreenEnableEx(0, 1);
    OSScreenEnableEx(1, 1);
    
    //Clear both framebuffers.
	for (int ii = 0; ii < 2; ii++)
	{
		fillScreen(0,0,0,0);
		flipBuffers();
	}
}

void screenDeinit()
{
    for(int ii = 0; ii < 2; ii++)
	{
		fillScreen(0,0,0,0);
		flipBuffers();
	}
    
    MEM1_free(screenBuffer);
}

void SaveCallback()
{
   OSSavesDone_ReadyToRelease(); // Required
}

bool AppRunning()
{
   if(!OSIsMainCore())
   {
      ProcUISubProcessMessages(true);
   }
   else
   {
      ProcUIStatus status = ProcUIProcessMessages(true);
    
      if(status == PROCUI_STATUS_EXITING)
      {
          // Being closed, deinit things and prepare to exit
          isAppRunning = false;
          
          if(initialized)
          {
              initialized = false;
              screenDeinit();
              memoryRelease();
          }
          
          ProcUIShutdown();
      }
      else if(status == PROCUI_STATUS_RELEASE_FOREGROUND)
      {
          // Free up MEM1 to next foreground app, etc.
          initialized = false;
          
          screenDeinit();
          memoryRelease();
          ProcUIDrawDoneRelease();
      }
      else if(status == PROCUI_STATUS_IN_FOREGROUND)
      {
         // Reallocate MEM1, reinit screen, etc.
         if(!initialized)
         {
            initialized = true;
            
            memoryInitialize();
            screenInit();
         }
      }
   }

   return isAppRunning;
}

int main(int argc, char **argv)
{	
    OSScreenInit();
    OSReport("Screen initted\n");
    
    ProcUIInit(&SaveCallback);

	/****************************>             Globals             <****************************/
	struct pongGlobals myPongGlobals;
	//Flag for restarting the entire game.
	myPongGlobals.restart = 1;
	//scale of game
	myPongGlobals.scale=1;
	//Default locations for paddles and ball location and movement dx/dy
	myPongGlobals.p1X_default=40*myPongGlobals.scale;
	myPongGlobals.p2X_default=340*myPongGlobals.scale;
	myPongGlobals.ballX_default=200*myPongGlobals.scale;
	myPongGlobals.p1Y_default=150*myPongGlobals.scale;
	myPongGlobals.p2Y_default=150*myPongGlobals.scale;
	myPongGlobals.ballY_default=120*myPongGlobals.scale;
	//Sizes of objects
	myPongGlobals.p1X_size=20*myPongGlobals.scale;
	myPongGlobals.p1Y_size=60*myPongGlobals.scale;
	myPongGlobals.ballX_size=8*myPongGlobals.scale;
	myPongGlobals.ballY_size=8*myPongGlobals.scale;
	myPongGlobals.p2X_size=20*myPongGlobals.scale;
	myPongGlobals.p2Y_size=60*myPongGlobals.scale;
	//Boundry of play area (screen)
	myPongGlobals.xMinBoundry=0*myPongGlobals.scale;
	myPongGlobals.xMaxBoundry=400*myPongGlobals.scale;
	myPongGlobals.yMinBoundry=0*myPongGlobals.scale;
	myPongGlobals.yMaxBoundry=240*myPongGlobals.scale;
	
	myPongGlobals.winX=11*2*myPongGlobals.scale;
	myPongGlobals.winY=5*2*myPongGlobals.scale;
	myPongGlobals.score1X=13*2*myPongGlobals.scale;
	myPongGlobals.score2X=15*2*myPongGlobals.scale;
	myPongGlobals.score1Y=0*myPongGlobals.scale;
	myPongGlobals.score2Y=0*myPongGlobals.scale;
	//Game engine globals
	myPongGlobals.direction = 1;
	myPongGlobals.button = 0;
	myPongGlobals.paddleColorR=0xFF;
	myPongGlobals.paddleColorG=0x00;
	myPongGlobals.paddleColorB=0x00;
	myPongGlobals.ballColorR=0x00;
	myPongGlobals.ballColorG=0xFF;
	myPongGlobals.ballColorB=0x00;
	myPongGlobals.ballTrailColorR=0x00;
	myPongGlobals.ballTrailColorG=0x00;
	myPongGlobals.ballTrailColorB=0xFF;
	myPongGlobals.backgroundColorR=0x00;
	myPongGlobals.backgroundColorG=0x00;
	myPongGlobals.backgroundColorB=0x00;
	myPongGlobals.count = 0;
	//Keep track of score
	myPongGlobals.score1 = 0;
	myPongGlobals.score2 = 0;
	myPongGlobals.scoreWin = 9;
	//Game engine globals
	myPongGlobals.direction = 1;
	myPongGlobals.button = 0;
	myPongGlobals.paddleColorR=0xFF;
	myPongGlobals.paddleColorG=0x00;
	myPongGlobals.paddleColorB=0x00;
	myPongGlobals.ballColorR=0x00;
	myPongGlobals.ballColorG=0xFF;
	myPongGlobals.ballColorB=0x00;
	myPongGlobals.ballTrailColorR=0x00;
	myPongGlobals.ballTrailColorG=0x00;
	myPongGlobals.ballTrailColorB=0xFF;
	myPongGlobals.backgroundColorR=0x00;
	myPongGlobals.backgroundColorG=0x00;
	myPongGlobals.backgroundColorB=0x00;
	myPongGlobals.count = 0;
	//Keep track of score
	myPongGlobals.score1 = 0;
	myPongGlobals.scoreWin = 9;
	//Used for collision
	myPongGlobals.flag = 0;

	//Flag to determine if p1 should be rendered along with p1's movement direction
	myPongGlobals.renderP1Flag = 0;
	//Flags for render states
	myPongGlobals.renderResetFlag = 0;
	myPongGlobals.renderBallFlag = 0;
	myPongGlobals.renderWinFlag = 0;
	myPongGlobals.renderScoreFlag = 0;
	OSReport("Globals initialized\n");
	
	/****************************>            VPAD Loop            <****************************/
	int error;
	VPADStatus vpad_data;
	while (AppRunning())
	{
	    if(!initialized) continue;
	    
		VPADRead(0, &vpad_data, 1, &error);
		//Get the status of the gamepad
		myPongGlobals.button = vpad_data.hold;
		//If the game has been restarted, reset the game (we do this one time in the beginning to set everything up)
		if (myPongGlobals.restart == 1)
		{
		    OSReport("Game reset\n");
			reset(&myPongGlobals);
			myPongGlobals.restart = 0;
		}		
		//Set old positions.
		updatePosition(&myPongGlobals);

		//Update location of player1 and 2 paddles
		p1Move(&myPongGlobals);
		p2Move(&myPongGlobals);

		//Update location of the ball
		moveBall(&myPongGlobals);
		//Check if their are any collisions between the ball and the paddles.
		checkCollision(&myPongGlobals);
		//Render the scene
		myPongGlobals.renderBallFlag = 1;
		render(&myPongGlobals);

		//Increment the counter (used for physicals calcuations)
		myPongGlobals.count+=1;
	}
	
	return 0;
}
