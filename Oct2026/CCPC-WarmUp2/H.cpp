#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 1505;
const int MAXP = 13;
int n, q;
int parent[MAXN];
int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int val[MAXN];
int cntg = 1;
void addEdge(int u, int v)
{
    Next[cntg] = head[u];
    head[u] = cntg;
    to[cntg++] = v;
}

void solve1()
{
    cin >> n;
    for (int i = 2; i <= n; ++i)
        cin >> parent[i];
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    cout << n << endl;
    for (int i = 2; i <= n; ++i)
        cout << parent[i] << ' ' << flush;
    cout << endl;
    for (int i = 1; i <= n; ++i)
        cout << val[i] << ' ' << flush;
    cout << endl;
}

int blen, bnum;
int where[MAXN << 1];

struct Query
{
    int l;
    int r;
    int lca;
    int id;
};

bool cmp(const Query &q1, const Query &q2)
{
    if (where[q1.l] != where[q2.l])
        return where[q1.l] < where[q2.l];
    return (where[q1.l] & 1) ? (q1.r < q2.r) : (q1.r > q2.r);
}

Query qs[MAXN];

int depth[MAXN << 1];
int seq[MAXN << 1];
int Start[MAXN];
int End[MAXN];
int dfn[MAXN];
int RMQ[MAXN][MAXP];
int cntd;
int dfn_cnt;

void dfs(int u, int f)
{
    depth[u] = depth[f] + 1;
    seq[++cntd] = u;
    Start[u] = cntd;
    dfn[u] = ++dfn_cnt;
    RMQ[dfn[u]][0] = f;
    for (int e = head[u], v; e != 0; e = Next[e])
    {
        v = to[e];
        if (v != f)
            dfs(v, u);
    }
    seq[++cntd] = u;
    End[u] = cntd;
}

int getUp(int x, int y)
{
    return dfn[x] < dfn[y] ? x : y;
}

int lg2(int x)
{
    return 31 - __builtin_clz(x);
}

void buildRMQ()
{
    int limit = lg2(n);
    for (int pre = 0, cur = 1; cur <= limit; ++pre, ++cur)
    {
        for (int i = 1; i + (1 << cur) - 1 <= n; ++i)
            RMQ[i][cur] = getUp(RMQ[i][pre], RMQ[i + (1 << pre)][pre]);
    }
}

int getLCA(int x, int y)
{
    if (x == y)
        return x;
    x = dfn[x];
    y = dfn[y];
    if (x > y)
        swap(x, y);
    ++x;
    int k = lg2(y - x + 1);
    return getUp(RMQ[x][k], RMQ[y - (1 << k) + 1][k]);
}

struct Answer
{
    int val;
    int freq;
};

int sorted[MAXN];
int cnts;
bool visited[MAXN];
int cnt[MAXN];
Answer ans[MAXN];
int curMin;

void invert(int node)
{
    int v = val[node];
    if (visited[node])
    {
        --cnt[v];
        while (curMin <= n && cnt[curMin] == 0)
            ++curMin;
    }
    else
    {
        ++cnt[v];
        curMin = min(curMin, v);
    }
    visited[node] = !visited[node];
}

int getKth(int x)
{
    int l = 1;
    int r = cnts;
    int mid;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (sorted[mid] == x)
            return mid;
        else if (sorted[mid] > x)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

void prepare()
{
    for (int i = 1; i <= n; ++i)
        sorted[i] = val[i];
    sort(sorted + 1, sorted + n + 1);
    cnts = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (sorted[cnts] != sorted[i])
            sorted[++cnts] = sorted[i];
    }
    for (int i = 1; i <= n; ++i)
        val[i] = getKth(val[i]);
    int blen = sqrt(cntd);
    for (int i = 1; i <= cntd; ++i)
        where[i] = (i - 1) / blen + 1;
    sort(qs + 1, qs + q + 1, cmp);
}

void solve()
{
    prepare();
    int winl = 1, winr = 0;
    curMin = cnts;
    for (int i = 1; i <= q; ++i)
    {
        auto [jobl, jobr, lca, id] = qs[i];
        while (winl > jobl)
            invert(seq[--winl]);
        while (winr < jobr)
            invert(seq[++winr]);
        while (winl < jobl)
            invert(seq[winl++]);
        while (winr > jobr)
            invert(seq[winr--]);
        if (lca > 0)
            invert(lca);
        ans[id] = {sorted[curMin], cnt[curMin]};
        if (lca > 0)
            invert(lca);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int turn;
    cin >> turn;
    if (turn == 1)
        solve1();
    else
    {
        cin >> n;
        for (int i = 2, p; i <= n; ++i)
        {
            cin >> p;
            parent[i] = p;
            addEdge(i, p);
            addEdge(p, i);
        }
        for (int i = 1; i <= n; ++i)
            cin >> val[i];
        dfs(1, 0);
        buildRMQ();
        cin >> q;
        for (int i = 1, u, v, c; i <= q; ++i)
        {
            cin >> u >> v;
            if (Start[u] > Start[v])
                swap(u, v);
            c = getLCA(u, v);
            if (u == c)
            {
                qs[i].l = Start[u];
                qs[i].r = Start[v];
                qs[i].lca = 0;
            }
            else
            {
                qs[i].l = End[u];
                qs[i].r = Start[v];
                qs[i].lca = c;
            }
            qs[i].id = i;
        }
        solve();
        for (int i = 1; i <= q; ++i)
            cout << ans[i].val << ' ' << ans[i].freq << endl;
    }
    return 0;
}
