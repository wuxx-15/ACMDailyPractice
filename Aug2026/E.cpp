#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define ll long long
using namespace std;
const int MAXN=210000;
int n;
int arr[MAXN];
int PrimePower[MAXN<<1];
int cnt=0;
bool isPrime[MAXN];
vector<int> divisors[MAXN];

bool visited[MAXN];
int ans[MAXN];
int cntAns;

void init()
{
    PrimePower[++cnt]=1;
    fill(isPrime+2,isPrime+MAXN,1);
    for (int i=2;i<MAXN;++i)
    {
        if (!isPrime[i])
            continue;
        for (ll j=i;j<MAXN;j*=i)
            PrimePower[++cnt]=j;
        for (int j=2*i;j<MAXN;j+=i)
            isPrime[j]=false;
    }
    sort(PrimePower+1,PrimePower+cnt+1);
    int backup=cnt;
    cnt=1;
    for (int i=2;i<=backup;++i)
    {
        if (PrimePower[i] != PrimePower[cnt])
            PrimePower[++cnt]=PrimePower[i];
    }
    for (int i=2;i<=cnt;++i)
    {
        int v=PrimePower[i];
        for (int j=v;j<MAXN;j+=v)
            divisors[j].push_back(i);
    }
}
/*
f(i,j)(1≤i<j≤n)一定是质数幂
定义last[q] 表示当前扫描位置之前，最近一次满足
q | a[j]的位置 j，其中 q 是质数幂
线段树维护前缀最小值
*/
int minlast[MAXN<<2];

void up(int i)
{
    minlast[i]=min(minlast[i<<1],minlast[i<<1|1]);
}

void update(int jobi,int jobv,int l,int r,int i)
{
    if (l==r)
        minlast[i]=jobv;
    else
    {
        int mid=l+r>>1;
        if (mid >= jobi)
            update(jobi,jobv,l,mid,i<<1);
        else
            update(jobi,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

int query_min(int jobl,int jobr,int l,int r,int i)
{
    if (l >= jobl && r <= jobr)
        return minlast[i];
    else
    {
        int mid=l+r>>1;
        int ans1=MAXN;
        int ans2=MAXN;
        if (mid >= jobl)
            ans1=query_min(jobl,jobr,l,mid,i<<1);
        if (mid < jobr)
            ans2=query_min(jobl,jobr,mid+1,r,i<<1|1);
        return min(ans1,ans2);
    }
}

int query_single(int jobi,int l,int r,int i)
{
    if (l==r)
        return minlast[i];
    else
    {
        int mid=l+r>>1;
        if (mid >= jobi)
            return query_single(jobi,l,mid,i<<1);
        else
            return query_single(jobi,mid+1,r,i<<1|1);
    }
}

int bs(int x)
{
    int l=1;
    int r=cnt;
    int mid;
    int ans=0;
    while (l <= r)
    {
        mid=l+r>>1;
        if (PrimePower[mid]>x)
        {
            ans=mid;
            r=mid-1;
        }
        else
            l=mid+1;
    }
    return ans;
}

void solve()
{
    int maxp=bs(n);
    memset(minlast,0,sizeof(int)*(4*maxp+1));
    memset(visited,0,sizeof(bool)*(maxp+1));
    cntAns=0;
    for (int i=1;i<=n;++i)
    {
        int v=arr[i];
        for (int d:divisors[v]) //只枚举质数幂因子（障碍物）
        {
            if (visited[d])
                continue;
            int l1=query_min(1,d-1,1,maxp,1);
            int l2=query_single(d,1,maxp,1);
            if (l1 > l2)
            {  
                visited[d]=true;
                ans[++cntAns]=PrimePower[d];
            }
        }
        update(1,i,1,maxp,1);
        for (int d:divisors[v])
            update(d,i,1,maxp,1);
    }
    for (int x=2;x<=maxp;++x) //末尾全面检查可行值
    {
        int l1=query_min(1,x-1,1,maxp,1);
        int l2=query_single(x,1,maxp,1);
        if (l1 > l2)
        {
            if (!visited[x])
                ans[++cntAns]=PrimePower[x];
        }
    }
    sort(ans+1,ans+cntAns+1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    int T;
    cin>>T;
    while (T--)
    {
        cin>>n;
        for (int i=1;i<=n;++i)
            cin>>arr[i];
        solve();
        cout<<cntAns<<'\n';
        for (int i=1;i<=cntAns;++i)
            cout<<ans[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
