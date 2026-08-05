#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int MAXN=200005;
const ll INF=1e18;
struct Node
{
    int pos;
    ll val;
    friend bool operator<(const Node& n1,const Node& n2)
    {
        return n1.val<n2.val;
    }
};
ll a[MAXN];
Node b[MAXN];
int n;
struct event
{
    vector<int> p;
    ll val;
    int index;
};

event events[MAXN];

bool solve()
{
    sort(b+1,b+n+1);
    if (b[1].val != 0) return false;
    int cnte=1;
    ll prev=0;
    events[1].p.clear();
    for (int i=1;i<=n;)
    {
        while (i <= n && b[i].val==prev)
        {
            events[cnte].p.push_back(b[i].pos);
            ++i;
        }
        events[cnte].index=i;
        if (i <= n)
        {
            events[cnte].val=b[i].val-prev;
            ++cnte;
            events[cnte].p.clear();
            prev=b[i].val;
        }
    }
    ll lastv=0;
    for (int i=1;i<cnte;++i)
    {
        auto cur=events[i];
        int s=cur.p.size();
        ll v=cur.val;
        if (v % s != 0) return false;
        v/=s;
        if (v <= lastv) return false;
        lastv=v;
        for (int& po:cur.p)
        {
            a[po]=v;
        }
    }
    for (int& po:events[cnte].p)
    {
        a[po]=lastv+1;
    }
    return true;
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
            cin>>b[i].val;
            b[i].pos=i;
        }
        if (!solve()) cout<<-1<<'\n';
        else
        {
            for (int i=1;i<=n;++i)
                cout<<a[i]<<' ';
            cout<<'\n';
        }
    }
    return 0;
}
