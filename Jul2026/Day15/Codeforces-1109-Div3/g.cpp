//若i > j
//i >= j + nums[j] + 1
//j <= i - nums[i] + 1
//用树状数组优化枚举，时间复杂度O(n*log n)
#include <iostream>
#include <array>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=200001;
int n;
ll nums[MAXN];
ll dp[MAXN]; //以nums[i]结尾时最大值
array<array<int,2>,MAXN> events;//解锁索引，解锁时间
int cnte;
bool cmp(const array<int,2>& a1,const array<int,2>& a2)
{
    return a1[1]<a2[1];
}
//FenwickTree
ll max_val[MAXN];
int lowbit(int i)
{
    return i & (-i);
}
void add(int i,ll v)
{
    while (i <= n)
    {
        max_val[i]=max(max_val[i],v);
        i+=lowbit(i);
    }
}
ll query_max(int i) //查询区间[1,i]上dp最大值
{
    ll ret=0;
    while (i > 0)
    {
        ret=max(ret,max_val[i]);
        i-=lowbit(i);
    }
    return ret;
}
ll compute()
{
    cnte=0;
    for (int i=1;i<=n;++i)
    {
        if (i+nums[i]+1<=n) 
        {
            events[++cnte][0]=i;
            events[cnte][1]=i+nums[i]+1;
        }
    }
    dp[1]=nums[1];
    ll ret=dp[1];
    sort(events.begin()+1,events.begin()+cnte+1,cmp);
    int NextEvent=1;
    for (int i=2;i<=n;++i)
    {
        if (NextEvent<=cnte && events[NextEvent][1]==i)
        {
            add(events[NextEvent][0],dp[events[NextEvent][0]]);
            ++NextEvent;
        }
        dp[i]=nums[i]+query_max(i-nums[i]-1);
        ret=max(ret,dp[i]);
    }
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
        cin>>n;
        for (int i=1;i<=n;++i) cin>>nums[i];
        cout<<compute()<<'\n';
    }
    return 0;
}
