#ifndef PONG_H
#define PONG_H
#include <wut_types.h>
#include <vpad/input.h>
//Using modified version of draw to render at twice the scale to improve framerate
#include "draw.h"
//Struct for global variables for pong
struct pongGlobals{
	//Flag for restarting the entire game.
	int restart;
	
	//Gameplay boundry
	int xMinBoundry;
	int xMaxBoundry;
	int yMinBoundry;
	int yMaxBoundry;
	int scale;
	int score1X;
	int score2X;
	int score1Y;
	int score2Y;
	int winX;
	int winY;

	//Globals for ball location and movement dx/dy
	int ballX;
	int ballX_old;
	int ballY;
	int ballY_old;
	int ballX_size;
	int ballY_size;

	//Globals for player1 location and movement dx/dy
	int p1X;
	int p1X_old;
	int p1Y;
	int p1Y_old;
	int p1X_size;
	int p1Y_size;

	//Globals for player2 location and movement dx/dy
	int p2X;
	int p2X_old;
	int p2Y;
	int p2Y_old;
	int p2X_size;
	int p2Y_size;

	int p1X_default;
	int p2X_default;
	int ballX_default;
	int p1Y_default;
	int p2Y_default;
	int ballY_default;

	//Game engine globals
	int direction;
	uint32_t button;
	int paddleColorR;
	int paddleColorG;
	int paddleColorB;
	int ballColorR;
	int ballColorG;
	int ballColorB;
	int ballTrailColorR;
	int ballTrailColorG;
	int ballTrailColorB;
	int backgroundColorR;
	int backgroundColorG;
	int backgroundColorB;
	int count;

	int score1;
	int score2;
	int scoreWin;

	int flag;

	int winningPlayer;

	int renderP1Flag;
	int renderP2Flag;

	int renderResetFlag;
	int renderBallFlag;
	int renderWinFlag;
	int renderScoreFlag;
};

//Function declarations for pong functions.
void renderP2(struct pongGlobals *myPongGlobals);
void renderP1(struct pongGlobals *myPongGlobals);
void renderInitialPlayers(struct pongGlobals *myPongGlobals);
void renderWin(struct pongGlobals *myPongGlobals);
void wait(int t);
void renderReset(struct pongGlobals *myPongGlobals);
void renderScore(struct pongGlobals *myPongGlobals);
void reset(struct pongGlobals *myPongGlobals);
void updatePosition(struct pongGlobals *myPongGlobals);
void resetRenderFlags(struct pongGlobals *myPongGlobals);
void render(struct pongGlobals *myPongGlobals);
void renderBall(struct pongGlobals *myPongGlobals);
void checkWin(struct pongGlobals *myPongGlobals);
void checkCollision(struct pongGlobals *myPongGlobals);
void moveBall(struct pongGlobals *myPongGlobals);
void p2Move(struct pongGlobals *myPongGlobals);
void p1Move(struct pongGlobals *myPongGlobals);
int collisionBox(int box1x, int box1y, int width1, int height1, int box2x, int box2y, int width2, int height2);
#endif /* PONG_H */
