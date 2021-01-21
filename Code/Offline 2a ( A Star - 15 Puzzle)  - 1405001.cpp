#include<bits/stdc++.h>
using namespace std;
#define MAX 105
#define ZERO 0

struct Node{
    int A[3][3];
    Node() {}
    Node(int M[3][3]){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                A[i][j]=M[i][j];
    }
    bool operator == (const Node &other){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(A[i][j]!=other.A[i][j]) return false;
        return true;
    }
    bool operator < (const Node &other) const{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(A[i][j]<other.A[i][j]) return true;
                else if(A[i][j]==other.A[i][j]) continue;
                else return false;
            }
        }
        return false;
    }

    void Print(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++) printf("%d ",A[i][j]);
            printf("\n");
        }
        printf(" ---------\n");
    }
};

map<Node,bool>Vis;
map<Node,double>Cost;
map<Node,Node>Par;

int dirX[4]={0,0,1,-1};
int dirY[4]={1,-1,0,0};
bool isValid(int x,int y) {return x>=0 && y>=0 && x<3 && y<3;}

double MIsplaced(Node a,Node b){
    double Ans=0;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(a.A[i][j] && a.A[i][j]!=b.A[i][j]) Ans++;
    return Ans;
}

double ManHattan(Node a,Node b){
    double Ans=0;
    int pX[10];
    int pY[10];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) pX[a.A[i][j]]=i, pY[a.A[i][j]]=j;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(b.A[i][j]) Ans+=abs(pX[b.A[i][j]]-i)+abs(pY[b.A[i][j]]-j);
    return Ans;
}

double Euclidean(Node a,Node b){
    double Ans=0;
    int pX[10];
    int pY[10];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) pX[a.A[i][j]]=i, pY[a.A[i][j]]=j;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(b.A[i][j]) Ans+=hypot(pX[b.A[i][j]]-i,pY[b.A[i][j]]-j);
    return Ans;
}

double OutOfRowColumn(Node a,Node b){
    double Ans=0;
    int pX[10];
    int pY[10];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) pX[a.A[i][j]]=i, pY[a.A[i][j]]=j;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(b.A[i][j]) Ans+=(pX[b.A[i][j]]!=i)+(pY[b.A[i][j]]!=j);
    return Ans;
}

double nMaxSwap(Node a,Node b){
    int P[10];
    int B[10];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) P[i*3+j]=a.A[i][j];
    for(int i=0;i<9;i++) B[P[i]]=i;

    double Ans=0;
    while(P[B[0]]!=P[B[B[0]]]) {Ans++; swap(P[B[0]],P[B[B[0]]]); swap(B[0],B[B[0]]);}
    return Ans;
}

int HType;
double Heuristic(Node a,Node b){
    if(HType==1) return MIsplaced(a,b);
    else if(HType==2) return ManHattan(a,b);
    else if(HType==3) return Euclidean(a,b);
    else if(HType==4) return OutOfRowColumn(a,b);
    else return nMaxSwap(a,b);
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

        int zX,zY;
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(u.A[i][j]==ZERO) zX=i,zY=j;

        for(int Mov=0;Mov<4;Mov++){
            int xx=zX+dirX[Mov];
            int yy=zY+dirY[Mov];
            if(isValid(xx,yy)){
                Node v=u;
                swap(v.A[zX][zY],v.A[xx][yy]);
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
    Node Start;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&Start.A[i][j]);

    Node Goal;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) Goal.A[i][j]=i*3+j;

    AStarSearch(Start,Goal);

    Node now=Goal;
    vector<Node>Path;
    while(!(Par[now]==now)) {Path.push_back(now); now=Par[now];}
    Path.push_back(Start);
    reverse(Path.begin(),Path.end());
    for(int i=0;i<Path.size();i++) Path[i].Print();

    printf("%.0lf\n",Cost[Goal]);
}

/*
8 2 0 5 4 7 3 6 1
*/
