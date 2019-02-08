#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15
#define DONT_BLINK		0
#define BLINK			1

void gotorc(/*char cstr[], int r, int c,*/ int color)
{ 
  HANDLE hConsoleOutput; 
  COORD dwCursorPosition;
 /* cout.flush(); 
  dwCursorPosition.X = c; 
  dwCursorPosition.Y = r; */
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
  //SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);  
  SetConsoleTextAttribute(hConsoleOutput,color);
  //cout<<cstr;
 // SetConsoleTextAttribute(hConsoleOutput,WHITE);
}