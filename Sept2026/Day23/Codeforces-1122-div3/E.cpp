#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAXN=200005;
int n,k;
int arr[MAXN];
ll dp[MAXN];
int primes[MAXN];
int spf[MAXN]; //最小质因子
int cntt;

void Euler()
{
    for (int i=2;i<MAXN;++i)
    {
        if (spf[i]==0)
        {
            spf[i]=i;
            primes[++cntt]=i;
        }
        for (int j=1;j<=cntt;++j)
        {
            if (i*primes[j] >= MAXN)
                break;
            spf[i*primes[j]]=primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

void prepare()
{
    Euler();
    dp[1]=0;
    for (int i=2;i<MAXN;++i)
    {
        int p=spf[i];
        dp[i]=1+p*dp[i/p];
    }
}

int freq[MAXN];
ll cost[MAXN];
ll solve()
{
    memset(freq,0,sizeof(int)*(n+1));
    ll ans=0;
    for (int i=1;i<=n;++i)
    {
        int v=arr[i];
        ++freq[v];
    }
    memset(cost,0x3f,sizeof(ll)*(n+1));
    for (int base=k;base>=1;--base)
    {
        for (int v=base;v <= n;v+=base)
        {
            cost[v]=min(cost[v],dp[v/base]);
        }
    }
    for (int v=1;v<=n;++v)
        ans += freq[v]*cost[v];
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    prepare();
    while (T--)
    {
        cin >> n >> k;
        for (int i=1;i<=n;++i)
            cin >> arr[i];
        ll ans=solve();
        cout<<ans<<'\n';
    }
    return 0;
}
