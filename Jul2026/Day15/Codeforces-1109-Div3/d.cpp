#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=200001;
int n,m;
ll val[MAXN];
ll presum[MAXN];
int impact[MAXN];
ll compute()
{
    for (int i=1;i<=n;++i)
    {
        presum[i]=presum[i-1]+val[i];
    }
    sort(impact+1,impact+m+1);
    ll ret=llabs(presum[impact[1]]);
    for (int i=1;i<m;++i)
    {
        ret+=llabs(presum[impact[i+1]]-presum[impact[i]]);
    }
    ret+=presum[n]-presum[impact[m]];
    return ret;
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
        cin>>n>>m;
        for (int i=1;i<=n;++i) cin>>val[i];
        for (int i=1;i<=m;++i) cin>>impact[i];
        cout<<compute()<<'\n';
    }
    return 0;
}
