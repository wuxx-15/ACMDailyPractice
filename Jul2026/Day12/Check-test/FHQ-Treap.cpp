//luogu P3369
//用于测试test.sh功能性
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;
const int MAXN = 100001;
int head = 0;
int cnt = 0;
int key[MAXN];
int cnts[MAXN];
int ls[MAXN];
int rs[MAXN];
int sizes[MAXN];
double priority[MAXN];

void up(int i)
{
    sizes[i] = sizes[ls[i]] + sizes[rs[i]] + cnts[i];
}

void split(int &l, int &r, int i, int num)
{
    if (i == 0)
        l = r = 0;
    else
    {
        if (key[i] <= num)
        {
            l = i;
            split(rs[i], r, rs[i], num);
        }
        else
        {
            r = i;
            split(l, ls[i], ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r)
{
    if (l == 0 || r == 0)
        return l + r;
    if (priority[l] >= priority[r])
    {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    }
    else
    {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

int find(int i, int num)
{
    if (i == 0)
        return 0;
    if (key[i] == num)
        return i;
    else if (key[i] > num)
        return find(ls[i], num);
    else
        return find(rs[i], num);
}

void changeCount(int i, int num, int change)
{
    if (key[i] == num)
        cnts[i] += change;
    else if (key[i] > num)
        changeCount(ls[i], num, change);
    else
        changeCount(rs[i], num, change);
    up(i);
}

void add(int num)
{
    if (find(head, num) != 0)
        changeCount(head, num, 1);
    else
    {
        int l = 0, r = 0;
        split(l, r, head, num);
        key[++cnt] = num;
        cnts[cnt] = sizes[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        head = merge(merge(l, cnt), r);
    }
}

void remove(int num)
{
    int i = find(head, num);
    if (i != 0)
    {
        if (cnts[i] > 1)
            changeCount(head, num, -1);
        else
        {
            int lm = 0, r = 0;
            split(lm, r, head, num);
            int l = 0, m = 0;
            split(l, m, lm, num-1);
            head = merge(l, r);
        }
    }
}

int small(int i, int num)
{
    if (i == 0)
        return 0;
    if (key[i] >= num)
        return small(ls[i], num);
    else
        return sizes[ls[i]] + cnts[i] + small(rs[i], num);
}

int getRank(int num)
{
    return small(head, num) + 1;
}

int index(int i, int x)
{
    assert(i != 0);
    if (sizes[ls[i]] >= x)
        return index(ls[i], x);
    else if (sizes[ls[i]] + cnts[i] < x)
        return index(rs[i], x - sizes[ls[i]] - cnts[i]);
    return key[i];
}

int index(int x)
{
    return index(head, x);
}

int pre(int i, int num)
{
    if (i == 0)
        return INT_MIN;
    if (key[i] >= num)
        return pre(ls[i], num);
    else
        return max(key[i], pre(rs[i], num));
}

int pre(int num)
{
    return pre(head, num);
}

int post(int i, int num)
{
    if (i == 0)
        return INT_MAX;
    if (key[i] <= num)
        return post(rs[i], num);
    else
        return min(key[i], post(ls[i], num));
}

int post(int num)
{
    return post(head, num);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++)
    {
        cin >> op >> x;
        if (op == 1)
        {
            add(x);
        }
        else if (op == 2)
        {
            remove(x);
        }
        else if (op == 3)
        {
            cout << getRank(x) << endl;
        }
        else if (op == 4)
        {
            cout << index(x) << endl;
        }
        else if (op == 5)
        {
            cout << pre(x) << endl;
        }
        else
        {
            cout << post(x) << endl;
        }
    }
    return 0;
}
