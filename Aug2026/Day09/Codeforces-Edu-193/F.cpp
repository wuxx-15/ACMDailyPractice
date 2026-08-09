#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAXN = 500005;
const int MASK = 1 << 19;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXS = 385;
ll m[MAXN];
int pow2[20];
int pow3[14];
int n;

void prepare()
{
    pow2[0] = 1;
    for (int i = 1; i < 20; ++i)
        pow2[i] = pow2[i - 1] * 2;
    pow3[0] = 1;
    for (int i = 1; i < 14; ++i)
        pow3[i] = pow3[i - 1] * 3;
}

ll dp[MASK]; //必须用滚动数组，把pos这一维去掉，不然MLE
ll Next[MASK];

/*
目标，消除所有(d,2d,3d,4d)四元组
任意一个数num=x*pow(2,p)*pow(3,q) (gcd(x,6)==1)
用位图存储最近W个格子的保留状态(1为保留，0为不保留)
处理当前格子 (q,p) 时，它可能是某个四元组中的 3d：
d=(q−1,p).
此时四元组另外三个位置是
(q−1,p),(q−1,p+1),(q−1,p+2).
在处理当前格子之前，这三个状态恰好分别位于 mask 的：
W−1,W−2,W−3位。
*/

ll Calc_DP(int b)
{
    int row = 0;
    int col = 0;
    while (b * pow2[row] <= n)
        ++row; // 2的最高次幂
    while (b * pow3[col] <= n)
        ++col; // 3的最高次幂
    if (row < 3 || col < 2)
        return 0;
    int states = 1 << row;
    int fullMask = states - 1;
    int cells = row * col;

    memset(dp, 0x3f, sizeof(ll) * states);
    memset(Next, 0x3f, sizeof(ll) * states);
    dp[0] = 0;

    for (int pos = 0; pos < cells; ++pos)
    {
        int c = pos / row;
        int r = pos % row;
        ll val = 1ll * b * pow2[r] * pow3[c];
        for (int mask = 0; mask < states; ++mask)
        {
            if (dp[mask] == INF)
                continue;
            int shifted = (mask << 1) & fullMask;

            // 不存在的格子设为不保留
            if (val > n)
            {
                Next[shifted] = min(Next[shifted], dp[mask]);
                continue;
            }

            Next[shifted] = min(Next[shifted], dp[mask] + m[val]);
            // 判断保留格子是否会产生非法四元组
            bool illegal = false;
            if (c > 0 && r + 2 < row)
            {
                bool keepD = (mask >> row - 1) & 1;
                bool keep2D = (mask >> row - 2) & 1;
                bool keep4D = (mask >> row - 3) & 1;

                if (keepD && keep2D && keep4D)
                    illegal = true;
            }

            if (!illegal)
            {
                Next[shifted | 1] = min(Next[shifted | 1], dp[mask]);
            }
        }
        memcpy(dp, Next, sizeof(ll) * states);
        memset(Next, 0x3f, sizeof(ll) * states);
    }
    ll ans = INF;
    for (int mask = 0; mask < states; ++mask)
        ans = min(ans, dp[mask]);
    return ans;
}

ll compute()
{
    prepare();
    ll ans = 0;
    for (int b = 1; b <= n / 4; ++b)
    {
        if (b % 2 != 0 && b % 3 != 0)
            ans += Calc_DP(b);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> m[i];
    cout << compute();
    return 0;
}
