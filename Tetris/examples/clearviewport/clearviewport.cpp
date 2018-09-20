/* clearviewport example */



#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>



#define CLIP_ON 1   /* activates clipping in viewport */



int main(void)

{

   /* request autodetection */

   int gdriver = DETECT, gmode, errorcode, ht;



   /* initialize graphics and local variables */

   initgraph(&gdriver, &gmode, "");



   /* read result of initialization */

   errorcode = graphresult();

   if (errorcode != grOk) {   /* an error occurred */

      printf("Graphics error: %s\n", grapherrormsg(errorcode));



      printf("Press any key to halt:");

      getch();

      exit(1);               /* terminate with an error code */

   }



   setcolor(getmaxcolor());

   ht = textheight("W");



   /* message in default full-screen viewport */

   outtextxy(0, 0, "* <-- (0, 0) in default viewport");



   /* create a smaller viewport */

   setviewport(50, 50, getmaxx()-50, getmaxy()-50, CLIP_ON);



   /* display some messages */

   outtextxy(0, 0, "* <-- (0, 0) in smaller viewport");



   outtextxy(0, 2*ht, "Press any key to clear viewport:");



   getch();   /* wait for a key */

   clearviewport();   /* clear the viewport */

   /* output another message */

   outtextxy(0, 0, "Press any key to quit:");



   /* clean up */

   getch();

   closegraph();

   return 0;

}
