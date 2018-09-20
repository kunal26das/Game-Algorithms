#include<windows.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

class pos
{
    public:
    int x,y;
    pos(){x=-1;y=-1;}
    pos(int p,int q)
    {x=p;y=q;}
    void assign(int p,int q)
    {x=p;y=q;}
    bool operator==(bool temp)
    {
        if(x==-1&&y==-1)
        return false;
        return true;
    }
    bool operator==(pos &temp)
    {
        if(x==temp.x&&y==temp.y)
        return true; return false;
    }
    bool operator!=(pos &temp)
    {
        if(x!=temp.x||y!=temp.y)
        return true; return false;
    }
    void operator=(pos &temp)
    {x=temp.x; y=temp.y;}
    void display()
    {cout<<"("<<x<<","<<y<<")";}
};

void print(pos path[],int s)
{
    cout<<"\n ";
    for(int i=0;i<s;i++)
    path[i].display();
    cout<<endl;
}

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

class matrix
{
    int full;
    pos *start,*finish;
    int **array,size,max;

    bool connect(pos p,pos q,int n,matrix &solution)
    {
        int a=p.x,b=p.y;
        if(n>max) return true;
        if(a<0||a>=size||b<0||b>=size) return false;
        if(get(p)&&get(p)!=n) return false;
        if(solution.get(p)) return false;

        //solution.full--;
        solution.put(p,n);
        solution.display(this);
        //cout<<n;
        //system("pause");

        if(p==q)
        {
            if(!connect(start[n+1],finish[n+1],n+1,solution))
            {
                //solution.full++;
                solution.put(p,0);
                return false;
            }
            else return true;
        }

        pos temp[4];
        int dx=0,dy=0;
        if(p.x>q.x)
        {
            dx=p.x-q.x;
            if(p.y>q.y)
            {
                dy=p.y-q.y;
                if(dx>dy||dx==dy)
                {
                    temp[0].assign(p.x-1,p.y); //up
                    temp[1].assign(p.x,p.y-1); //left
                    temp[2].assign(p.x+1,p.y); //down
                    temp[3].assign(p.x,p.y+1); //right
                }
                else if(dx<dy||dx==dy)
                {
                    temp[0].assign(p.x,p.y-1); //left
                    temp[1].assign(p.x-1,p.y); //up
                    temp[2].assign(p.x,p.y+1); //right
                    temp[3].assign(p.x+1,p.y); //down
                }
            }
            else if(p.y<q.y)
            {
                dy=q.y-p.y;
                if(dx>dy||dx==dy)
                {
                    temp[0].assign(p.x-1,p.y); //up
                    temp[1].assign(p.x,p.y+1); //right
                    temp[2].assign(p.x+1,p.y); //down
                    temp[3].assign(p.x,p.y-1); //left
                }
                else if(dx<dy||dx==dy)
                {
                    temp[0].assign(p.x,p.y+1); //right
                    temp[1].assign(p.x-1,p.y); //up
                    temp[2].assign(p.x,p.y-1); //left
                    temp[3].assign(p.x+1,p.y); //down
                }
            }
            else
            {
                temp[0].assign(p.x-1,p.y); //up
                temp[1].assign(p.x,p.y-1); //left
                temp[2].assign(p.x,p.y+1); //right
                temp[3].assign(p.x+1,p.y); //down
            }
        }
        else if(p.x<q.x)
        {
            dx=q.x-p.x;
            if(p.y>q.y)
            {
                dy=p.y-q.y;
                if(dx>dy||dx==dy)
                {
                    temp[0].assign(p.x+1,p.y); //down
                    temp[1].assign(p.x,p.y-1); //left
                    temp[2].assign(p.x-1,p.y); //up
                    temp[3].assign(p.x,p.y+1); //right
                }
                else if(dx<dy||dx==dy)
                {
                    temp[0].assign(p.x,p.y-1); //left
                    temp[1].assign(p.x+1,p.y); //down
                    temp[2].assign(p.x,p.y+1); //right
                    temp[3].assign(p.x-1,p.y); //up
                }
            }
            else if(p.y<q.y)
            {
                dy=q.y-p.y;
                if(dx>dy||dx==dy)
                {
                    temp[0].assign(p.x+1,p.y); //down
                    temp[1].assign(p.x,p.y+1); //right
                    temp[2].assign(p.x-1,p.y); //up
                    temp[3].assign(p.x,p.y-1); //left
                }
                else if(dx<dy||dx==dy)
                {
                    temp[0].assign(p.x,p.y+1); //right
                    temp[1].assign(p.x+1,p.y); //down
                    temp[2].assign(p.x,p.y-1); //left
                    temp[3].assign(p.x-1,p.y); //up
                }
            }
            else
            {
                temp[0].assign(p.x+1,p.y); //down
                temp[1].assign(p.x,p.y-1); //left
                temp[2].assign(p.x,p.y+1); //right
                temp[3].assign(p.x-1,p.y); //up
            }
        }
        else
        {
            dx=0;
            if(p.y>q.y)
            {
                temp[0].assign(p.x,p.y-1); //left
                temp[1].assign(p.x-1,p.y); //up
                temp[2].assign(p.x+1,p.y); //down
                temp[3].assign(p.x,p.y+1); //right
            }
            else if(p.y<q.y)
            {
                temp[0].assign(p.x,p.y+1); //right
                temp[1].assign(p.x-1,p.y); //up
                temp[2].assign(p.x+1,p.y); //down
                temp[3].assign(p.x,p.y-1); //left
            }
            else return true;
        }


        /*
        temp[0].assign(p.x-1,p.y); //up
        temp[1].assign(p.x+1,p.y); //down
        temp[2].assign(p.x,p.y-1); //left
        temp[3].assign(p.x,p.y+1); //right
        */

        bool reach[4];
        for(int i=0;i<4;i++)
        reach[i]=connect(temp[i],q,n,solution);

        for(int i=0;i<4;i++)
        if(reach[i]) return true;

        solution.put(p,0);
        return false;
    }

    public:

    matrix()
    {
        max=-1;
        size=0;
        full=0;
        start=NULL;
        array=NULL;
        finish=NULL;
    }

    matrix(int s)
    {
        max=0;
        size=s;
        full=s*s;
        start=NULL;
        finish=NULL;
        array=new int*[s];
        for(int i=0;i<s;i++)
        *(array+i)=new int[s];
        for(int i=0;i<s;i++)
        for(int j=0;j<s;j++)
        array[i][j]=0;
    }

    matrix(int *board,int s)
    {
        max=0;
        size=s;
        full=s*s;
        array=new int*[s];
        for(int i=0;i<s;i++)
        *(array+i)=new int[s];
        for(int i=0;i<s;i++)
        for(int j=0;j<s;j++)
        {
            array[i][j]=*(board+i*s+j);
            if(array[i][j]>max)
            max=array[i][j];
        }
        start=new pos[max+1];
        finish=new pos[max+1];
        for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        if(array[i][j])
        {
            full--;
            if(start[array[i][j]]==true)
            finish[array[i][j]].assign(i,j);
            else start[array[i][j]].assign(i,j);
        }
    }

    void put(pos p,int value)
    {array[p.x][p.y]=value;}

    int get(pos p)
    {return array[p.x][p.y];}

    matrix solve()
    {
        matrix solution(size);
        connect(start[1],finish[1],1,solution);
        return solution;
    }

    void display(matrix *prblm)
    {
        system("cls");
        for(int i=0;i<size;i++)
        {
            cout<<"\n ";
            //for(int j=0;j<size;j++)
            //cout<<" ---";
            cout<<" \n ";
            for(int j=0;j<size;j++)
            {
                cout<<"  ";
                //cout<<"| ";
                if((*prblm).array[i][j])
                {
                    setcolor((*prblm).array[i][j]);
                    cout<<(*prblm).array[i][j];
                    setcolor(7);
                }
                else if(array[i][j])
                {
                    setcolor(array[i][j]);
                    cout<<array[i][j];
                    setcolor(7);
                }
                else cout<<" ";
                cout<<" ";
            }
            cout<<" ";
            //cout<<"|";
        }
        cout<<"\n ";
        //for(int j=0;j<size;j++)
        //cout<<" ---";
        cout<<"\n ";
        //system("pause");
    }
};

int main()
{
    int n=5;
    int board[][n]={
        {1,0,0,0,5},
        {0,0,0,0,0},
        {0,0,2,0,5},
        {3,2,4,0,1},
        {4,0,0,0,3}
    };
    matrix solution;
    int *ptr=&board[0][0];
    matrix problem(ptr,n);
    solution=problem.solve();
    //solution.display();
}
