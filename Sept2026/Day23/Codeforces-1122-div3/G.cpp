#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int MAXN = 200005;
int n;
int val[MAXN];
int mod[MAXN];

int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cntg = 1;
void addEdge(int u, int v)
{
    Next[cntg] = head[u];
    head[u] = cntg;
    to[cntg++] = v;
}

int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);
    int tmp;
    while (b > 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int GCD[MAXN]; // 节点能产生的变化量的 gcd
ll dp[MAXN];   // 在这个节点为根的子树内得到的答案
ll best[MAXN]; // 这个节点最大能取到的值

void dfs(int u, int f)
{
    int g = mod[u]; //可达值之间的最小步长
    ll sum = 0; //孩子的初始值
    ll childrenAns = 0; //从孩子转移过来的答案
    for (int e = head[u], v; e != 0; e = Next[e])
    {
        v = to[e];
        if (v != f)
        {
            dfs(v, u);
            sum += val[v];
            childrenAns += dp[v];
            g = gcd(g, GCD[v]);
        }
    }
    g = gcd(g, sum % mod[u]);
    best[u] = mod[u] - g + val[u] % g;
    dp[u] = childrenAns + best[u];
    GCD[u] = g < mod[u] ? g : 0;
}

ll solve()
{
    dfs(1, 0);
    return dp[1];
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
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> val[i];
        for (int i = 1; i <= n; ++i)
            cin >> mod[i];
        memset(head, 0, sizeof(int) * (n + 1));
        cntg = 1;
        for (int i = 1, u, v; i < n; ++i)
        {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        ll ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
