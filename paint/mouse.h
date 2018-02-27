#include "mouselib.h"
#include<malloc.h>
//#pragma inline
/*-----------------------------------------------
 InitMouse - Initializes Mouse.
 Returns 0 for success. */

unsigned int ** bufferMouse;

#define O   16  //outer color mouse
#define I   15  //inner color mouse
#define mouseWidth 13
#define mouseHeight 18

/* mouse form */
static unsigned char mouse[mouseWidth * mouseHeight] =
{
  O,0,0,0,0,0,0,0,0,0,0,0,0,
  O,O,0,0,0,0,0,0,0,0,0,0,0,
  O,O,O,0,0,0,0,0,0,0,0,0,0,
  O,O,O,O,0,0,0,0,0,0,0,0,0,
  O,O,I,O,O,0,0,0,0,0,0,0,0,
  O,O,I,I,O,O,0,0,0,0,0,0,0,
  O,O,I,I,I,O,O,0,0,0,0,0,0,
  O,O,I,I,I,I,O,O,0,0,0,0,0,
  O,O,I,I,I,I,I,O,O,0,0,0,0,
  O,O,I,I,I,I,I,I,O,O,0,0,0,
  O,O,I,I,I,I,I,I,I,O,O,0,0,
  O,O,I,I,I,I,I,I,I,I,O,O,0,
  O,O,I,I,I,I,I,I,O,O,O,O,0,
  O,O,I,I,I,I,I,I,O,O,0,0,0,
  O,O,O,O,O,O,I,I,O,O,0,0,0,
  O,O,O,O,O,O,I,I,I,O,0,0,0,
  0,0,0,0,O,O,O,I,I,O,0,0,0,
  0,0,0,0,0,O,O,O,O,O,0,0,0,
};

int InitMouse( void )
{
 asm {
 MOV AX, 0;
 INT 33h;
 }
 return;
} /*--InitMouse( )---*/
/*-----------------------------------------------
 ShowMousePtr - Shows Mouse Pointer. */
void ShowMousePtr( void )
{
 asm {
 MOV AX, 1h
 INT 33h
 }
} /*--ShowMousePtr( )----*/
/*-----------------------------------------------
 HideMousePtr - Hide Mouse Pointer. */
void HideMousePtr( void )
{
 asm {
 MOV AX, 2h;
 INT 33h;
 }
} /*--HideMousePtr( )-----*/
/*-----------------------------------------------
 MoveMousePtr - Move Mouse Pointer
 to (x, y). */


void MoveMousePtr( int x, int y )
{
 asm {
 MOV AX, 4h;
 MOV CX, x;
 MOV DX, y;
 INT 33h;
 }
} /*--MoveMousePtr( )-----*/
/*-----------------------------------------------
 RestrictMousePtr - Restrict Mouse Pointer
 to the specified coordinates */
void RestrictMousePtr( int x1, int y1, int x2, int y2 )
{
 asm {
 MOV AX, 7h;
 MOV CX, x1;
 MOV DX, x2;
 INT 33h;
 MOV AX, 8h;
 MOV CX, y1;
 MOV DX, y2;
 INT 33h;
 }
} /*--RestrictMousePtr( )--------*/
/*-----------------------------------------------
 GetMousePos - Gets Mouse position &
 mouse button value. */
void GetMousePos( int *mbutton, int *mx, int *my )
{
 asm {
 MOV AX, 3h;
 INT 33h;
 MOV AX, BX;
 MOV BX, mbutton;
 MOV WORD PTR [BX], AX;
 MOV BX, mx;
 MOV WORD PTR [BX], CX;
 MOV BX, my;
 MOV WORD PTR [BX], DX;
 }
 } /*--GetMousePos( )------*/ 

//update mouse position
/*void repaintMouse(int *x, int *y, int *clicked, int *xtemp, int *ytemp) {
  //getMouse(x, y, clicked);
  if (*xtemp != *x || *ytemp != *y) {
    mouseHide(*xtemp, *ytemp);
    mouseShow(*x, *y);
    *xtemp = *x;
    *ytemp = *y;
  }
}*/

// Hides mouse from screen
int mouseHide(int x, int y) {
  int i,j;
  for (i=0; i < mouseWidth; i++) {
    for (j=0; j < mouseHeight; j++) {
      putpixel(x+i+2,y+j+2,bufferMouse[i][j]);
    }
    //deallocates the memory, receives pointer
    free(bufferMouse[i]);
  }
  //deallocates the memory, receives pointer
  free(bufferMouse);
  return 0;
}


int mouseShow(int x, int y){
	int i,j;
	bufferMouse=malloc(sizeof(int) * mouseWidth);
	for (i=0;i<mouseWidth;i++){
		bufferMouse[i]=malloc(sizeof(int)*mouseHeight);
		for (j=0;j<mouseHeight;j++)
			bufferMouse[i][j]= getpixel(x+i+2,y+j+2);
	}

	for (i=0;i<mouseHeight;i++){
		for(j=0;j<mouseWidth;j++){
			if (mouse[mouseWidth*i+j]!=0){
				putpixel(x+j+2,y+i+2,mouse[mouseWidth*i+j]);
			}
		}
	}
	return 0;
}
