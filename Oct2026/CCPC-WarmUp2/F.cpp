#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAXN = 2e5 + 5;
int n;
int arr[MAXN];
int pos[MAXN];
int pre1[MAXN];
int pre2[MAXN];
int suf1[MAXN];
int suf2[MAXN];

int treeSum[MAXN];

int lowbit(int i)
{
    return i & (-i);
}

void add_pre(int i, int v)
{
    while (i <= n)
    {
        treeSum[i] += v;
        i += lowbit(i);
    }
}

int query_pre(int i)
{
    int ans = 0;
    while (i > 0)
    {
        ans += treeSum[i];
        i -= lowbit(i);
    }
    return ans;
}

void add_suf(int i, int v)
{
    while (i > 0)
    {
        treeSum[i] += v;
        i -= lowbit(i);
    }
}

int query_suf(int i)
{
    int ans = 0;
    while (i <= n)
    {
        ans += treeSum[i];
        i += lowbit(i);
    }
    return ans;
}

int bs_pre(int rb, int x)
{
    int l = 1;
    int r = rb;
    int mid;
    int ans = 0;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (query_pre(mid) >= x)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ans;
}

int bs_suf(int lb, int x)
{
    int l = lb;
    int r = n;
    int mid;
    int ans = n + 1;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (query_suf(mid) >= x)
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ans;
}

ll solve()
{
    for (int i = 1.; i <= n; ++i)
        pos[arr[i]] = i;
    for (int v = n; v >= 1; --v)
    {
        int p = pos[v];
        add_pre(p, 1);
        int sum = query_pre(p);
        pre1[p] = sum > 1 ? bs_pre(p - 1, sum - 1) : 0;
        pre2[p] = sum > 2 ? bs_pre(p - 2, sum - 2) : 0;
    }
    memset(treeSum, 0, sizeof(int) * (n + 1));
    for (int v = n; v >= 1; --v)
    {
        int p = pos[v];
        add_suf(p, 1);
        int sum = query_suf(p);
        suf1[p] = sum > 1 ? bs_suf(p + 1, sum - 1) : n+1;
        suf2[p] = sum > 2 ? bs_suf(p + 2, sum - 2) : n+1;
    }
    ll ans = 0;
    for (int u = 1; u <= n; ++u)
    {
        int p1 = pre1[u];
        int p2 = pre2[u];
        int s1 = suf1[u];
        int s2 = suf2[u];
        ans += 1LL * (u - p1) * (p1 - p2) * (s1 - u);
        ans += 1LL * (s1 - u) * (u - p1) * (s2 - s1);
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
        cin >> arr[i];
    ll ans = solve();
    cout << ans << '\n';
    return 0;
}
