#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>
#define ll long long
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif
using namespace std;
constexpr int MAXN = 500005;
constexpr ll MOD = 998244353;
constexpr ll G = 3;
constexpr ll GI = 332748118;
//求同一行第一类斯特林数
template <size_t MAX_LEN>
class Poly
{
public:
    ll arr[MAX_LEN << 1];

    Poly() { memset(arr, 0, sizeof(arr)); }

    ll &operator[](int i) { return arr[i]; }
    const ll &operator[](int i) const { return arr[i]; }

    //截断乘法，积传入新对象
    void mul(const Poly &rhs, Poly &out, int n) const
    {
        assert(&out != this && &out != &rhs);
        memset(out.arr, 0, sizeof(out.arr));
        _mul(arr, n, rhs.arr, n, out.arr, n);
    }

    //截断乘法，就地运算
    void mul(const Poly &rhs, int n)
    {
        _mul(arr, n, rhs.arr, n, arr, n);
    }

    //完整乘法，积传入新对象
    void mul(int len_a, const Poly &rhs, int len_b, Poly &out) const
    {
        assert(&out != this && &out != &rhs);
        memset(out.arr, 0, sizeof(out.arr));
        _mul(arr, len_a, rhs.arr, len_b, out.arr, len_a + len_b - 1);
    }

    //完整乘法，就地运算
    void mul(int len_a, const Poly &rhs, int len_b) 
    {
        _mul(arr, len_a, rhs.arr, len_b, arr, len_a + len_b - 1);
    }

    void inv(Poly &out, int n) const
    {
        assert(n >= 1 && arr[0] != 0);
        _inv(arr, out.arr, n);
    }

    void ln(Poly &out, int n) const
    {
        assert(n >= 1 && arr[0] == 1);
        _ln(arr, out.arr, n);
    }

    void ln(int n)
    {
        _ln(arr,arr,n);
    }

    void exp(Poly &out, int n) const
    {
        assert(n >= 1 && arr[0] == 0);
        memset(out.arr, 0, sizeof(out.arr));
        _exp(arr, out.arr, n);
    }

    void exp(int n)
    {
        _exp(arr,arr,n);
    }

private:
    inline static int rev[MAX_LEN << 1];
    inline static ll tmp[MAX_LEN << 1];
    inline static ll deriv[MAX_LEN << 1];
    inline static ll B[MAX_LEN << 1];
    inline static ll tmp_mulA[MAX_LEN << 1];
    inline static ll tmp_mulB[MAX_LEN << 1];

    static ll powq(ll base, int p)
    {
        ll ret = 1;
        while (p > 0)
        {
            if (p & 1)
                ret = ret * base % MOD;
            base = base * base % MOD;
            p >>= 1;
        }
        return ret;
    }

    static void init(int limit)
    {
        if (limit == 1)
        {
            rev[0] = 0;
            return;
        }
        int bits = __builtin_ctz(limit);
        for (int i = 0; i < limit; ++i)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bits - 1));
    }

    static void NTT(ll *a, int n, int op)
    {
        for (int i = 0; i < n; ++i)
        {
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        }
        for (int len = 2; len <= n; len <<= 1)
        {
            ll wn = powq(op == 1 ? G : GI, (MOD - 1) / len);
            for (int l = 0; l < n; l += len)
            {
                ll w = 1;
                for (int k = l; k < l + len / 2; ++k)
                {
                    ll x = a[k];
                    ll y = w * a[k + len / 2] % MOD;
                    a[k] = x + y >= MOD ? x + y - MOD : x + y;
                    a[k + len / 2] = x - y < 0 ? x - y + MOD : x - y;
                    w = w * wn % MOD;
                }
            }
        }
    }

    static void _mul(const ll *a, int len_a, const ll *b, int len_b, ll *res, int res_len)
    {
        int limit = 1;
        while (limit < len_a + len_b - 1)
            limit <<= 1;

        init(limit);
        memset(tmp_mulA, 0, sizeof(ll) * limit);
        memset(tmp_mulB, 0, sizeof(ll) * limit);
        memcpy(tmp_mulA, a, sizeof(ll) * len_a);
        memcpy(tmp_mulB, b, sizeof(ll) * len_b);

        NTT(tmp_mulA, limit, 1);
        NTT(tmp_mulB, limit, 1);
        for (int i = 0; i < limit; ++i)
            tmp_mulA[i] = tmp_mulA[i] * tmp_mulB[i] % MOD;
        NTT(tmp_mulA, limit, -1);

        ll inv_limit = powq(limit, MOD - 2);
        for (int i = 0; i < res_len; ++i)
            res[i] = tmp_mulA[i] * inv_limit % MOD;

        for (int i = res_len; i < limit; ++i)
            res[i] = 0;
    }

    static void _inv(const ll *a, ll *res, int n)
    {
        int cap = 1;
        while (cap < n)
            cap <<= 1;
        memset(res, 0, sizeof(ll) * (cap << 1));
        res[0] = powq(a[0], MOD - 2);
        int len = 1;
        while (len < n)
        {
            len <<= 1;
            int limit = len << 1;
            init(limit);
            memset(tmp, 0, sizeof(ll) * limit);
            memcpy(tmp, a, sizeof(ll) * len);
            NTT(tmp, limit, 1);
            NTT(res, limit, 1);
            for (int i = 0; i < limit; ++i)
                res[i] = (2LL - 1LL * tmp[i] * res[i] % MOD + MOD) * res[i] % MOD;
            NTT(res, limit, -1);
            ll inv_limit = powq(limit, MOD - 2);
            for (int i = 0; i < len; i++)
                res[i] = res[i] * inv_limit % MOD;
            for (int i = len; i < limit; i++)
                res[i] = 0;
        }
    }

    static void _ln(const ll *a, ll *res, int n)
    {
        for (int i = 1; i < n; ++i)
            deriv[i - 1] = a[i] * i % MOD;
        deriv[max(0, n - 1)] = 0;

        _inv(a, res, n);

        int limit = 1;
        while (limit < n * 2)
            limit <<= 1;
        for (int i = n; i < limit; ++i)
            res[i] = 0;
        for (int i = max(0, n - 1); i < limit; ++i)
            deriv[i] = 0;

        init(limit);
        NTT(deriv, limit, 1);
        NTT(res, limit, 1);
        for (int i = 0; i < limit; ++i)
            res[i] = res[i] * deriv[i] % MOD;
        NTT(res, limit, -1);
        ll inv_limit = powq(limit, MOD - 2);
        for (int i = n - 1; i >= 1; --i)
        {
            res[i] = res[i - 1] * inv_limit % MOD;
            res[i] = res[i] * powq(i, MOD - 2) % MOD;
        }
        res[0] = 0;
    }

    static void _exp(const ll *a, ll *res, int n)
    {
        if (n == 1)
        {
            res[0] = 1;
            return;
        }
        int m = (n + 1) >> 1;
        _exp(a, res, m);

        int limit = 1;
        while (limit < n * 2)
            limit <<= 1;
        for (int i = m; i < limit; ++i)
            res[i] = 0;

        _ln(res, B, n);

        memset(tmp, 0, sizeof(ll) * limit);
        for (int i = 0; i < n; ++i)
        {
            tmp[i] = a[i] - B[i];
            if (tmp[i] < 0)
                tmp[i] += MOD;
            if (i == 0)
            {
                if (++tmp[i] >= MOD)
                    tmp[i] -= MOD;
            }
        }
        init(limit);
        NTT(res, limit, 1);
        NTT(tmp, limit, 1);
        for (int i = 0; i < limit; ++i)
            res[i] = res[i] * tmp[i] % MOD;
        NTT(res, limit, -1);
        ll inv_limit = powq(limit, MOD - 2);
        for (int i = 0; i < n; ++i)
            res[i] = res[i] * inv_limit % MOD;
        for (int i = n; i < limit; ++i)
            res[i] = 0;
    }
};

Poly<MAXN> A, B, C, tmp;
int n,k;

ll fac[MAXN];
ll inv_fac[MAXN];

ll powq(ll base, int p)
{
    ll ret = 1;
    while (p > 0)
    {
        if (p & 1)
            ret = ret * base % MOD;
        base = base * base % MOD;
        p >>= 1;
    }
    return ret;
}

ll calc_inv(ll x)
{
    return powq(x, MOD - 2);
}

void prepare()
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    inv_fac[n] = calc_inv(fac[n]);
    for (int i = n - 1; i >= 0; --i)
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
}

void calc_StirlingI(int n) // A=x*(x+1)*...*(x+n-1)
{
    if (n == 1)
    {
        A[0] = 0;
        A[1] = 1;
        return;
    }
    int k = n / 2;
    calc_StirlingI(k);
    for (int i = 0; i <= k; ++i)
    {
        B[i] = A[k - i] * fac[k - i] % MOD;
        C[i] = powq(k, i) * inv_fac[i] % MOD;
    }
    for (int i = k + 1; i <= n; ++i)
        B[i] = C[i] = 0;
    B.mul(k + 1, C, k + 1, tmp);
    for (int i = 0; i <= k; ++i)
        B[i] = tmp[k - i] * inv_fac[i] % MOD;
    for (int i = k + 1; i <= n; ++i)
        B[i] = 0;
    A.mul(k + 1, B, k + 1);
    if (n & 1)
    {
        ll c = n - 1;
        for (int i = n; i >= 1; --i)
            A[i] = (A[i - 1] + A[i] * c) % MOD;
        A[0] = A[0] * c % MOD;
    }
}

ll solve()
{
    if (k > 2*n-1 || k < n)
        return 0;
    prepare();
    calc_StirlingI(n);
    return A[2*n-k]*inv_fac[n]%MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>k;
    ll ans=solve();
    cout<<ans;
    return 0;
}
/*
a submission link:https://atcoder.jp/contests/abc473/submissions/78864467
author: tokitsukaze 
dp i j 表示考虑了前 i 个，当前操作次数为 j 的方案数。
考虑第 i 个数如何插入。
发现一个数 x，如果在这之前存在 1~x-1，它的贡献为 1，否则为 2。
当 i 插入时，只有放在最后位置贡献会增加 1，否则增加 2。
dp[i][j]=dp[i-1][j-1]+(i-1)*dp[i-1][j-2]
发现这转移式子长得有点像第一类斯特林数，打表发现就是 s(n,2n-k)。
*/
