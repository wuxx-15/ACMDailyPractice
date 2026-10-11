#include <iostream>
#define ll long long
using namespace std;
const int MAXN=205;
const ll INF=1e18;
ll arr[MAXN];
int n;
int query(ll x)
{
    cout << "? " << x << endl;
    int sign;
    cin >> sign;
    return sign;
}

void answer()
{
    cout <<'!' << flush;
    for (int i=1;i <= n;++i)
        cout << ' ' << arr[i] << flush;
    cout << endl;
}

void dfs(ll l,ll r,int cnt1,int cnt2)
{
    if (cnt1==cnt2)
        return;
    if (l==r)
    {
        for (int i=cnt1+1;i <=cnt2;++i)
            arr[i]=l;
        return;
    }
    ll mid=l+r>>1LL;
    int cnt3=query(mid);
    dfs(l,mid,cnt1,cnt3);
    dfs(mid+1,r,cnt3,cnt2);
}

void solve()
{
    dfs(0,INF,0,n);
    answer();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    solve();
    return 0;
}
