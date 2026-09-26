#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T, int MAX_SIZE, typename Compare = less<T>>
class FastHeap
{
private:
    T heap[MAX_SIZE + 1];
    int heap_size;
    Compare comp;

public:
    FastHeap() : heap_size(0) {}
    void clear()
    {
        heap_size = 0;
    }
    bool empty() const
    {
        return heap_size == 0;
    }
    int size() const
    {
        return heap_size;
    }
    const T &top() const
    {
        return heap[1];
    }
    void push(const T &val)
    {
        heap[++heap_size] = val;
        int p = heap_size;
        while (p > 1 && comp(heap[p >> 1], heap[p]))
        {
            swap(heap[p >> 1], heap[p]);
            p >>= 1;
        }
    }
    void pop()
    {
        heap[1] = heap[heap_size--];
        int p = 1;
        while ((p << 1) <= heap_size)
        {
            int son = p << 1;
            if (son < heap_size && comp(heap[son], heap[son + 1]))
                son++;
            if (!comp(heap[p], heap[son]))
                break;
            swap(heap[p], heap[son]);
            p = son;
        }
    }
};
const int MAXN = 1e5 + 5;
const int BIT = 30;
const int MAXT = MAXN * BIT;
const int INF = 1 << 30;
int n, q;
int cntv;
int arr[MAXN];
int tmp[MAXN << 1];
int ansArr[BIT];

int trie[MAXT][2];
int pass[MAXT];
int cntn = 1;

void insert(int num)
{
    int cur = 1;
    for (int b = 29; b >= 0; --b)
    {
        int bit = num >> b & 1;
        if (trie[cur][bit] == 0)
            trie[cur][bit] = ++cntn;
        cur = trie[cur][bit];
        ++pass[cur];
    }
}

int query_kth_xor(int x, int k)
{
    int cur = 1;
    int ans = 0;
    for (int b = 29; b >= 0; --b)
    {
        int bit = (x >> b) & 1;
        int best = trie[cur][bit];
        if (best > 0 && pass[best] >= k)
            cur = best;
        else
        {
            if (best > 0)
                k -= pass[best];
            cur = trie[cur][bit ^ 1];
            ans |= 1 << b;
        }
    }
    return ans;
}

struct Node
{
    int val;
    int idx;
    int kth;
    bool operator>(const Node &rhs) const
    {
        return val > rhs.val;
    }
};

//使用小根堆维护每个元素第k小xor值
FastHeap<Node, MAXN << 1, greater<Node>> minheap;

void calc()
{
    memset(ansArr, 0, sizeof(ansArr));
    int turn = 0;
    while (true)
    {
        sort(arr + 1, arr + n + 1);
        ansArr[turn] = arr[n] - arr[1];
        if (ansArr[turn] == 0)
            break;
        ++turn;
        for (int i = 1; i <= n; ++i)
            insert(arr[i]);
        for (int i = 1; i <= n; ++i)
        {
            int val = query_kth_xor(arr[i], 2);
            minheap.push({val, i, 2});
        }
        int step = 2 * n; //(arr[i]^arr[j]==arr[j]^arr[i]，所以要2*n次)
        int cntv = 0;
        while (step--)
        {
            auto [val, idx, k] = minheap.top();
            minheap.pop();
            tmp[++cntv] = val;
            if (k < n)
            {
                int new_val = query_kth_xor(arr[idx], k + 1);
                minheap.push({new_val, idx, k + 1});
            }
        }
        for (int i = 1, j = 1; i <= n; ++i, j += 2)
            arr[i] = tmp[j];
        minheap.clear();
        memset(trie, 0, sizeof(int) * (cntn + 1) * 2);
        memset(pass, 0, sizeof(int) * (cntn + 1));
        cntn = 1;
    }
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
        cin >> n >> q;
        for (int i = 1; i <= n; ++i)
            cin >> arr[i];
        calc();
        int x;
        while (q--)
        {
            cin >> x;
            int ans = x < BIT ? ansArr[x] : 0;
            cout << ans << '\n';
        }
    }
    return 0;
}
