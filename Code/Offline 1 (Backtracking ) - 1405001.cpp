#include<bits/stdc++.h>
using namespace std;
#define MAX 10

int n;
int Count=0;
bool Found;
bool vis[MAX][MAX];

void Solve(int x,int y){
    if(x<1 || y<1 || x>n || y>n) return;
    if(vis[x][y]) return;

    Count++;
    vis[x][y]=1;
    if(Count==n*n) Found=true;

    Solve(x-1,y-1);
    Solve(x,y+1);
    Solve(x+1,y);

    vis[x][y]=0;
    Count--;
}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            Found=0;
            Solve(i,j);
            printf("%d ",Found);
        }
        printf("\n");
    }

}
