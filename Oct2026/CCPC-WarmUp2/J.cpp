#include <iostream>
using namespace std;
const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXP=20;
int n,m,q;
int cntn;

int headg[MAXN];
int Nextg[MAXM<<1];
int tog[MAXM<<1];
int cntg=1;
void addEdgeG(int u,int v)
{
    Nextg[cntg]=headg[u];
    headg[u]=cntg;
    tog[cntg++]=v;
}

int headc[MAXN<<1];
int Nextc[MAXM<<2];
int toc[MAXM<<2];
int cntc=1;

void addEdgeC(int u,int v)
{
    Nextc[cntc]=headc[u];
    headc[u]=cntc;
    toc[cntc++]=v;
}

int dfn[MAXN<<1];
int low[MAXN];
int cntd;

int Stack[MAXN];
int top;

int depth[MAXN<<1];
int RMQ[MAXN<<1][MAXP];
int dfn_cnt;

void Tarjan(int u)
{
    dfn[u]=low[u]=++cntd;
    Stack[++top]=u;
    for (int e=headg[u],v;e != 0;e=Nextg[e])
    {
        v=tog[e];
        if (dfn[v]==0)
        {
            Tarjan(v);
            low[u]=min(low[u],low[v]);
            if (low[v] >= dfn[u])
            {
                ++cntn;
                addEdgeC(cntn,u);
                addEdgeC(u,cntn);
                int pop;
                do
                {
                    pop=Stack[top--];
                    addEdgeC(cntn,pop);
                    addEdgeC(pop,cntn);
                } while (pop != v);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void dfs(int u,int f)
{
    depth[u]=depth[f]+1;
    dfn[u]=++dfn_cnt;
    RMQ[dfn[u]][0]=f;
    for (int e=headc[u],v;e != 0;e=Nextc[e])
    {
        v=toc[e];
        if (v != f)
            dfs(v,u);
    }
}

int getUp(int x,int y)
{
    return dfn[x] < dfn[y] ? x : y;
}

int lg2(int x)
{
    return 31-__builtin_clz(x);
}

void buildRMQ()
{
    int limit=lg2(cntn);
    for (int pre=0,cur=1;cur <= limit;++pre,++cur)
    {
        for (int i=1;i+(1<<cur)-1<=cntn;++i)
            RMQ[i][cur]=getUp(RMQ[i][pre],RMQ[i+(1<<pre)][pre]);
    }
}

int getLCA(int x,int y)
{
    if (x == y)
        return x;
    x=dfn[x];
    y=dfn[y];
    if (x > y)
        swap(x,y);
    ++x;
    int k=lg2(y-x+1);
    return getUp(RMQ[x][k],RMQ[y-(1<<k)+1][k]);
}

int getDist(int x,int y)
{
    return depth[x]+depth[y]-2*depth[getLCA(x,y)];
}

int solve(int x,int y)
{
    if (x == y)
        return 0;
    return getDist(x,y)/2-1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> q;
    cntn=n;
    for (int i=1,u,v;i <= m;++i)
    {
        cin >> u >> v;
        addEdgeG(u,v);
        addEdgeG(v,u);
    }
    Tarjan(1);
    dfs(1,0);
    buildRMQ();
    int x,y;
    while (q--)
    {
        cin >> x >> y;
        int ans=solve(x,y);
        cout << ans << '\n';
    }
    return 0;
}
