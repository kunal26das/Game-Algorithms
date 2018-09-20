#include<iostream>
#include<stdlib.h>
#include<windows.h>
#define n 7

using namespace std;

class pos
{
    public:
    int x,y;
    pos(){x=0;y=0;}
    pos(int p,int q)
    {x=p;y=q;}
    void assign(int p,int q)
    {x=p;y=q;}
    bool operator==(bool temp)
    {
        if(!x&&!y)
        return false;
        return true;
    }
    bool operator==(pos &temp)
    {
        if(x==temp.x&&y==temp.y)
        return true; return false;
    }
    void operator=(pos &temp)
    {x=temp.x; y=temp.y;}
    void display()
    {cout<<"("<<x<<","<<y<<")";}
};

void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut,wColor);
    }
}

int m=0;
int matrix[n][n]={
    {0,0,0,4,0,0,0},
    {0,3,0,0,2,5,0},
    {0,0,0,3,1,0,0},
    {0,0,0,5,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0},
    {2,0,0,0,4,0,0}
};
int visited[n][n]={
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
};
pos start[n],finish[n];

void display()
{
    system("cls");
    for(int i=0;i<n;i++)
    {
        cout<<"\n ";
        for(int j=0;j<n;j++)
        cout<<" ---";
        cout<<" \n ";
        for(int j=0;j<n;j++)
        {
            cout<<"| ";
            if(matrix[i][j])
            {
                setcolor(matrix[i][j]);
                cout<<matrix[i][j];
                setcolor(7);
            }
            else if(visited[i][j])
            {
                setcolor(visited[i][j]);
                cout<<visited[i][j];
                setcolor(7);
            }
            else cout<<" ";
            cout<<" ";
        }
        cout<<"|";
    }
    cout<<"\n ";
    for(int j=0;j<n;j++)
    cout<<" ---";
    cout<<"\n ";
    //system("pause");
}

void print(pos path[],int s)
{
    cout<<"\n ";
    for(int i=0;i<s;i++)
    path[i].display();
    cout<<endl;
}

bool connect(pos p,pos q,int no)
{
    if(no>m) return true;
    int a=p.x,b=p.y;
    int c=q.x,d=q.y;
    if(a<0||a>=n||b<0||b>=n) return false;
    if(matrix[a][b]&&matrix[a][b]!=no) return false;
    if(visited[a][b]) return false;

    visited[a][b]=no;
    if(p==q)
    {
        display();
        if(!connect(start[no+1],finish[no+1],no+1))
        {
            visited[a][b]=0;
            return false;
        }
        else return true;
    }

    pos temp[4];
    temp[0].assign(a-1,b); //up
    temp[1].assign(a+1,b); //down
    temp[2].assign(a,b-1); //left
    temp[3].assign(a,b+1); //right

    bool reach[4];
    for(int j=0;j<4;j++)
    reach[j]=connect(temp[j],q,no);

    for(int j=0;j<4;j++)
    if(reach[j]) return true;
    visited[a][b]=0;
    return false;
}

void solve()
{
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    if(matrix[i][j])
    {
        if(matrix[i][j]>m)
            m=matrix[i][j];
        if(start[matrix[i][j]]==true)
        finish[matrix[i][j]].assign(i,j);
        else start[matrix[i][j]].assign(i,j);
    }
    connect(start[1],finish[1],1);
}

int main(){solve();}
