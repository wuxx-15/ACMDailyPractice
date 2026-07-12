//用于测试testspj1.sh功能性
#include <iostream>
#include <unordered_set>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 100001;
int arr[MAXN];
int color[MAXN];
vector<vector<int>> ans(MAXN);
unordered_set<int> hashset;
int n, k;
int bs(int x)
{
    int l = 1;
    int r = n;
    int ret = 0;
    int mid;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (color[mid] >= x)
        {
            ret = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ret;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    hashset.clear();
    memset(color, 0, sizeof(color));
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        hashset.insert(arr[i]);
        if (arr[i]==arr[i-1]) color[i]=color[i-1];
        else color[i]=color[i-1]+1;
    }
    if (color[n] == k)
        cout << 0 << '\n';
    else if (color[n] < k)
    {
        int misc = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (hashset.find(i) == hashset.end())
            {
                misc = i;
                break;
            }
        }
        int q=n-k+1;
        vector<int> ans;
        for (int i=1;i<=q;++i) ans.push_back(i);
        for (int i=q+2;i<=n;i+=2) ans.push_back(i);
        cout<<1<<'\n';
        cout<<ans.size()<<' ';
        for (const int& i:ans) cout<<i<<' ';
        cout<<misc<<'\n';
    }
    else
    {
        cout << 1 << '\n';
        int p = bs(k + 1);
        cout << n - p + 1 << " ";
        for (int i = p; i <= n; ++i)
            cout << i << " ";
        cout << arr[p - 1] << '\n';
    }
    return 0;
}
