#include <iostream>
using namespace std;
int n,m,q;
const int MAXS=250001;
const int MAXT=MAXS<<1;
int dist[5]={-1,0,1,0,-1};
int id(int x,int y) //映射到一维坐标
{
    if (x < 1 || x > n || y < 1 || y > m) return -1;
    return (x-1)*m+y;
}

int father[MAXT];
int max_cost[MAXT];
int sizes[MAXT];
int volume[MAXT];

int head[MAXT];
int Next[MAXT];
int to[MAXT];
int cntg=1;

void addEdge(int u,int v)
{
    Next[cntg]=head[u];
    head[u]=cntg;
    to[cntg++]=v;
}

int find(int i) //做路径压缩
{
    if (i==father[i]) return i;
    int p=father[i];
    int root=find(p);
    max_cost[i]=max(max_cost[i],max_cost[p]);
    father[i]=root;
    return root;
}

int solve1(int x,int y)
{
    int cur=id(x,y);
    return sizes[find(cur)]-1;
}

int solve2(int x,int y)
{
    int cur=id(x,y);
    int root=find(cur);
    if (root==cur) return 0; 

    int v=volume[cur];
    return max(0,max_cost[cur]-v);
}

void addFish(int x,int y,int v)
{
    int cur=id(x,y);
    volume[cur]=v;
    father[cur]=cur;
    sizes[cur]=1;
    for (int i=0,root,np;i<4;++i)
    {
        np=id(x+dist[i],y+dist[i+1]);
        if (np != -1 && father[np] > 0)
        {
            root=find(np);
            //加进来的鱼体积最大，做root
            if (root != cur) //本来就连通的不要合并       
            {
                father[root]=cur;
                max_cost[root]=v-sizes[root]+1;
                sizes[cur]+=sizes[root];
            } 
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m>>q;
    int op,x,y,v;
    int lastAns=0;
    while (q--)
    {
        cin>>op>>x>>y;
        x^=lastAns;
        y^=lastAns;
        if (op==1)
        {
            cin>>v;
            addFish(x,y,v);
            lastAns=solve1(x,y);
        }
        else
        {
            lastAns=solve2(x,y);
        }
        cout<<lastAns<<'\n';
    }
    return 0;
}
