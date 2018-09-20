/* closegraph example */



#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>



int main(void)

{

   /* request autodetection */

   int gdriver = DETECT, gmode, errorcode, x, y;



   /* initialize graphics mode */

   initgraph(&gdriver, &gmode, "");



   /* read result of initialization */

   errorcode = graphresult();



   if (errorcode != grOk) {   /* an error occurred */

      printf("Graphics error: %s\n", grapherrormsg(errorcode));

      printf("Press any key to halt:");



      getch();

      exit(1);               /* terminate with an error code */

      }



   x = getmaxx() / 2;

   y = getmaxy() / 2;



   /* output a message */

   settextjustify(CENTER_TEXT, CENTER_TEXT);

   outtextxy(x, y, "Press a key to close the graphics system:");



   getch();   /* wait for a key */

   /* closes down the graphics system */

   closegraph();

   printf("We're now back in text mode.\n");

   printf("Press any key to halt:");

   getch();

   return 0;



}

