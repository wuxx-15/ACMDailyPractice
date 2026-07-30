#include <iostream>
#include <algorithm>
#include <cstring>
#define ull unsigned long long
using namespace std;
const int MAXN=200001;
const int MAXK=62;
const int INF=0x3f3f3f3f;
ull arr[MAXN];
ull sorted[MAXN];
int Rank[MAXN];
int cnts=0;
int n,q;
int total_k;

// 第一个元素必须选择a[i]时，构造一个长度为k的好子序列，最早能在哪个位置结束。
int dp[MAXK][MAXN];
//DP后缀最小值
int sufMin[MAXK][MAXN];

int treemin[MAXN<<2];

void up(int i)
{
    treemin[i]=min(treemin[i<<1],treemin[i<<1|1]);
}

void insert(int jobi,int jobv,int l,int r,int i)
{
    if (l==r) treemin[i]=min(treemin[i],jobv);
    else
    {
        int mid=l+r>>1;
        if (mid >= jobi) insert(jobi,jobv,l,mid,i<<1);
        else insert(jobi,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i)
{
    if (l >= jobl && r <= jobr) return treemin[i];
    else
    {
        int ret=INF;
        int mid=l+r>>1;
        if (mid >= jobl) ret=min(ret,query(jobl,jobr,l,mid,i<<1));
        if (mid < jobr) ret=min(ret,query(jobl,jobr,mid+1,r,i<<1|1));
        return ret;
    }
}

int upper(ull num)
{
    int l=1;
    int r=cnts;
    int mid;
    int ret=cnts+1;
    while (l <= r)
    {
        mid=l+r>>1;
        if (sorted[mid]>=num)
        {
            ret=mid;
            r=mid-1;
        }
        else
            l=mid+1;
    }
    return ret;
}

int lower(ull num)
{
    int l=1;
    int r=cnts;
    int mid;
    int ret=0;
    while (l<=r)
    {
        mid=l+r>>1;
        if (sorted[mid]<=num)
        {
            ret=mid;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return ret;
}

int lb[MAXN];
int rb[MAXN];

void prepare()
{
    sort(sorted+1,sorted+n+1);
    cnts=1;
    for (int i=2;i<=n;++i)
    {
        if (sorted[i] != sorted[cnts])
            sorted[++cnts]=sorted[i];
    }
    for (int i=1;i<=n;++i)
    {
        Rank[i]=upper(arr[i]);
        lb[i]=upper(2*arr[i]);
        rb[i]=lower(3*arr[i]);
    }
    memset(dp,INF,sizeof(dp));
    memset(sufMin,INF,sizeof(sufMin));
    for (int i=1;i<=n;++i)
        dp[1][i]=sufMin[1][i]=i;
    for (int k=2;k<=total_k;++k)
    {
        memset(treemin,INF,sizeof(treemin));
        insert(Rank[n-k+2],dp[k-1][n-k+2],1,cnts,1);
        for (int i=n-k+1;i>=1;--i)
        {
            int l=lb[i];
            int r=rb[i];
            if (l <= r)
                dp[k][i]=query(l,r,1,cnts,1);
            sufMin[k][i]=min(sufMin[k][i+1],dp[k][i]);
            insert(Rank[i],dp[k-1][i],1,cnts,1);
        }
    }
}

int compute(int lb,int rb)
{
    int l=1,r=total_k;
    int mid;
    int ret=1;
    while (l <= r)
    {
        mid=l+r>>1;
        if (sufMin[mid][lb]<=rb)
        {
            ret=mid;
            l=mid+1;
        }
        else 
        {
            r=mid-1;
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>q;
    total_k=min(n,60);
    for (int i=1;i<=n;++i)
    {
        cin>>arr[i];
        sorted[++cnts]=arr[i];
    }
    prepare();
    int l,r;
    while (q--)
    {
        cin>>l>>r;
        cout<<compute(l,r)<<'\n';
    }
    return 0;
}
