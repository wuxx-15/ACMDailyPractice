#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN=300010;
int n,len;
int a[MAXN];
int b[MAXN];
int cntb=0;
int c[MAXN<<1];
bool cnt[MAXN];
bool used[MAXN];

int delta(int x)
{
    return min(x,n+1-x);
}

bool cmp(int x,int y)
{
    int dx=delta(x);
    int dy=delta(y);
    if (dx!=dy) return dx<dy; //让相同数一定连续
    return x<y;
}

bool solve()
{
    memset(cnt,0,sizeof(cnt));
    memset(used,0,sizeof(used));
    cntb=0;
    int bl=(n+1)/2;
    for (int i=1,v;i<=len;++i)
    {
        v=c[i];
        if (cnt[v]) 
        {
            b[++cntb]=v;
            used[v]=true;
            if (cntb>bl) return false;
        }
        else cnt[v]=true;
    }
    if (cntb != bl) return false;
    sort(b+1,b+bl+1,cmp);
    int l=1,r=n;
    int cnta=0;
    a[++cnta]=b[1];
    for (int i=2;i<=bl;++i)
    {
        if (delta(b[i])<i) return false;
        if (b[i]==b[i-1])
        {
            while (used[r]) --r;
            a[++cnta]=r;
            used[r]=true;
            while (used[l]) ++l;
            a[++cnta]=l;
            used[l]=true;
        }
        else if (b[i]>b[i-1])
        {
            a[++cnta]=b[i];
            while (used[r]) --r;
            a[++cnta]=r;
            used[r]=true;
        }
        else
        {
            a[++cnta]=b[i];
            while (used[l]) ++l;
            a[++cnta]=l;
            used[l]=true;
        }
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
        len=(3*n+1)/2;
        for (int i=1;i<=len;++i)
        {
            cin>>c[i];
        }
        if (!solve()) cout<<-1<<'\n';
        else
        {
            for (int i=1;i<=n;++i)
                cout<<a[i]<<' ';
            cout<<'\n';
        }
    }
    return 0;
}
