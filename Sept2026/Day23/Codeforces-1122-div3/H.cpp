#include <iostream>
#include <cstring>
using namespace std;
const int MAXN=200005;
int n,m;
int arr[MAXN];
bool emerged[MAXN];
/*
push_front使得元素在时间上递减
越晚到达并执行 push_front 的元素，其数值必须越小
push_back使得元素在时间上递增
越晚到达并执行 push_back 的元素，其数值必须越大。
来到一个位置时，设此时的值为x，为形成LDS(push_front)LDS必须接一个比 x 小的元素
为形成LIS(push_back)LIS必须接一个比 x 大的元素
*/
int suf_LIS[MAXN]; 
int pre_LDS[MAXN]; 

int lowbit(int i)
{
    return i & (-i);
}

void update_pre(int i,int val)
{
    while (i <= n)
    {
        pre_LDS[i]=max(pre_LDS[i],val);
        i += lowbit(i);
    }
}

int query_pre(int i)
{
    int ans=0;
    while (i > 0)
    {
        ans=max(ans,pre_LDS[i]);
        i -= lowbit(i);
    }
    return ans;
}

//注意这里维护后缀最大值，因此倒置树状数组
void update_suf(int i,int val)
{
    while (i > 0)
    {
        suf_LIS[i]=max(suf_LIS[i],val);
        i -= lowbit(i);
    }
}

int query_suf(int i)
{
    int ans=0;
    while (i <= n)
    {
        ans=max(ans,suf_LIS[i]);
        i += lowbit(i);
    }
    return ans;
}

int dp_dec[MAXN];
int dp_inc[MAXN];
/*
当想把v push_front时，任何 ≤v时元素之前不能入队
当想把v push_back时，任何 ≥v时元素之前不能入队
*/
int bound_L[MAXN];
int bound_R[MAXN];
int last[MAXN];

int solve()
{
    memset(emerged,0,sizeof(bool)*(n+1));
    for(int i=1;i<=m;++i)
    {
        emerged[arr[i]]=true;
        last[arr[i]]=i;
    }
    for (int i=1;i<=n;++i)
    {
        if (!emerged[i])
            return -1;
    }

    bound_L[1]=last[1];
    for (int i=2;i<=n;++i)
        bound_L[i]=min(bound_L[i-1],last[i]);
    bound_R[n]=last[n];
    for (int i=n-1;i>=1;--i)
        bound_R[i]=min(bound_R[i+1],last[i]);

    memset(suf_LIS,0,sizeof(int)*(n+2));
    memset(pre_LDS,0,sizeof(int)*(n+2));
    memset(dp_dec,0,sizeof(int)*(n+2));
    memset(dp_inc,0,sizeof(int)*(n+2));
    for (int i=m;i>=1;--i)
    {
        int v=arr[i];
        if (i <= bound_L[v])
        {
            int val_dec=query_pre(v-1)+1;
            dp_dec[v]=max(dp_dec[v],val_dec);
            update_pre(v,val_dec);
        }

        if (i <= bound_R[v])
        {
            int val_inc=query_suf(v+1)+1;
            dp_inc[v]=max(dp_inc[v],val_inc);
            update_suf(v,val_inc);
        }
    }
    for (int i=2;i<=n;++i)
        dp_dec[i]=max(dp_dec[i],dp_dec[i-1]);
    for (int i=n-1;i>=1;--i)
        dp_inc[i]=max(dp_inc[i],dp_inc[i+1]);
    int max_free=0;
    for (int v=0;v<=n;++v)
    {
        int cur=dp_dec[v]+dp_inc[v+1];
        max_free=max(max_free,cur);
    }
    return n-max_free;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i=1;i<=m;++i)
            cin >> arr[i];
        int ans=solve();
        cout<<ans<<'\n';
    }
    return 0;
}
