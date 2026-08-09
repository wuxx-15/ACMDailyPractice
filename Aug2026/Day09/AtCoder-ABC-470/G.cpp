#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const int MAXN=300005;

int n;
int arr[MAXN];
vector<int> pos[MAXN];

//SegmentTree Beats
int maxv[MAXN<<2];
int subv[MAXN<<2]; //严格次大值（不能等于最大值）
int maxcnt[MAXN<<2];
ll sum[MAXN<<2]; 

void up(int i)
{
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    if (maxv[l]==maxv[r])
    {
        maxv[i]=maxv[l];
        maxcnt[i]=maxcnt[l]+maxcnt[r];
        subv[i]=max(subv[l],subv[r]);
    }
    else if (maxv[l]>maxv[r])
    {
        maxv[i]=maxv[l];
        maxcnt[i]=maxcnt[l];
        subv[i]=max(subv[l],maxv[r]);
    }
    else
    {
        maxv[i]=maxv[r];
        maxcnt[i]=maxcnt[r];
        subv[i]=max(maxv[l],subv[r]);
    }
}

void build(int l,int r,int i)
{
    if (l==r)
    {
        maxv[i]=l;
        subv[i]=-1;
        maxcnt[i]=1;
        sum[i]=l;
    }
    else
    {
        int mid=l+r>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

//只修改最大值，不修改严格次大值(Beats过程)
void chmin(int ceil,int i)
{
    if (maxv[i]<=ceil)
        return;
    sum[i]-=1ll*(maxv[i]-ceil)*maxcnt[i];
    maxv[i]=ceil;
}

void down(int i)
{
    int ceil=maxv[i];
    if (maxv[i<<1]>ceil)
        chmin(ceil,i<<1);
    if (maxv[i<<1|1]>ceil)
        chmin(ceil,i<<1|1);
}

void range_chmin(int jobl,int jobr,int ceil,int l,int r,int i)
{
    if (l > jobr || r < jobl || maxv[i]<=ceil)
        return;
    if (l >= jobl && r <= jobr && subv[i] < ceil)
    {
        chmin(ceil,i);
        return;
    }
    down(i);
    int mid=l+r>>1;
    range_chmin(jobl,jobr,ceil,l,mid,i<<1);
    range_chmin(jobl,jobr,ceil,mid+1,r,i<<1|1);
    up(i);
}

/*
首先，对于区间B,mex(B)=sum [mex(B) >= k] (k >= 1)
(1<=k<=n,中括号里的式子成立时值为1，否则为0，可理解为bool类型)
这样将"区间的mex为k"转化成了mex至少为k"
mex(B)>=k等价于区间B内同时出现了0,1,...,k-1

令last[x][r]为x在前缀a[1:r]中最后出现的位置
为了让[l,r]同时包含0,1,...,x，必须满足
l <= last[i][r] (0 <= i <= x)
合法的左端点数量为H[x][r]=min last[v][r] (0 <= v <= x)
同时包含0,1,...,x的区间总数为sum H[x][r] (r >= 1)
答案为sum (sum H[x][r](1<=r<=n)) (0<=x<=1)

加入新的值x后,H(r)=min(H(r),last[x][r])
假设x出现位置为p1<p2<...<pm (补充p0=0,p[m+1]=n)
那么last[x][r]=p[i] (p[i]<=r<p[i+1],0<=i<=m)
所以需要:
chmin(1,p1-1,0)
chmin(p1,p2-1,p1)
......
chmin(pm,n,pm)
(把H(r)削减得不能超过last[x][r])

sum数组维护 H(r) (1<=r<=n,r为子数组右端点) 
对于叶节点,sum值有如上含义
父节点则可以表示其叶节点H(r)值的和(向上汇总)
*/

ll compute()
{
    for (int i=1,v;i<=n;++i)
    {
        v=arr[i];
        if (v < n)
            pos[v].push_back(i);
    }
    ll ans=0;
    build(1,n,1);
    //枚举mex值
    for (int x=0;x<n;++x)
    {
        int prev=0;
        //枚举x出现的位置
        for (int p:pos[x])
        {
            int left=max(1,prev);
            if (left <= p-1)
                range_chmin(left,p-1,prev,1,n,1); 
            prev=p;
        }
        int left=max(1,prev);
        if (left<=n)
            range_chmin(left,n,prev,1,n,1);
        ans+=sum[1];
        if (sum[1]==0)
            break;
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
        cin>>arr[i];
    cout<<compute();
    return 0;
}
