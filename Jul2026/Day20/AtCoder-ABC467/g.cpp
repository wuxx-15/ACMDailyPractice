//树套树（外层：树状数组，内层：开点线段树）
//时间复杂度O((n+q)*log n*log m) m=cnts
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=100001;
const int MAXS=200001;
const int MAXT=300*MAXS;
const int BIT=20;

int n,q;
int arr[MAXN];
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sizes[MAXT];
ll sum_d[MAXT];
int cntu=0; //分配线段树节点

int sorted[MAXS]; //离散化
int cnts;

int rNodes[BIT];
int lNodes[BIT];
int cntl,cntr;

struct Event
{
    int c,x,l,r;
    ll k;
};

Event events[MAXN];

int lowbit(int i)
{
    return i & (-i);
}

int getRank(int x)
{
    int l=1;
    int r=cnts;
    int mid;
    while (l <= r)
    {
        mid=l+r>>1;
        if (sorted[mid]==x) return mid;
        else if (sorted[mid]>x) r=mid-1;
        else l=mid+1;
    }
    return -1;
}

void up(int i)
{
    sizes[i]=sizes[ls[i]]+sizes[rs[i]];
    sum_d[i]=sum_d[ls[i]]+sum_d[rs[i]];
}

void inner_add(int jobi,int v,int l,int r,int i)
{
    if (l==r)
    {
        sizes[i]+=v;
        sum_d[i]+=v*sorted[l];
    }
    else
    {
        int mid=l+r>>1;
        if (mid >= jobi)
        {
            if (ls[i]==0) ls[i]=++cntu;
            inner_add(jobi,v,l,mid,ls[i]);
        }
        else
        {
            if (rs[i]==0) rs[i]=++cntu;
            inner_add(jobi,v,mid+1,r,rs[i]);
        }
        up(i);
    }
}

void outer_initialize(int i)
{
    int pos=getRank(arr[i]);
    while (i <= n)
    {
        inner_add(pos,1,1,cnts,root[i]);
        i+=lowbit(i);
    }
}

void outer_update(int c,int x)
{
    int old_pos=getRank(arr[c]);
    int new_pos=getRank(x);
    arr[c]=x;
    while (c <= n)
    {
        inner_add(old_pos,-1,1,cnts,root[c]);
        inner_add(new_pos,1,1,cnts,root[c]);
        c+=lowbit(c);
    }
}

//同步游走
ll lsum()
{
    ll ret=0;
    for (int i=1;i<=cntl;++i) 
        ret+=sum_d[lNodes[i]];
    return ret;
}

ll lrssum()
{
    ll ret=0;
    for (int i=1;i<=cntl;++i)
    {
        ret+=sum_d[rs[lNodes[i]]];
    }
    return ret;
}

int lrssize()
{
    int ret=0;
    for (int i=1;i<=cntl;++i)
    {
        ret+=sizes[rs[lNodes[i]]];
    }
    return ret;
}

ll rsum()
{
    ll ret=0;
    for (int i=1;i<=cntr;++i)
        ret+=sum_d[rNodes[i]];
    return ret;
}

ll rrssum()
{
    ll ret=0;
    for (int i=1;i<=cntr;++i)
        ret+=sum_d[rs[rNodes[i]]];
    return ret;
}

int rrsize()
{
    int ret=0;
    for (int i=1;i<=cntr;++i)
        ret+=sizes[rs[rNodes[i]]];
    return ret;
}

void toNext(bool right)
{
    if (right)
    {
        for (int i=1;i<=cntl;++i)
            lNodes[i]=rs[lNodes[i]];
        for (int i=1;i<=cntr;++i)
            rNodes[i]=rs[rNodes[i]];
    }
    else
    {
        for (int i=1;i<=cntl;++i)
            lNodes[i]=ls[lNodes[i]];
        for (int i=1;i<=cntr;++i)
            rNodes[i]=ls[rNodes[i]];
    }
}

int inner_query(ll k,int l,int r)
{
    if (l==r)
    {
        return (k+sorted[l]-1)/sorted[l];
    }
    else
    {
        int mid=l+r>>1;
        ll rd=rrssum()-lrssum();
        int ret;
        if (rd >= k)
        {
            toNext(true);
            ret=inner_query(k,mid+1,r);
        }
        else
        {
            ret=rrsize()-lrssize();
            toNext(false);
            ret+=inner_query(k-rd,l,mid);
        }
        return ret;
    }
}

int outer_query(int l,int r,ll k)
{
    cntl=cntr=0;
    //收集树状数组的前缀节点
    for (int i=l-1;i>0;i-=lowbit(i)) lNodes[++cntl]=root[i];
    for (int i=r;i>0;i-=lowbit(i)) rNodes[++cntr]=root[i];

    if (rsum()-lsum()<k) return -1;

    return inner_query(k,1,cnts);
}

void prepare()
{
    sort(sorted+1,sorted+cnts+1);
    int tmp=1;
    for (int i=2;i<=cnts;++i)
    {
        if (sorted[i] != sorted[tmp])
            sorted[++tmp]=sorted[i];
    }
    cnts=tmp;
    for (int i=0;i<=n;++i) root[i]=++cntu;
    for (int i=1,kth;i<=n;++i)
    {
        outer_initialize(i);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>q;
    for (int i=1;i<=n;++i)
    {
        cin>>arr[i];
        sorted[++cnts]=arr[i];
    }
    for (int i=1;i<=q;++i)
    {
        cin>>events[i].c>>events[i].x>>events[i].l>>events[i].r>>events[i].k;
        sorted[++cnts]=events[i].x;
    }
    prepare();
    for (int i=1;i<=q;++i)
    {
        outer_update(events[i].c,events[i].x);
        cout<<outer_query(events[i].l,events[i].r,events[i].k)<<'\n';
    }
    return 0;
}
