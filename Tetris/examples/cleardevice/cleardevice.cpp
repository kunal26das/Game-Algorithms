/* cleardevice example */



#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>



int main(void)

{

   /* request autodetection */

   int gdriver = DETECT, gmode, errorcode;

   int midx, midy;



   /* initialize graphics and local variables */

   initgraph(&gdriver, &gmode, "");



   /* read result of initialization */

   errorcode = graphresult();

   if (errorcode != grOk) {    /* an error occurred */

      printf("Graphics error: %s\n", grapherrormsg(errorcode));



      printf("Press any key to halt:");

      getch();

      exit(1);                 /* terminate with an error code */

   }



   midx = getmaxx() / 2;

   midy = getmaxy() / 2;

   setcolor(getmaxcolor());



   /* for centering screen messages */

   settextjustify(CENTER_TEXT, CENTER_TEXT);



   /* output a message to the screen */

   outtextxy(midx, midy, "Press any key to clear the screen:");



   getch();   /* wait for a key */

   cleardevice();   /* clear the screen */



   /* output another message */

   outtextxy(midx, midy, "Press any key to quit:");

   /* clean up */

   getch();

   closegraph();

   return 0;

}
