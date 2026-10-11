#include <iostream>
#include <vector>
using namespace std;
const int MAXN=45;
const int MAXK=800;
int arr[MAXN];
int base[MAXN];
int cnts;
int n,b,k;

struct Node
{
    vector<int> segment;
    bool flag=false;
};

Node dp[MAXN][MAXN][MAXK];

bool solve()
{
    for (int i=1;i <= n;++i)
        base[i]=i*(i-1)/2;
    dp[0][n][k].flag=true;
    for (int i=1;i <= b;++i)
    {
        for (int rem=0;rem <= n;++rem)
        {
            for (int s=0;s <= k;++s)
            {
                for (int len=1;len <= n;++len)
                {
                    int cost=base[len];
                    if (s + cost > k || rem + len > n)
                        break;
                    if (!dp[i-1][rem+len][s+cost].flag)
                        continue;
                    dp[i][rem][s].segment=dp[i-1][rem+len][s+cost].segment;
                    dp[i][rem][s].segment.push_back(len);
                    dp[i][rem][s].flag=true;
                }
            }
        }
    }

    if (!dp[b][0][0].flag)
        return false;
    auto& vec=dp[b][0][0].segment;
    int st=1;
    int cntv=0;
    for (int len : vec)
    {
        int maxv=st+len-1;
        for (int v=maxv;v >= st;--v)
            arr[++cntv]=v;
        st+=len;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> b >> k;
    if (solve())
    {
        for (int len : dp[b][0][0].segment)
            cout << len <<  '\n';
        for (int i=1;i <= n;++i)
            cout << arr[i] << ' ';
        cout << '\n';
    }
    else 
        cout << "IMPOSSIBLE";
    return 0;
}
