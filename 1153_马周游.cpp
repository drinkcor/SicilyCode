// Problem#: 1153
// Submission#: 2487276
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int dx[]={-1, -1, -2, -2, 1, 1, 2, 2}; 
int dy[]={-2, 2, 1, -1, 2, -2, 1, -1}; 
bool repeat[8][8];                     //用来记录那些点已经被走过 
int point[64];                         //用来记录马周游的路径 

struct node{                           //用此结构体来记录每一个走过的节点的信息 
    int x,y,ex;
    node (int _x,int _y,int _ex){
         x  = _x;
         y  = _y;
         ex = _ex;     
    } 
};

struct compare{                            //函数对象，实现根据可扩展的宽度对节点进行排序的功能 
    bool operator()(node *n1,node *n2){
        return n1->ex>n2->ex;
    }
};

int extend(int x,int y){               //用来计算节点可扩展的方向个数 
    int exNum=0,nx,ny;
    for (int i=0;i<8;++i){
        nx=x+dx[i];
        ny=y+dy[i];
        if (nx<8 && nx>=0 && ny<8 && ny>=0 && !repeat[nx][ny]){
            ++exNum;
        }
    }
    return exNum;
}

bool travel(int x,int y,int step){        //用来判断当以(x,y)为起点，step为已经经过了的点的个数时，是否能实现马周游。可以的话则打印路径。 
    point[step]=x*8+y+1;
    if (step>=63){
        for (int i=0;i<63;++i)
            cout<<point[i]<<" ";
        cout<<point[63]<<endl;
        return true;
    }
    priority_queue<node*,vector<node*>,compare> pq;
    for (int i=0;i<8;++i){
        int nx=x+dx[i];
        int ny=y+dy[i];

        if (nx<8 && nx>=0 && ny<8 && ny>=0 && !repeat[nx][ny])
            pq.push(new node(nx,ny,extend(nx,ny)));
    }
    while(!pq.empty())  {
        node* tmp=pq.top();
        pq.pop();
        repeat[tmp->x][tmp->y]=true;
        if (travel(tmp->x,tmp->y,step+1))
            return true;
        repeat[tmp->x][tmp->y]=false;
        delete tmp;
    }
    return false;
}
int main(){
    int N;
    int x,y;
    while(cin>>N&&N!=-1){
        memset(repeat,0,sizeof(repeat));                      //将repeat中的元素全部置零 
        x=(N-1)/8;                                            //8*8的格局 
        y=(N-1)%8;
        repeat[x][y]=1;
        travel(x,y,0);
    }
    return 0;
}               
