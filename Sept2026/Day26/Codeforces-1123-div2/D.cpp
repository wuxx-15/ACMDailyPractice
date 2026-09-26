#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
int n;

int odd[MAXN];
int cnt1;
int even[MAXN];
int cnt2;

bool solve()
{
    if (n == 1)
        return true;
    sort(odd + 1, odd + cnt1 + 1, greater<int>());
    sort(even + 1, even + cnt2 + 1, greater<int>());
    if (odd[1] > even[1])
    {
        int i1 = 2, i2 = 1;
        for (; i1 <= cnt1 && i2 <= cnt2; ++i1, ++i2)
        {
            if (even[i2] < odd[i1])
                return false;
        }
        i1 = 2, i2 = 3;
        for (; i1 <= cnt1 && i2 <= cnt2; ++i1, ++i2)
        {
            if (odd[i1] < even[i2])
                return false;
        }
    }
    else
    {
        int i1 = 1, i2 = 2;
        for (; i1 <= cnt1 && i2 <= cnt2; ++i1, ++i2)
        {
            if (odd[i1] < even[i2])
                return false;
        }
        i1 = 3, i2 = 2;
        for (; i1 <= cnt1 && i2 <= cnt2; ++i1, ++i2)
        {
            if (even[i2] < odd[i1])
                return false;
        }
    }
    return true;
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
        cnt1 = 0;
        cnt2 = 0;
        for (int i = 1, v; i <= n; ++i)
        {
            cin >> v;
            if (i & 1)
                odd[++cnt1] = v;
            else
                even[++cnt2] = v;
        }
        if (solve())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
