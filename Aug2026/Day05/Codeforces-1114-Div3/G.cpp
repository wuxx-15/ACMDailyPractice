#include <iostream>
#include <queue>
#define ll long long
using namespace std;
const int MAXN=200005;
int n;
ll arr[MAXN];
int parent[MAXN];

/*
左偏树(小根堆，存子节点子树链的最大点权)
这题不存在"拿原堆中的某个任意节点查所在堆的根"的需求，无需引入DSU查根
*/
ll val[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];

int heapTop[MAXN];

void initHeap()
{
    dist[0]=-1;
    for (int i=1;i<=n;++i)
    {
        ls[i]=rs[i]=dist[i]=0;
        heapTop[i]=0;
    }
}

int merge(int i,int j)
{
    if (i==0 || j==0)
        return i+j;
    if (val[i]>val[j])
        swap(i,j);
    rs[i]=merge(rs[i],j);
    if (dist[ls[i]]<dist[rs[i]])
        swap(ls[i],rs[i]);
    dist[i]=dist[rs[i]]+1;
    return i;
}

ll ans[MAXN];
priority_queue<ll> choices; //可选的额外收益

void solve()
{   
    initHeap();
    ll base=0; //基础收益（划分leaves条链）
    int leaves=0; //叶节点数
    //题目数据保证p[i]<i,故可以按顺序合并
    for (int u=n;u>=1;--u)
    {
        if (heapTop[u]==0)
        {
            ++leaves;
            base+=arr[u];
            val[u]=arr[u];
        }
        else
        {
            //选其中的最小值向上合并，收益最大化
            int oldRoot=heapTop[u];
            ll x=val[oldRoot];
            heapTop[u]=merge(ls[oldRoot],rs[oldRoot]);

            choices.push(min(x,arr[u]));
            base += max(0ll,arr[u]-x);
            val[u]=max(x,arr[u]);
        }

        heapTop[u]=merge(heapTop[u],u);

        if (u != 1)
        {
            int p=parent[u];
            heapTop[p]=merge(heapTop[p],heapTop[u]);
        }
    }
    ans[leaves]=base;
    for (int i=1;i<leaves;++i)
        ans[i]=-1;
    for (int i=leaves+1;i<=n;++i)
    {
        ans[i]=ans[i-1]+choices.top();
        choices.pop();
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
        for (int i=1;i<=n;++i)
            cin>>arr[i];
        parent[1]=0;
        for (int i=2;i<=n;++i)
            cin>>parent[i];
        solve();
        for (int i=1;i<=n;++i)
            cout<<ans[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
