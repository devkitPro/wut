#include "program.h"

#include <coreinit/debug.h>
#include <coreinit/internal.h>
#include <coreinit/screen.h>
#include <coreinit/exit.h>
#include <vpad/input.h>
#include <sysapp/switch.h>
#include <sysapp/launch.h>
#include "memory.h"

char log_buf[0x400];

int main(int argc, char **argv)
{	
	memoryInitialize();
	OSReport("Memory initialized\n");

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
	
	//Call the Screen initilzation function.
	OSScreenInit();
	OSReport("Screen initted\n");
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
	OSReport("Screen initialized\n");
	
	/****************************>            VPAD Loop            <****************************/
	int error;
	VPADStatus vpad_data;
	while (1)
	{
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

		//To exit the game
		if (myPongGlobals.button & VPAD_BUTTON_HOME)
		{
		    break;
		}
	}
	//WARNING: DO NOT CHANGE THIS. YOU MUST CLEAR THE FRAMEBUFFERS AND IMMEDIATELY CALL EXIT FROM THIS FUNCTION. RETURNING TO LOADER CAUSES FREEZE.
	for(int ii = 0; ii < 2; ii++)
	{
		fillScreen(0,0,0,0);
		flipBuffers();
	}
	
	//TODO: This doesn't work?
	OSReport("Exiting to menu\n");
	memoryRelease();
	SYSLaunchMenu();
	exit(0);
	
	return 0;
}
