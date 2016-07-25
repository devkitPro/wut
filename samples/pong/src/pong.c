#include "pong.h"

#include <stdlib.h>
#include <coreinit/internal.h>

//Sets a collsion box.
int collisionBox(int box1x, int box1y, int width1, int height1, int box2x, int box2y, int width2, int height2){
	int corner1x = box1x + width1;
	int corner1y = box1y - height1;
	int corner2x = box2x + width2;
	int corner2y = box2y - height2;

	if (abs(box1x - corner2x)< 2 || abs(corner1x - box2x)< 2){
		if ((box1y >= corner2y && box1y <= box2y) || (corner1y >= corner2y && corner1y <= box2y))return 1;

	}

	if (abs(box1y - corner2y) < 2 || abs(corner1y - box2y) < 2){
		if ((box1x <= corner2x && box1x >= box2x) || (corner1x <= corner2x && corner1x >= box2x))return 2;
	}



	return 0;
}

//Updates player1 location
void p1Move(struct pongGlobals *myPongGlobals) {
	
	if ((myPongGlobals->button & VPAD_BUTTON_LEFT) && myPongGlobals->p1X > myPongGlobals->xMinBoundry) {

		//Trigger render flag
		myPongGlobals->renderP1Flag = 1;

		//Update player location
		myPongGlobals->p1X--;

	}
		
	if ((myPongGlobals->button & VPAD_BUTTON_RIGHT) && myPongGlobals->p1X+myPongGlobals->p1X_size < myPongGlobals->xMaxBoundry/4) {

		myPongGlobals->p1X++;
		//Trigger render flag
		myPongGlobals->renderP1Flag = 1;
	}
	
	if ((myPongGlobals->button & VPAD_BUTTON_UP) && myPongGlobals->p1Y-myPongGlobals->p1Y_size > myPongGlobals->yMinBoundry) {

		//Trigger render flag
		myPongGlobals->renderP1Flag = 1;

		//Update player location
		myPongGlobals->p1Y--;

	}
	if ((myPongGlobals->button & VPAD_BUTTON_DOWN) && myPongGlobals->p1Y < myPongGlobals->yMaxBoundry) {

		myPongGlobals->p1Y++;
		//Trigger render flag
		myPongGlobals->renderP1Flag = 1;
	}

};

//Updates player1 location
void p2Move(struct pongGlobals *myPongGlobals) {
	
	if ((myPongGlobals->button & VPAD_BUTTON_Y) && myPongGlobals->p2X > myPongGlobals->xMaxBoundry-myPongGlobals->xMaxBoundry/4) {

		//Trigger render flag
		myPongGlobals->renderP2Flag = 1;

		//Update player location
		myPongGlobals->p2X--;

	}
		
	if ((myPongGlobals->button & VPAD_BUTTON_A) && myPongGlobals->p2X+myPongGlobals->p2X_size < myPongGlobals->xMaxBoundry) {

		myPongGlobals->p2X++;
		//Trigger render flag
		myPongGlobals->renderP2Flag = 1;
	}
	
	if ((myPongGlobals->button & VPAD_BUTTON_X) && myPongGlobals->p2Y-myPongGlobals->p2Y_size > myPongGlobals->yMinBoundry) {

		//Trigger render flag
		myPongGlobals->renderP2Flag = 1;

		//Update player location
		myPongGlobals->p2Y--;

	}
	if ((myPongGlobals->button & VPAD_BUTTON_B) && myPongGlobals->p2Y < myPongGlobals->yMaxBoundry) {

		myPongGlobals->p2Y++;
		//Trigger render flag
		myPongGlobals->renderP2Flag = 1;
	}

};

//Physics for ball
void moveBall(struct pongGlobals *myPongGlobals) {
	int jump = 1;

	//Don't move at all
	if (myPongGlobals->flag)jump = 4;

	switch (myPongGlobals->direction) {
	case 1:
		myPongGlobals->ballX -= jump; //down left
		myPongGlobals->ballY += jump;
		break;
	case 3:
		myPongGlobals->ballX += jump; //down right
		myPongGlobals->ballY += jump;
		break;
	case 2:
		myPongGlobals->ballX += jump; //up right
		myPongGlobals->ballY -= jump;
		break;
	case 0:
		myPongGlobals->ballX -= jump; //up left
		myPongGlobals->ballY -= jump;
		break;
	default:
		break;

	}

	myPongGlobals->flag = 0;
};

//Checks for collsions
void checkCollision(struct pongGlobals *myPongGlobals) {
	int old;
	old = myPongGlobals->direction;

	if (myPongGlobals->ballY-myPongGlobals->ballY_size < myPongGlobals->yMinBoundry) {
		myPongGlobals->direction ^= 1;
	}
	
	/*
	if (myPongGlobals->ballX < myPongGlobals->xMinBoundry) {
		myPongGlobals->direction ^= 2;
	}

	if (myPongGlobals->ballX > myPongGlobals->xMaxBoundry) {
		myPongGlobals->direction ^= 2;
	}
	*/
	
	if (myPongGlobals->ballY > myPongGlobals->yMaxBoundry) {
		myPongGlobals->direction ^= 1;
	}
	
	//if (myPongGlobals->ballX < myPongGlobals->p1X+myPongGlobals->p1X_size+2) 
	{
		//Check p1 collision
		if (collisionBox(myPongGlobals->ballX, myPongGlobals->ballY, myPongGlobals->ballX_size, myPongGlobals->ballY_size, myPongGlobals->p1X, myPongGlobals->p1Y_old, myPongGlobals->p1X_size, myPongGlobals->p1Y_size) == 1) {
			myPongGlobals->direction ^= 2;
		}
		else if (collisionBox(myPongGlobals->ballX, myPongGlobals->ballY, myPongGlobals->ballX_size, myPongGlobals->ballY_size, myPongGlobals->p1X, myPongGlobals->p1Y, myPongGlobals->p1X_size, myPongGlobals->p1Y_size) == 2) 
		{
			myPongGlobals->direction ^= 1;
		
		}	
	}
	//if (myPongGlobals->ballX+myPongGlobals->ballX_size > myPongGlobals->p2X-2) 
	{
		//Check p2 collision
		if (collisionBox(myPongGlobals->ballX, myPongGlobals->ballY, myPongGlobals->ballX_size, myPongGlobals->ballY_size, myPongGlobals->p2X, myPongGlobals->p2Y, myPongGlobals->p2X_size, myPongGlobals->p2Y_size) == 1) {
			myPongGlobals->direction ^= 2;
		}
		else if (collisionBox(myPongGlobals->ballX, myPongGlobals->ballY, myPongGlobals->ballX_size, myPongGlobals->ballY_size, myPongGlobals->p2X, myPongGlobals->p2Y, myPongGlobals->p2X_size, myPongGlobals->p2Y_size) == 2) 
		{
			myPongGlobals->direction ^= 1;
		
		}	
	}
	if ((myPongGlobals->direction ^ old) != 0)myPongGlobals->flag = 1;
	
	if (myPongGlobals->ballX+myPongGlobals->ballX_size >= myPongGlobals->xMaxBoundry)
	{
		myPongGlobals->score1++;
		checkWin(myPongGlobals);
	}
	
	if (myPongGlobals->ballX <= myPongGlobals->xMinBoundry)
	{
		myPongGlobals->score2++;
		checkWin(myPongGlobals);
	}

};

//Checks to see if we have meet the requirements for entering the win state
void checkWin(struct pongGlobals *myPongGlobals) {
	if (myPongGlobals->score1 > myPongGlobals->scoreWin) {
		myPongGlobals->score1 = 0;
		myPongGlobals->renderWinFlag = 1;
		myPongGlobals->winningPlayer = 1;
	}
	
	if (myPongGlobals->score2 > myPongGlobals->scoreWin) {
		myPongGlobals->score2 = 0;
		myPongGlobals->renderWinFlag = 1;
		myPongGlobals->winningPlayer = 2;
	}
	reset(myPongGlobals);

};

//Render function for ball and updates player and balls new locations.
void renderBall(struct pongGlobals *myPongGlobals) {
	drawFillRect(myPongGlobals->ballX_old, myPongGlobals->ballY_old - myPongGlobals->ballY_size, myPongGlobals->ballX_old + myPongGlobals->ballX_size, myPongGlobals->ballY_old, myPongGlobals->ballTrailColorR,myPongGlobals->ballTrailColorG,myPongGlobals->ballTrailColorB, 0);
	drawFillRect(myPongGlobals->ballX, myPongGlobals->ballY - myPongGlobals->ballY_size, myPongGlobals->ballX + myPongGlobals->ballX_size, myPongGlobals->ballY, myPongGlobals->ballColorR, myPongGlobals->ballColorG, myPongGlobals->ballColorB, 0);
};

void render(struct pongGlobals *myPongGlobals)
{
	for (int ii = 0; ii < 2; ii++)
	{
		if (myPongGlobals->renderResetFlag)
		{
			renderReset(myPongGlobals);
		}
		if (myPongGlobals->renderScoreFlag)
		{
			renderScore(myPongGlobals);
		}

		if (myPongGlobals->renderBallFlag)
		{
			renderBall(myPongGlobals);
		}

		if (myPongGlobals->renderWinFlag)
		{
			renderWin(myPongGlobals);
		}

		if (myPongGlobals->renderP1Flag)
		{
			renderP1(myPongGlobals);
		}
		
		if (myPongGlobals->renderP2Flag)
		{
			renderP2(myPongGlobals);
		}
		flipBuffers();
	}

	resetRenderFlags(myPongGlobals);


}

void resetRenderFlags(struct pongGlobals *myPongGlobals)
{
	myPongGlobals->renderResetFlag = 0;
	myPongGlobals->renderBallFlag = 0;
	myPongGlobals->renderWinFlag = 0;
	myPongGlobals->renderP1Flag = 0;
	myPongGlobals->renderP2Flag = 0;
	myPongGlobals->renderScoreFlag=0;

}

void updatePosition(struct pongGlobals *myPongGlobals)
{
	myPongGlobals->p1X_old = myPongGlobals->p1X;
	myPongGlobals->p1Y_old = myPongGlobals->p1Y;
	myPongGlobals->p2X_old = myPongGlobals->p2X;
	myPongGlobals->p2Y_old = myPongGlobals->p2Y;
	myPongGlobals->ballX_old = myPongGlobals->ballX;
	myPongGlobals->ballY_old = myPongGlobals->ballY;
}

//Reset the game
void reset(struct pongGlobals *myPongGlobals) {
	//Set global variables to default state
	myPongGlobals->ballX = myPongGlobals->ballX_default;
	myPongGlobals->ballY = myPongGlobals->ballY_default;
	myPongGlobals->p1X = myPongGlobals->p1X_default;
	myPongGlobals->p1Y = myPongGlobals->p1Y_default;
	myPongGlobals->p1X_old = myPongGlobals->p1X;
	myPongGlobals->p1Y_old = myPongGlobals->p1Y;
	myPongGlobals->p2X = myPongGlobals->p2X_default;
	myPongGlobals->p2Y = myPongGlobals->p2Y_default;
	myPongGlobals->p2X_old = myPongGlobals->p2X;
	myPongGlobals->p2Y_old = myPongGlobals->p2Y;
	myPongGlobals->ballX_old = myPongGlobals->ballX;
	myPongGlobals->ballY_old = myPongGlobals->ballY;
	myPongGlobals->direction = (myPongGlobals->count & 3);
	myPongGlobals->button = 0;

	//Set flag to render reset screen;
	myPongGlobals->renderResetFlag = 1;
	myPongGlobals->renderScoreFlag = 1;

};

void renderScore(struct pongGlobals *myPongGlobals)
{
	char output1[255];
	__os_snprintf(output1, 255, "%d", myPongGlobals->score1);
	drawString(myPongGlobals->score1X, myPongGlobals->score1Y, output1);
	char output2[255];
	__os_snprintf(output2, 255, "%d", myPongGlobals->score2);
	drawString(myPongGlobals->score2X, myPongGlobals->score2Y, output2);
	
}

void renderReset(struct pongGlobals *myPongGlobals)
{
	fillScreen(myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB,0);
	renderInitialPlayers(myPongGlobals);
}

//Sleeping function to kill time. Should probably update this to use tick.
void wait(int t) {
	int i = 0;
	int j = 0;
	int z = 0;

	for (i = 0; i < t; i++) {
		for (j = 0; j < t; j++) {
			z = i / 33;
		}
	}

};


//Draws the win screen.
void renderWin(struct pongGlobals *myPongGlobals) {
	if (myPongGlobals->winningPlayer == 1) {
		char p1win[255];
		__os_snprintf(p1win, 255, "Player 1 Wins!");
		drawString(myPongGlobals->winX, myPongGlobals->winY, p1win);
	}
	if (myPongGlobals->winningPlayer == 2) {
		char p2win[255];
		__os_snprintf(p2win, 255, "Player 2 Wins!");
		drawString(myPongGlobals->winX, myPongGlobals->winY, p2win);
	}
};

//Draws the inital player paddles and ball.
void renderInitialPlayers(struct pongGlobals *myPongGlobals) {
	drawFillRect(myPongGlobals->p1X_old, myPongGlobals->p1Y_old - myPongGlobals->p1Y_size, myPongGlobals->p1X_old + myPongGlobals->p1X_size, myPongGlobals->p1Y_old, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	
	drawFillRect(myPongGlobals->p2X_old, myPongGlobals->p2Y_old - myPongGlobals->p2Y_size, myPongGlobals->p2X_old + myPongGlobals->p2X_size, myPongGlobals->p2Y_old, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	drawFillRect(myPongGlobals->ballX_old, myPongGlobals->ballY_old - myPongGlobals->ballY_size, myPongGlobals->ballX_old + myPongGlobals->ballX_size, myPongGlobals->ballY_old, myPongGlobals->ballColorR, myPongGlobals->ballColorG, myPongGlobals->ballColorB, 0);
	
	char credits[255];
	__os_snprintf(credits, 255, "Pong by Relys!");
	drawString(myPongGlobals->winX, myPongGlobals->winY+1, credits);
};

//Draws player1's paddle
void renderP1(struct pongGlobals *myPongGlobals) {
	//move up
	if (myPongGlobals->p1Y_old>myPongGlobals->p1Y)
	{
		drawLine(myPongGlobals->p1X_old, myPongGlobals->p1Y_old, myPongGlobals->p1X_old + myPongGlobals->p1X_size, myPongGlobals->p1Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
		
		drawLine(myPongGlobals->p1X, myPongGlobals->p1Y - myPongGlobals->p1Y_size, myPongGlobals->p1X + myPongGlobals->p1X_size, myPongGlobals->p1Y - myPongGlobals->p1Y_size, myPongGlobals->paddleColorR,myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	}
	//Move down
	if(myPongGlobals->p1Y_old<myPongGlobals->p1Y)
	{
		drawLine(myPongGlobals->p1X, myPongGlobals->p1Y, myPongGlobals->p1X + myPongGlobals->p1X_size, myPongGlobals->p1Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
		drawLine(myPongGlobals->p1X_old, myPongGlobals->p1Y_old - myPongGlobals->p1Y_size, myPongGlobals->p1X_old + myPongGlobals->p1X_size, myPongGlobals->p1Y_old - myPongGlobals->p1Y_size, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
	}
	
	//Move right
	if(myPongGlobals->p1X_old<myPongGlobals->p1X)
	{
		drawLine(myPongGlobals->p1X_old, myPongGlobals->p1Y_old-myPongGlobals->p1Y_size, myPongGlobals->p1X_old , myPongGlobals->p1Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
		drawLine(myPongGlobals->p1X+myPongGlobals->p1X_size, myPongGlobals->p1Y-myPongGlobals->p1Y_size, myPongGlobals->p1X+myPongGlobals->p1X_size, myPongGlobals->p1Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	}
	
	//Move left
	if(myPongGlobals->p1X_old>myPongGlobals->p1X)
	{
		drawLine(myPongGlobals->p1X, myPongGlobals->p1Y-myPongGlobals->p1Y_size, myPongGlobals->p1X , myPongGlobals->p1Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
		drawLine(myPongGlobals->p1X_old+myPongGlobals->p1X_size, myPongGlobals->p1Y_old-myPongGlobals->p1Y_size, myPongGlobals->p1X_old+myPongGlobals->p1X_size, myPongGlobals->p1Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
	}
}

//Draws player2's paddle
void renderP2(struct pongGlobals *myPongGlobals) {
	//move up
	if (myPongGlobals->p2Y_old>myPongGlobals->p2Y)
	{
		drawLine(myPongGlobals->p2X_old, myPongGlobals->p2Y_old, myPongGlobals->p2X_old + myPongGlobals->p2X_size, myPongGlobals->p2Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
		
		drawLine(myPongGlobals->p2X, myPongGlobals->p2Y - myPongGlobals->p2Y_size, myPongGlobals->p2X + myPongGlobals->p2X_size, myPongGlobals->p2Y - myPongGlobals->p2Y_size, myPongGlobals->paddleColorR,myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	}
	//Move down
	if(myPongGlobals->p2Y_old<myPongGlobals->p2Y)
	{
		drawLine(myPongGlobals->p2X, myPongGlobals->p2Y, myPongGlobals->p2X + myPongGlobals->p2X_size, myPongGlobals->p2Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
		drawLine(myPongGlobals->p2X_old, myPongGlobals->p2Y_old - myPongGlobals->p2Y_size, myPongGlobals->p2X_old + myPongGlobals->p2X_size, myPongGlobals->p2Y_old - myPongGlobals->p2Y_size, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
	}
	
	//Move right
	if(myPongGlobals->p2X_old<myPongGlobals->p2X)
	{
		drawLine(myPongGlobals->p2X_old, myPongGlobals->p2Y_old-myPongGlobals->p2Y_size, myPongGlobals->p2X_old , myPongGlobals->p2Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
		drawLine(myPongGlobals->p2X+myPongGlobals->p2X_size, myPongGlobals->p2Y-myPongGlobals->p2Y_size, myPongGlobals->p2X+myPongGlobals->p2X_size, myPongGlobals->p2Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
	}
	
	//Move left
	if(myPongGlobals->p2X_old>myPongGlobals->p2X)
	{
		drawLine(myPongGlobals->p2X, myPongGlobals->p2Y-myPongGlobals->p2Y_size, myPongGlobals->p2X , myPongGlobals->p2Y, myPongGlobals->paddleColorR, myPongGlobals->paddleColorG, myPongGlobals->paddleColorB, 0);
		drawLine(myPongGlobals->p2X_old+myPongGlobals->p2X_size, myPongGlobals->p2Y_old-myPongGlobals->p2Y_size, myPongGlobals->p2X_old+myPongGlobals->p2X_size, myPongGlobals->p2Y_old, myPongGlobals->backgroundColorR, myPongGlobals->backgroundColorG, myPongGlobals->backgroundColorB, 0);
	}

}
