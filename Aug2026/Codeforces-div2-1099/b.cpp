#include <iostream>
#include <climits>
#include <cstring>
using namespace std;
const int MAXN=200005;
int arr[MAXN];
//0:不加，1:加
bool dp[MAXN][2];
int n;
bool solve()
{
    int k=0;
    for (int i=2;i<=n;++i)
    {
        if (arr[i]<arr[i-1])
            k=max(k,arr[i-1]-arr[i]);
    }
    memset(dp,0,sizeof(dp));
    dp[1][0]=dp[1][1]=true;
    for (int i=2;i<=n;++i)
    {
        if (arr[i]>=arr[i-1])
        {
            dp[i][0] |= dp[i-1][0];
            if (arr[i]>=arr[i-1]+k)
                dp[i][0] |= dp[i-1][1];
        }
        if (arr[i]+k>=arr[i-1])
        {
            dp[i][1] |= dp[i-1][0];
            if (arr[i]+k>=arr[i-1]+k)
                dp[i][1] |= dp[i-1][1];
        }
    }
    return dp[n][0] || dp[n][1];
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
        for (int i=1;i<=n;++i)
            cin>>arr[i];
        arr[n+1]=INT_MAX;
        if (solve()) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
