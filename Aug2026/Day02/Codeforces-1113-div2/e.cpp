#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int MAXM=2005;
int m;
ll n,d;
ll sum[MAXM<<1]; //f(I(a)) (|a|为奖励点) 的值
ll sumAll; //|a|=n
struct reward
{
    int p;
    ll r;
};

reward rewards[MAXM];

int event[MAXM];

void prepare()
{
    int prev=0;
    memset(sum,0,sizeof(ll)*(m+1));
    for (int i=1;i<=m;++i)
    {
        int p=rewards[i].p;
        ll r=rewards[i].r;
        sum[i]=sum[i-1]+(p-prev)*d+r;
        prev=p;
    }
    sumAll=sum[m]+(n-event[m])*d;
}

int binary_search(int x)
{
    int l=1;
    int r=m;
    int mid;
    int ans=0;
    while (l <= r)
    {
        mid=l+r>>1;
        if (event[mid]<=x)
        {
            ans=mid;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return ans;
}

ll countSum(int x)
{
    ll ret=0;
    if (x>n)
    {
        int tmp=x/n;
        x%=n;
        ret+=tmp*sumAll;
    }
    int epos=binary_search(x);
    int p=rewards[epos].p;
    ret+=sum[epos]+(x-p)*d;
    return ret;
}

bool solve()
{
    prepare();
    //只枚举奖励点
    for (int i=1;i<=m;++i)
    {
        for (int j=i;j<=m;++j)
        {
            ll s1=sum[i]+sum[j];
            ll x=event[i]+event[j]+1;
            ll s2=countSum(x);
            //若S[i]+S[j]>S[i+j+1]则可以成功构造
            if (s1>s2) return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    while (t--)
    {
        cin>>n>>m>>d;
        for (int i=1;i<=m;++i)
        {
            cin>>rewards[i].p>>rewards[i].r;
            event[i]=rewards[i].p;
        }
        if (solve()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
