#include <iostream>
using namespace std;
const int MAXN=500001;
int n;
int arr[MAXN];

int dp[MAXN];

int treemax[MAXN];

int lowbit(int i)
{
    return i & (-i);
}

void update(int i,int v)
{
    while (i < n)
    {
        treemax[i]=max(treemax[i],v);
        i+=lowbit(i);
    }
}

int query(int i)
{
    int ret=0;
    while (i > 0)
    {
        ret=max(ret,treemax[i]);
        i-=lowbit(i);
    }
    return ret;
}

int compute()
{
    int premax=0;
    int ret1=0;
    for (int i=1;i<=n;++i)
    {
        //x负责吸收前缀最大值
        if (arr[i]>premax)
        {
            premax=arr[i];
            ++ret1;
        }
        //处理LIS
        else
        {
            dp[i]=query(arr[i]-1)+1;
            update(arr[i],dp[i]);
        }
    }
    int ret2=0;
    for (int i=1;i<=n;++i)
        ret2=max(ret2,dp[i]);
    return ret1+ret2;
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
