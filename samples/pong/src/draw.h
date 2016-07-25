#ifndef DRAW_H
#define DRAW_H
#include <coreinit/screen.h>
#include <wut_types.h>

void *screenBuffer;

//Function declarations for my graphics library
void flipBuffers();
void fillScreen(char r, char g, char b, char a);
void drawString(int x, int y, char * string);
void drawPixel(int x, int y, char r, char g, char b, char a);
void drawLine(int x1, int y1, int x2, int y2, char r, char g, char b, char a);
void drawRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a);
void drawFillRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a);
void drawCircle(int xCen, int yCen, int radius, char r, char g, char b, char a);
void drawFillCircle(int xCen, int yCen, int radius, char r, char g, char b, char a);
void drawCircleCircum(int cx, int cy, int x, int y, char r, char g, char b, char a);
#endif /* DRAW_H */
