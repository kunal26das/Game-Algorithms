/*
    Batch B4, Group members :
    Kunal Das       (15103262)
    Aarush Verma    (15103116)
    Vaibhav Sharma  (15103226)
    Rohan Kumar     (15103217)

*/

#include<graphics.h>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<queue>

#define Block 20
#define Width Block*15
#define Height Block*20
#define mrow Height/Block
#define mcol Width/Block
#define Name "Tetris"

int Score;
int Memory[mrow][mcol];

using namespace std;

class Position
{
    public:
    int x,y;
    Position()
    {
        x=(mcol-2)/2;
        y=0;
    }
    void Down()
    {
        y++;
    }
    int Left()
    {
        x--;
    }
    int Right()
    {
        x++;
    }
};

class Tetriminio
{
    public:
    //Data-Members
    Position p; //Stores top left x and y co-ordinates
    int colour; //Stores color of the piece
    int row,col; //Stores the row and col length
    int Space[4][4]; //Stores the shape of the piece
    //Member-Function
    Tetriminio(); //Default constructor
    void Create(int temp[][4],int m,int n,int c);
    void RotateLeft(); //Rotate piece anti-clock wise
    void RotateRight(); //Rotate piece clock wise
    int PushDown(); //Push the piece one block down
    int ShiftLeft(); //Shift the piece one block to the left
    int ShiftRight(); //Shift the piece one block to the right
    //int Drop(); //Drop the piece vertically
    int Check(); //Check whether the current position fits the piece in memory
    void Remove(); //Remove the piece from the memory at given position
    void Store(); //Write the piece into memory
    void Display(); //Display the current shape of piece
}Piece[7];

/*class Queue
{
    Tetriminio *array;
    int size,front,rear;
    public:
    queue(int s)
    {
        array=new Tetriminio[s];
        front=-1;
        rear=-1;
        size=s;
    }
    int Empty()
    {
        if(front==-1)
        return 1;
        return 0;
    }
    int Full()
    {
        if(rear==size-1)
        return 1;
        return 0;
    }
    void Enqueue(Tetriminio T)
    {
        if(front==-1) front++;
        array[++rear]=T;
    }
    Tetriminio Dequeue()
    {
        Tetriminio temp;
        temp=array[front];
        if(front==rear)
        {
            front=-1;
            rear=-1;
        }
        else front++;
        return temp;
    }
    void Shuffle(){}
};*/

Tetriminio::Tetriminio()
{
    colour=COLOR(0,0,0);
    row=4; col=4;
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    Space[i][j]=0;
}

void Tetriminio::Create(int temp[][4],int m,int n,int c)
{
    colour=c; row=m; col=n;
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    Space[i][j]=temp[i][j];
}

void Tetriminio::RotateLeft()
{
    Remove();

    int temp[4][4];
    for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
    {
        temp[i][j]=Space[i][j];
        Space[i][j]=0;
    }
    for(int i=0,n=0;i<row;i++,n++)
    for(int j=0,m=col-1;j<col;j++,m--)
    Space[m][n]=temp[i][j];
    swap(row,col);

    int flag=1;
    for(int i=p.y,m=0;m<row;i++,m++)
    for(int j=p.x,n=0;n<col;j++,n++)
    if(Space[m][n]&&Memory[i][j])
    flag=0;

    if(!flag)
    {
        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        Space[i][j]=temp[i][j];
        swap(row,col);
    }
    Store();
}

void Tetriminio::RotateRight()
{
    Remove();

    int temp[4][4];
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    {
        temp[i][j]=Space[i][j];
        Space[i][j]=0;
    }
    for(int i=0,n=row-1;i<row;i++,n--)
    for(int j=0,m=0;j<col;j++,m++)
    Space[m][n]=temp[i][j];
    swap(row,col);

    int flag=1;
    for(int i=p.y,m=0;m<row;i++,m++)
    for(int j=p.x,n=0;n<col;j++,n++)
    if(Space[m][n]&&Memory[i][j])
    flag=0;

    if(!flag)
    {
        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        Space[i][j]=temp[i][j];
        swap(row,col);
    }
    Store();
}

int Tetriminio::PushDown()
{
    if(p.y+row>=mrow) return 0;

    for(int j=p.x,n=0;n<col;j++,n++)
    for(int i=p.y,m=0;m<row;i++,m++)
    if(Space[m][n]&&!Space[m+1][n])
    if(Memory[i+1][j])
    return 0;

    Remove();
    p.Down();
    Store();
    return 1;
}

int Tetriminio::ShiftLeft()
{
    if(p.x-1<0) return 0;

    for(int i=p.y,m=0;m<row;i++,m++)
    if(Space[m][0])
    if(Memory[i][p.x-1])
    return 0;

    Remove();
    p.Left();
    Store();
    return 1;
}

int Tetriminio::ShiftRight()
{
    if(p.x+col>=mcol) return 0;

    for(int i=p.y,m=row-1;m>=0;i++,m--)
    if(Space[m][0])
    if(Memory[i][p.x+col])
    return 0;

    Remove();
    p.Right();
    Store();
    return 1;
}

int Tetriminio::Check()
{
    for(int i=p.y,m=0;m<row;i++,m++)
    for(int j=p.x,n=0;n<col;j++,n++)
    if(Space[m][n]) if(Memory[i][j])
    return 0; return 1;
}

void Tetriminio::Remove()
{
    setfillstyle(SOLID_FILL,COLOR(0,0,0));
    for(int i=p.y,m=0;m<row;i++,m++)
    for(int j=p.x,n=0;n<col;j++,n++)
    if(Space[m][n])
    {
        Memory[i][j]=COLOR(0,0,0);
        bar(j*Block,i*Block,(j+1)*Block,(i+1)*Block);
    }
}

void Tetriminio::Store()
{
    setfillstyle(SOLID_FILL,colour);
    for(int i=p.y,m=0;m<row;i++,m++)
    for(int j=p.x,n=0;n<col;j++,n++)
    if(Space[m][n])
    {
        Memory[i][j]=colour;
        bar(j*Block,i*Block,(j+1)*Block,(i+1)*Block);
    }
}

void Tetriminio::Display()
{
    for(int i=0;i<row;i++)
    {
        cout<<endl;
        for(int j=0;j<col;j++)
        cout<<" "<<Space[i][j];
    }
    cout<<endl;
}

//End of class tetriminio

void Reset()
{
    Score=0;
    for(int i=0;i<mrow;i++)
    for(int j=0;j<mcol;j++)
    Memory[i][j]=COLOR(0,0,0);
}

void CreatePieceI()//0
{
    int Space[4][4]={
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[0].Create(Space,1,4,COLOR(0,255,255));
}

void CreatePieceJ()//1
{
    int Space[4][4]={
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[1].Create(Space,2,3,COLOR(0,0,255));
}

void CreatePieceL()//2
{
    int Space[4][4]={
        {1,1,1,0},
        {1,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[2].Create(Space,2,3,COLOR(255,165,0));
}

void CreatePieceO()//3
{
    int Space[4][4]={
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[3].Create(Space,2,2,COLOR(255,255,0));
}

void CreatePieceS()//4
{
    int Space[4][4]={
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[4].Create(Space,2,3,COLOR(0,255,0));
}

void CreatePieceT()//5
{
    int Space[4][4]={
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[5].Create(Space,2,3,COLOR(170,0,255));
}

void CreatePieceZ()//6
{
    int Space[4][4]={
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };Piece[6].Create(Space,2,3,COLOR(255,0,0));
}

void CreatePieces()
{
    CreatePieceI();
    CreatePieceJ();
    CreatePieceL();
    CreatePieceO();
    CreatePieceS();
    CreatePieceT();
    CreatePieceZ();
}

Tetriminio RandomPiece()
{
    int _Piece=rand()%7;
    return Piece[_Piece];
}

int CheckLines(Tetriminio T)
{
    int flag;
    for(int i=T.p.y,m=0;m<T.row;i++,m++)
    {
        flag=1;
        for(int j=0;j<mcol;j++)
        if(!Memory[i][j])
        {
            flag=0;
            break;
        }
        if(flag)
        {
            Score+=100;
            setfillstyle(SOLID_FILL,COLOR(0,0,0));
            for(int j=0;j<mcol;j++)
            {
                Memory[i][j]=0;
                bar(j*Block,i*Block,(j+1)*Block,(i+1)*Block);
            }
            for(int a=T.p.y;a>=0;a--)
            for(int b=0;b<mcol;b++)
            {
                Memory[a][b]=Memory[a-1][b];
                setfillstyle(SOLID_FILL,Memory[a][b]);
                bar(b*Block,a*Block,(b+1)*Block,(a+1)*Block);
            }
        }
    }
}

void DisplayMemory()
{
    for(int i=0;i<mrow;i++)
    {
        cout<<endl;
        for(int j=0;j<mcol;j++)
        {
            cout<<" ";
            if(Memory[i][j]) cout<<"*";
            else cout<<" ";
        }
    }
    cout<<endl;
}

int GameOver(Tetriminio T)
{
    if(T.Check())
    {
        T.Store();
        return 0;
    }
    else
    {
        cout<<"\n Game Over.";
        return 1;
    }
}

void NewGame()
{
    if(initwindow(Width,Height,Name)==0)
    {
        int ch,flag;
        queue<Tetriminio> Incoming;
        Tetriminio CurrentPiece;
        for(int i=0;i<100;i++)
        Incoming.push(RandomPiece());
        //Incoming.Shuffle();
        do
        {
            flag=1;
            CurrentPiece=Incoming.front();
            Incoming.pop();
            if(GameOver(CurrentPiece))
            break;
            do{
                if(kbhit())
                {
                    ch=getch();
                    if(ch==32)
                        while(CurrentPiece.PushDown()){}
                    else if(ch==72)
                        CurrentPiece.RotateLeft();
                    else if(ch==75&&!CurrentPiece.ShiftLeft())
                        {break;}
                    else if(ch==77&&!CurrentPiece.ShiftRight())
                        {break;}
                    else if(ch==80&&!CurrentPiece.PushDown())
                        {break;}
                }
                else if(CurrentPiece.PushDown())
                delay(800);
                else
                {
                    CheckLines(CurrentPiece);
                    delay(800);
                    flag=0;
                }
            }while(flag);
        }while(true);
    }
    else cout<<"\n Window initialization failed. ";
}

void ShowScore()
{
    if(Score)
    cout<<"\n Last game's score was : "<<Score;
    else cout<<"\n No score to display. ";
    cout<<"\n\n ";
}

void Controls()
{
    cout<<"\n Up    : Rotate piece ";
    cout<<"\n Down  : Move piece down by one step ";
    cout<<"\n Left  : Move piece left by one step ";
    cout<<"\n Right : Move piece right by one step ";
    cout<<"\n Space : Drop piece vertically in its place ";
    cout<<"\n\n ";
}

void About()
{
    cout<<"\n Tetris : Version 1.0 \n";
    cout<<"\n Developed by : ";
    cout<<"\n 1. Kunal Das      (15103262)";
    cout<<"\n 2. Aarush Verma   (15103116)";
    cout<<"\n 3. Vaibhav Sharma (15103226)";
    cout<<"\n 4. Rohan Kumar    (15103217)";
    cout<<"\n\n ";
}

int main()
{
    int ch;
    CreatePieces();
    do
    {
        system("cls");
        cout<<"\n 1. Start Game ";
        cout<<"\n 2. Show Score ";
        cout<<"\n 3. Controls   ";
        cout<<"\n 4. About      ";
        cout<<"\n 5. Quit Game  ";
        cout<<"\n\n Select>>";
        cin>>ch; switch(ch)
        {
            case 1 :
            Reset();
            NewGame();
            ShowScore();
            system("pause");
            break;

            case 2 :
            ShowScore();
            system("pause");
            break;

            case 3 :
            Controls();
            system("pause");
            break;

            case 4 :
            About();
            system("pause");
            break;

            case 0 :
            DisplayMemory();
            system("pause");
            break;
        }
    }while(ch!=5);
}
