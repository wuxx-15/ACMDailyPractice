#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN=1000005;
int n;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

void addEdge(int u,int v)
{
    Next[cntg]=head[u];
    head[u]=cntg;
    to[cntg++]=v;
}

int ans[MAXN];
int cntAns=0;

int diameter;
int h;
int sNode;
int tNode;
int dist[MAXN];
int last[MAXN];

void dfs1(int u,int f,int w)
{
    last[u]=f;
    dist[u]=dist[f]+w;
    for (int e=head[u],v;e != 0;e=Next[e])
    {
        v=to[e];
        if (v != f)
            dfs1(v,u,1);
    }
}

int depth1[MAXN];
int maxdepth1[MAXN];
int valid1[MAXN];
int cnt1;
int depth2[MAXN];
int maxdepth2[MAXN];
int valid2[MAXN];
int cnt2;

void dfs2(int u,int f)
{
    bool isLeaf=true;
    depth1[u]=depth1[f]+1;
    maxdepth1[u]=depth1[u];
    int cnt=0;
    for (int e=head[u],v;e != 0;e=Next[e])
    {
        v=to[e];
        if (v != f)
        {
            isLeaf=false;
            dfs2(v,u);
            if (maxdepth1[v]>=h)
                ++cnt;
            maxdepth1[u]=max(maxdepth1[u],maxdepth1[v]);
        }
    }
    if (isLeaf)
    {
        if (depth1[u]>=h)
            valid1[++cnt1]=depth1[u];
    }
    else
    {
        if (cnt>=2)
            valid1[++cnt1]=depth1[u];
    }
}

void dfs3(int u,int f)
{
    bool isLeaf=true;
    depth2[u]=depth2[f]+1;
    maxdepth2[u]=depth2[u];
    int cnt=0;
    for (int e=head[u],v;e != 0;e=Next[e])
    {
        v=to[e];
        if (v != f)
        {
            isLeaf=false;
            dfs3(v,u);
            if (maxdepth2[v]>=h)
                ++cnt;
            maxdepth2[u]=max(maxdepth2[u],maxdepth2[v]);
        }
    }
    if (isLeaf) //深度为h的叶，是直径端点
    {
        if (depth2[u]>=h)
            valid2[++cnt2]=depth2[u];
    }
    else //有两个孩子子树里有深度为h的叶，可做两条直径公共部分的端点
    {
        if (cnt>=2)
            valid2[++cnt2]=depth2[u];
    }
}

void solve()
{
    //两次DFS求直径
    dfs1(1,0,0);
    sNode=1;
    for (int i=2;i<=n;++i)
    {
        if (dist[i]>dist[sNode])
            sNode=i;
    }
    dfs1(sNode,0,0);
    tNode=1;
    for (int i=2;i<=n;++i)
    {
        if (dist[i]>dist[tNode])
            tNode=i;
    }
    diameter=dist[tNode];

    h=diameter/2; //直径的一半（向下取整）

    int center1=tNode;
    for (int i=0;i<h;++i)
        center1=last[center1];
    int center2=last[center1];

    memset(depth1,0,sizeof(int)*(n+1));
    memset(maxdepth1,0,sizeof(int)*(n+1));
    cnt1=0;
    depth1[center2]=-1;
    dfs2(center1,center2);
    memset(depth2,0,sizeof(int)*(n+1));
    memset(maxdepth2,0,sizeof(int)*(n+1));
    cnt2=0;
    depth2[center1]=-1;
    dfs3(center2,center1);

    sort(valid1+1,valid1+cnt1+1);
    int len=cnt1;
    cnt1=1;
    for (int i=2;i<=len;++i)
    {
        if (valid1[i] != valid1[cnt1])
            valid1[++cnt1]=valid1[i];
    }
    sort(valid2+1,valid2+cnt2+1);
    len=cnt2;
    cnt2=1;
    for (int i=2;i<=len;++i)
    {
        if (valid2[i] != valid2[cnt2])
            valid2[++cnt2]=valid2[i];
    }

    cntAns=0;
    for (int i=1;i<=cnt1;++i)
    {
        for (int j=1;j<=cnt2;++j)
        {
            ans[++cntAns]=valid1[i]+valid2[j]+1;
        }
    }
    sort(ans+1,ans+cntAns+1);
    len=cntAns;
    cntAns=1;
    for (int i=2;i<=len;++i)
    {
        if (ans[cntAns] != ans[i])
            ans[++cntAns]=ans[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    while (t--)
    {
        cin>>n;
        cntg=1;
        memset(head,0,sizeof(int)*(n+1));
        for (int i=1,u,v;i<n;++i)
        {
            cin>>u>>v;
            addEdge(u,v);
            addEdge(v,u);
        }
        solve();
        cout<<cntAns<<' ';
        for (int i=1;i<=cntAns;++i)
            cout<<ans[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
