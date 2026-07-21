#include <iostream>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;

struct Node
{
    ll sa,sb;
    int id;
    bool operator<(const Node& n2) const
    {
        if (sa*n2.sb != n2.sa*sb)
            return sa*n2.sb < n2.sa*sb;
        return id > n2.id;
    }
};

const int MAXN=200005;
int n;
ll a[MAXN],b[MAXN];
ll suma[MAXN],sumb[MAXN];
int up[MAXN];
int father[MAXN];

int find(int i)
{
    if (i != father[i]) father[i]=find(father[i]);
    return father[i];
}

ll compute()
{
    ll ans=0;
    priority_queue<Node> pq;
    for (int i=2;i<=n;++i)
        pq.push({suma[i],sumb[i],i});
    while (!pq.empty())
    {
        auto cur=pq.top();
        pq.pop();
        int u=cur.id;
        if (u==1) continue;
        //合并过了
        if (find(u) != u) continue;
        //过期数据
        if (suma[u] != cur.sa || sumb[u] != cur.sb) continue;

        int p=find(up[u]);

        ans+=suma[u]*sumb[p];

        suma[p]+=suma[u];
        sumb[p]+=sumb[u];
        father[u]=p;

        if (p != 1)
            pq.push({suma[p],sumb[p],p});
    }
    return ans;
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
        {
            cin>>a[i];
            suma[i]=a[i];
        }
        for (int i=1;i<=n;++i)
        {
            cin>>b[i];
            sumb[i]=b[i];
        }
        for (int i=1;i<=n;++i)
        {
            cin>>up[i];
            father[i]=i;
        }
        cout<<compute()<<'\n';
    }
    return 0;
}
