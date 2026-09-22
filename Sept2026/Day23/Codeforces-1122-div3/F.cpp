#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAXN=200055;
ll cnt[MAXN];
ll total; //元素总数
int n; 
int maxv;

bool check(int x)
{
    /*
    缺的数目,由于它会指数级
    在极端情况，连续几个数词频为0时,owned->2*owned+1，指数级增长
    元素最多2e14个，log2(2e14) = 48
    将n+50设为右边界足够
    */
    ll owned=0; 
    ll used=0;
    for (int i=x-1;i>=1;--i)
    {
        ll need=1+owned;
        ll take=min(need,cnt[i]);
        owned+=need-take;
        used+=take;
        if (owned > total)
            break;
    }
    ll need_0=1+owned; //所有正数都能变成0
    used+=need_0;
    return used <= total;
}

int solve()
{
    int l=1;
    int r=n+50;
    int mid=l+r>>1;
    int ans=0;
    while (l <= r)
    {
        mid=l+r>>1;
        if (check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return max(ans,maxv);
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
        memset(cnt,0,sizeof(ll)*(n+51));
        total=0;
        maxv=0;
        for (int i=1,x,y;i<=n;++i)
        {
            cin >> x >> y;
            total += y;
            maxv=max(maxv,x);
            if (x <= n + 50) //太大的数只能当0用
                cnt[x]=y;
        }
        int ans=solve();
        cout<<ans<<'\n';
    }
    return 0;
}
