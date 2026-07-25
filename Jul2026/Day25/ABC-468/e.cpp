#include <iostream>
#define ll long long
using namespace std;
const ll MOD=998'244'353;
const int MAXN=500001;
int n;
ll arr[MAXN];
ll presum[MAXN];
ll dsum[MAXN];
ll inv[MAXN];

void prepare()
{
    inv[1]=1;
    for (int i=2;i<=n;++i)
    {
        inv[i]=MOD-inv[MOD%i]*(MOD/i)%MOD;
    }
    for (int i=1;i<=n;++i)
    {
        presum[i]=(presum[i-1]+arr[i])%MOD;
    }
    for (int i=1;i<=n;++i)
    {
        dsum[i]=(dsum[i-1]+presum[i])%MOD;
    }
}

ll compute()
{
    ll ret=0;
    //按照区间长度计算
    for (int i=1;i<=n;++i)
    {
        ret=(ret+(dsum[n]-dsum[i-1]-dsum[n-i]+2*MOD)
        %MOD*inv[i]%MOD)%MOD;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for (int i=1;i<=n;++i)
    {
        cin>>arr[i];
    }
    prepare();
    cout<<compute();
    return 0;
}
