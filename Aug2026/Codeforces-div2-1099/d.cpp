#include <iostream>
#include <string>
#define ll long long
using namespace std;
const int MAXN=200005;
const ll INF=2e11;
int n;
string str;
ll a[MAXN];
ll b[MAXN];
ll c[MAXN];
bool solve()
{
    for (int i=2;i<=n;++i)
    {
        if (c[i]<c[i-1]) return false;
    }
    b[1]=c[1];
    if (str[1]=='1')
    {
        if (a[1] != b[1]) return false;
    }
    else
        a[1]=b[1];
    ll sum=a[1];
    for (int i=2;i<=n;)
    {
        //当前是上升点
        if (c[i]>c[i-1])
        {
            if (str[i]=='0')
            {
                a[i]=c[i]-sum;
                sum=c[i];
            }
            else
            {
                sum += a[i];
                if (sum != c[i])
                    return false;
            }
            ++i;
            continue;
        }
        int changable=0;
        if (str[i]=='1')
        {
            sum+=a[i];
            if (c[i]>c[i-1])
            {
                if (sum != c[i]) return false;
            }
            else
            {
                if (sum > c[i]) return false;
            }
            ++i;
        }
        else
        {
            changable=i;
            a[i]=-INF;
            sum+=a[i];
            int r=i+1;
            while (r <= n && c[r]==c[r-1])
                ++r;
            if (r==n+1)
            {
                for (int j=i+1;j<=n;++j)
                {
                    if (str[j]=='0')
                        a[j]=-INF;
                }
                break;
            }
            else
            {
                for (int j=i+1;j<r;++j)
                {
                    if (str[j]=='0')
                    {
                        changable=j;
                        a[j]=-INF;
                    }
                    sum+=a[j];
                    if (sum > c[j]) return false;
                }
                if (str[r]=='0')
                {
                    a[r]=c[r]-sum;
                }
                else
                {
                    //贪心再反悔
                    sum-=a[changable];
                    a[changable]=c[r]-sum-a[r];
                }
                sum=c[r];
                i=r+1;
            }
        }
    }

    //复检
    sum=0;
    ll maxSum=-INF;
    for (int i=1;i<=n;++i)
    {
        sum+=a[i];
        maxSum=max(maxSum,sum);
        if (maxSum != c[i])
            return false;
    }

    return true;
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
        cin>>n;
        cin>>str;
        str.insert(0,"#");
        for (int i=1;i<=n;++i)
            cin>>a[i];
        for (int i=1;i<=n;++i)
            cin>>c[i];
        if (solve()) 
        {
            cout<<"Yes\n";
            for (int i=1;i<=n;++i)
                cout<<a[i]<<' ';
            cout<<'\n';
        }
        else
            cout<<"No\n";
    }
    return 0;
}
