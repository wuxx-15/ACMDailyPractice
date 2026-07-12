#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//暴力解尽量用STL模板
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    vector<int> v;
    while (n--)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1)
        {
            v.insert(lower_bound(v.begin(), v.end(), x), x);
        }
        else if (op == 2)
        {
            auto it = lower_bound(v.begin(), v.end(), x);
            if (it != v.end() && *it == x)
            {
                v.erase(it);
            }
        }
        else if (op == 3)
        {
            cout << lower_bound(v.begin(), v.end(), x) - v.begin() + 1 << '\n';
        }
        else if (op == 4)
        {
            cout << v[x - 1] << '\n';
        }
        else if (op == 5)
        {
            auto it = lower_bound(v.begin(), v.end(), x);
            --it;
            cout << *it << '\n';
        }
        else if (op == 6)
        {
            auto it = upper_bound(v.begin(), v.end(), x);
            cout << *it << '\n';
        }
    }
    return 0;
}
