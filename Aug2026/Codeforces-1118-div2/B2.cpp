#include <iostream>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=200005;
int n,m;
ll cnt[MAXN];
ll ans[MAXN];
ll presum[MAXN];
ll total[MAXN];
ll sufmax[MAXN];
ll query_sum(int x)
{
    if (x > m)
        return 0;
    return presum[m] - presum[x - 1];
}

/*
依次在pow(2,k-1)L,pow(2,k-2)L,...L 的位置切下机器。
*/
void solve() 
{
    memset(presum,0,sizeof(ll)*(m+2));
    for (int i = 1; i <= m; ++i) 
        presum[i] = presum[i - 1] + cnt[i];

    memset(total,0,sizeof(ll)*(m+2));
    for (int l = 1; l <= m; ++l) 
    {
        for (int c = 1; c * l <= m; ++c) 
        {
            total[l] += query_sum(c * l);
        }
    }

    memset(sufmax,0,sizeof(ll)*(m+2));
    for (int l = m; l >= 1; --l) 
        sufmax[l] = max(sufmax[l + 1], total[l]);

    for (int k = 1; k <= m; ++k) 
    {
        if (k >= 20 || (1LL << k) > m) 
            ans[k] = sufmax[1];
        else 
        {
            ll cur = 0;
            ll p2 = 1LL << k;
            int limit = m / p2;

            if (limit + 1 <= m) //操作数溢出
                cur = sufmax[limit + 1];
            for (int l = 1; l <= limit; ++l) 
            {
                ll y = 0;
                for (int c = 1; c < p2; ++c) //>=c*L的胡萝卜都贡献一度
                    y += query_sum(c * l);
                y += cnt[p2 * l];  //长度为pow(2,k)*L的胡萝卜额外贡献一段 
                cur = max(cur, y);
            }
            ans[k] = cur;
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin>>T;
    while (T--)
    {
        cin >> n >> m;
        memset(cnt,0,sizeof(ll)*(m+2));
        for (int i = 0,v; i < n; ++i)
        {
            cin >> v;
                ++cnt[v];
        }
        solve();
        for (int k = 1; k <= m; ++k) 
            cout << ans[k] << " ";
        cout << "\n";
    }
    return 0;
}
