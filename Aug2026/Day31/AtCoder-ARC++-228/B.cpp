#include <iostream>
#define ll long long
using namespace std;
const int MAXN=200005;
const ll INF=1e18;
int n;
ll arr[MAXN];
int p[MAXN];
int prior[MAXN];
int childcnt[MAXN];
ll minv[MAXN<<2]; //区间代价最小值
int midx[MAXN<<2]; //最小值所在索引

void up(int i)
{
    int l=i<<1;
    int r=i<<1|1;
    if (minv[l]<=minv[r])
    {
        minv[i]=minv[l];
        midx[i]=midx[l];
    }
    else
    {
        minv[i]=minv[r];
        midx[i]=midx[r];
    }
}

void build(int l,int r,int i)
{
    if (l==r)
    {
        int idx=p[l];
        minv[i]=arr[idx];
        midx[i]=idx;
    }
    else
    {
        int mid=l+r>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobi,ll jobv,int l,int r,int i)
{
    if (l==r)
        minv[i]=jobv;
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

void query_min(int jobl,int jobr,int l,int r,int i,ll& val,int& idx)
{
    if (l>=jobl && r <= jobr)
    {
        if (minv[i]<val)
        {
            val=minv[i];
            idx=midx[i];
        }
    }
    else
    {
        int mid=l+r>>1;
        if (mid >= jobl)
            query_min(jobl,jobr,l,mid,i<<1,val,idx);
        if (mid < jobr)
            query_min(jobl,jobr,mid+1,r,i<<1|1,val,idx);
    }
}
int Stack[MAXN];

ll solve()
{
    build(1,n,1);
    ll ans=0;
    int pos=0;
    Stack[++pos]=p[1];
    for (int i=2;i<=n;++i)
    {
        int cur=p[i];
        while (pos > 0 && Stack[pos]<cur)
            --pos;
        int lidx=1;
        if (pos != 0)
            lidx=prior[Stack[pos]];
        ll val=INF;
        int idx=0;
        query_min(lidx,i-1,1,n,1,val,idx);
        ans+=val;
        int& c=childcnt[idx];
        ++c;
        ll ncost=arr[idx]*(2*c+1);
        update(prior[idx],ncost,1,n,1);
        Stack[++pos]=cur;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for (int i=1;i<=n;++i)
    {
        cin>>p[i];
        prior[p[i]]=i;
    }
    for (int i=1;i<=n;++i)
        cin>>arr[i];
    ll ans=solve();
    cout<<ans;
    return 0;
}
/*
局部贪心为什么对：
    节点可选择的区间不会交叉，只会不相交或包含
*/
