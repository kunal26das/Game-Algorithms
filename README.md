# Game-Algorithms
Synopsis of
"Tetris" Game
-----------------------------------------------------------------
To be submitted by Group 4d
15103116 - Aarush Verma
15103217 - Rohan Kumar
15103226 - Vaibhav Pandit
15103262 - Kunal Das
of Batch B4
-----------------------------------------------------------------
For the partial fulfillment of the course
Data Structures Lab 15B11CI371
 
Tetris is a tile-matching puzzle video game. The project will feature the same game with seven different pieces of blocks of different shapes, which drop down one by one from top to bottom and the player can adjust their position horizontally. once the piece is placed somewhere, another one will drop down. Score is kept on the basis of how many complete horizontal lines filled with blocks the player destroys. The game will end when the player places a piece on the topmost position of the screen.

Proposed concepts used in the project:
1. Classes and Objects
2. Array and Matrices
3. Stack Data Structure
4. Queue Data Structure
5. Borland Graphics Interface

ABOUT THE PROJECT:
The knight is a piece in the game of chess. It is normally represented by a horse’s head and neck. The knight’s movement is unusual among chess pieces. When it moves, it can move to a square horizontally and on square vertically, or two squares vertically and one square horizontally. The complete move therefore looks like the letter L.
A knight on the edge of the board attacks only three or four squares, depending on its exact location, and a knight in the corner only two.

	a	b	c	d	e	f	g	h	
8		 		 					8
7	 				 				7
6			♘						6
5	 				 				5
4		 		 					4
3									3
2									2
1									1
	a	b	c	d	e	f	g	h	
Knight’s all Possible Moves on a Standard 8x8 Chess Board

 
KNIGHT’S TOUR PROBLEM:
A knight’s tour is a sequence of moves of a knight on a chessboard such that the knight visits every square only once. If the knight ends on a square that ends on a square that is one knight’s move from the beginning square, the tour is closed, otherwise it is open. 

	a	b	c	d	e	f	g	h	
8	15	62	19	34	1	50	31	46	8
7	18	35	16	63	32	47	2	49	7
6	61	14	33	20	51	4	45	30	6
5	36	17	60	13	64	29	48	3	5
4	11	58	21	40	5	52	27	44	4
3	22	37	12	59	28	41	6	53	3
2	57	10	39	24	55	8	43	26	2
1	38	23	56	9	42	25	54	7	1
	a	b	c	d	e	f	g	h	
Example of Set of movements of Knight’s Tour

 
CODE:
<!DOCTYPE html>
<html>
 <head>
  <title> Knight's Tour Demonstration </title>
 </head>
 <body style="text-align:center;
 background-color:#F2F2F2">
  <canvas id="display"> </canvas>
  <script>

   var board,blocks,size,canvas,context;
   execute();

   function execute() {
       create();
       var row=1,col=1;
       if(row>=0&&row<size&&col>=0&&col<size)
       solve(row,col,1);
   }

   function create() {
    board=[
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0]];
    size=64;
    blocks=8;
    canvas=document.getElementById("display");
    context=canvas.getContext("2d");
    canvas.width=size*blocks;
    canvas.height=size*blocks;
    for(var i=0;i<blocks;i++)
    for(var j=0;j<blocks;j++) {
        context.beginPath();
        context.rect(i*size,j*size,size,size);
        if((i+j)%2!=0)
        context.fillStyle="#D18B47";
        else context.fillStyle="#FFCE9E";
        context.fill();
    }
   }

   function solve(row,col,k) {
       var r,c; board[row][col]=k;
       for(var i=1,j=2;i<=2&&j>=1;i++,j--) {
           if(check(row+i,col+j)==1) {
               if(solve(row+i,col+j,k+1)==0)
               board[row+i][col+j]=0;
               else {
                   r=row+i; c=col+j;
                   markpos(k,row,col);
                   drawline(row,col,r,c);
                   return 1;
               }
           }
           if(check(row+i,col-j)==1) {
               if(solve(row+i,col-j,k+1)==0)
               board[row+i][col-j]=0;
               else {
                   r=row+i; c=col-j;
                   markpos(k,row,col);
                   drawline(row,col,r,c);
                   return 1;
               }
           }
           if(check(row-i,col+j)==1) {
               if(solve(row-i,col+j,k+1)==0)
               board[row-i][col+j]=0;
               else {
                   r=row-i; c=col+j;
                   markpos(k,row,col);
                   drawline(row,col,r,c);
                   return 1;
               }
           }
           if(check(row-i,col-j)==1) {
               if(solve(row-i,col-j,k+1)==0)
               board[row-i][col-j]=0;
               else {
                   r=row-i; c=col-j;
                   markpos(k,row,col);
                   drawline(row,col,r,c);
                   return 1;
               }
           }
       }
       if(k==blocks*blocks) {
           markpos(k,row,col);
           return 1;
       }
       else return 0;
   }

   function check(row,col) {
       if(row>=0&&row<blocks&&col>=0&&col<blocks)
       if(board[row][col]==0)
       return 1;
       return 0;
   }

   function markpos(num,row,col) {
       context.fillStyle="#000000";
       context.font="16px consolas";
       context.fillText(num,col*size+2,
       row*size+16);
   }

   function drawline(fromr,fromc,tor,toc) {
       context.moveTo(fromc*size+size/2,
       fromr*size+size/2);
       context.lineTo(toc*size+size/2,
       tor*size+size/2);
       context.stroke();
   }
   
  </script>
 </body>
</html>

 

Analysing multi-aspects for linking numbers in maze solver