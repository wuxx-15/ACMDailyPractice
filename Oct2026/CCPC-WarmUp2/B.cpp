#include <iostream>
using namespace std;
int query(int x)
{
    cout << "? " << x << endl;
    int sign;
    cin >> sign;
    return sign;
}

void answer(int x)
{
    cout << "! " << x << endl;
}

void solve()
{
    int l=0;
    int r=1e9;
    int mid;
    int ans=0;
    while (l <= r)
    {
        mid=l+r>>1;
        if (query(mid)==1)
        {
            ans=mid;
            r=mid-1;
        }
        else
            l=mid+1;
    }
    answer(ans);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
