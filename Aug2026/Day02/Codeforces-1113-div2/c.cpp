#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
#define ll long long
using namespace std;
const int MAXN=200005;
int n,len;
int arr[MAXN<<1];
int pos[MAXN][2];
ll dist[MAXN];

ll dp[MAXN<<1];
ll compute()
{
    dp[len+1]=0;
    dp[len]=1;
    for (int i=len-1,v;i>=1;--i)
    {
        v=arr[i];
        if (pos[v][0]==i)
        {
            //贪心选距离最大的
            dp[i]=max(dp[pos[v][1]+1]+1ll*(dist[v]+1)*(dist[v]+1)
            ,dp[i+1]+1);
        }
        else
        {
            dp[i]=dp[i+1]+1;
        }
    }
    return dp[1];
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
        memset(pos,0,sizeof(pos));
        cin>>n;
        len=2*n;
        for (int i=1,v;i<=len;++i)
        {
            cin>>v;
            arr[i]=v;
            if (pos[v][0]==0) 
            {
                pos[v][0]=i;
            }
            else 
            {
                pos[v][1]=i;
                dist[v]=pos[v][1]-pos[v][0];
            }
        }
        cout<<compute()<<'\n';
    }
    return 0;
}
