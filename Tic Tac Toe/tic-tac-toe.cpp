#include<iostream>
#include<stdlib.h>

using namespace std;

class tree
{
    class node
    {
        public:
        int *board;
        node **child;

        node()
        {
            board=new int[9];
            child=new node*[9];
            for(int i=0;i<9;i++)
            {
                board[i]=0;
                *(child+i)=NULL;
            }
        }

        void display(int f=0)
        {
            for(int i=0;i<9;i++)
            {
                if(!(i%3)) cout<<"\n";
                for(int j=0;j<=f;j++)
                cout<<" "; cout<<*(board+i);
            }
        }
    }*root;

    public:
    tree()
    {
        root=new node();
        root->display();
    }
};

int main()
{
    tree obj;
}
