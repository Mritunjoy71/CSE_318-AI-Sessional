#include<bits/stdc++.h>
using namespace std;
#define MAX 105

struct Node{
    int x;
    int y;
    Node() {}
    Node(int a,int b) {x=a; y=b;}
    bool operator == (const Node &other) {return x==other.x && y==other.y;}
    bool operator < (const Node &other) const{
        if(x<other.x) return true;
        else if(x==other.x) return y<other.y;
        else return false;
    }
    void Print(){printf("%d %d\n",x,y);}
};

map<Node,bool>Vis;
map<Node,double>Cost;
map<Node,Node>Par;

int row,col;
string G[MAX];
int dirX[4]={0,0,1,-1};
int dirY[4]={1,-1,0,0};
bool isValid(int x,int y) {return x>=1 && y>=1 && x<=row && y<=col && G[x][y]!='#';}

double ManHattan(Node a,Node b){return fabs(a.x-b.x)+fabs(a.y-b.y);}
double Euclidean(Node a,Node b){return hypot(a.x-b.x,a.y-b.y);}
double MaxRC(Node a,Node b){return max(abs(a.x-b.x),abs(a.y-b.y));}

int HType;
double Heuristic(Node a,Node b){
    if(HType==1) return ManHattan(a,b);
    else if(HType==2) return Euclidean(a,b);
    else return MaxRC(a,b);
}

void AStarSearch(Node Start,Node Goal){
    priority_queue< pair<double, Node> >pq;
    pq.push({0,Start});
    Vis[Start]=1;
    Cost[Start]=0;
    Par[Start]=Start;

    while(!pq.empty()){
        Node u=pq.top().second;
        pq.pop();
        if(u==Goal) break;

        int X=u.x; int Y=u.y;
        for(int Mov=0;Mov<4;Mov++){
            int xx=X+dirX[Mov];
            int yy=Y+dirY[Mov];
            if(isValid(xx,yy)){
                Node v=Node(xx,yy);
                double NewCost=Cost[u]+1;
                if(!Vis[v] || NewCost<Cost[v]){
                    Vis[v]=1;
                    Cost[v]=NewCost;
                    Par[v]=u;
                    double Priority=NewCost+Heuristic(v,Goal);
                    pq.push({-Priority,v});
                }
            }
        }
    }
}

int main(){
    scanf("%d %d",&row,&col);
    for(int i=1;i<=row;i++) cin>>G[i], G[i]="0"+G[i];

    int ux,uy;
    int vx,vy;
    for(int i=1;i<=row;i++) for(int j=1;j<=col;j++){
        if(G[i][j]=='S') ux=i, uy=j;
        if(G[i][j]=='G') vx=i, vy=j;
    }

    Node Start=Node(ux,uy);
    Node Goal=Node(vx,vy);
    AStarSearch(Start,Goal);

    Node now=Goal;
    vector<Node>Path;
    while(!(Par[now]==now)) {Path.push_back(now); now=Par[now];}
    Path.push_back(Start);
    reverse(Path.begin(),Path.end());
    for(int i=0;i<Path.size();i++) Path[i].Print();
}

/*
6 10
......##..
.....####.
.S..#...#.
.....###G.
...#......
..........
*/
