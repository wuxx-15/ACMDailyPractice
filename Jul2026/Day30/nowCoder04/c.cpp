//SOS DP（Sum over Subsets Dynamic Programming，子集和动态规划
#include <iostream>
#include <string>
#include <cstring>
#define ll long long
using namespace std;
const ll INF=2e18;
const int MAXN=20001;
const int MAXM=21;
int n,m;

int d[MAXN][MAXM];
int acceptMask[MAXN];
ll cost[MAXM][1<<MAXM-1]; //评测点，删除评测点后的状态
ll dp[1<<MAXM];

int removeBit(int mask,int p)
{
    int low=mask & ((1<<p)-1);
    int high=mask >> p+1;
    return low | (high << p);
}

ll compute()
{
    int half=1<<m-1;
    for (int j=0;j<m;++j)
    {
        auto& cur=cost[j];
        for (int i=0;i<n;++i)
        {
            int mask=removeBit(acceptMask[i],j);
            cur[mask]+=d[i][j];
        }
        for (int b=0;b<m-1;++b)
        {
            for (int mask=0;mask<half;++mask)
            {
                if (!(mask >> b & 1))
                    cur[mask]+=cur[mask|(1<<b)];
            }
        }
    }
    int total=1<<m;
    for (int i=1;i<total;++i) dp[i]=INF;
    for (int s=0;s<total;++s)
    {
        if (dp[s]==INF) continue;
        int remain=(total-1)^s;
        while (remain)
        {
            int bit=remain & -remain;
            //数尾数0,看最低位1在第几位
            int j = __builtin_ctz(bit);

            int nextState=removeBit(s,j);

            dp[s|bit]=min(dp[s|bit],dp[s]+cost[j][nextState]);
            remain-=bit;
        }
    }
    return dp[total-1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    string str;
    for (int i=0;i<n;++i)
    {
        for (int j=0;j<m;++j)
            cin>>d[i][j];
        cin>>str;
        for (int j=0;j<m;++j)
        {
            if (str[j]=='A')
                acceptMask[i] |= 1<<j;
        }
    }
    cout<<compute();
    return 0;
}
