#include <iostream>
#include <set>
#define ll long long
using namespace std;
const int MAXN=200005;
ll a[MAXN];
ll b[MAXN];
int n;

multiset<ll> s;

bool solve()
{
    s.clear();
    for (int i=1;i<=n;++i)
        s.insert(b[i]);
    a[0]=0;
    for (int i=1;i<=n;++i)
    {
        auto it=s.upper_bound(-a[i-1]);
        if (it==s.end()) return false;
        ll val=*it;
        a[i]=a[i-1]+val;
        s.erase(it);
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
            cin>>b[i];
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
