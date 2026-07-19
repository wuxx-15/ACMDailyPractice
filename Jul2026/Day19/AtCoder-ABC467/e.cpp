#include <iostream>
#include <array>
#include <algorithm>
#define ll long long
using namespace std;
typedef pair<int,ll> np;
const int MAXN=200001;
int n,m;
ll a[MAXN];
ll b[MAXN];
ll c[MAXN]; // b[i]-a[i]-a[i+1] mod m
ll k[MAXN]; // c[i-1]-k[i-1] mod m k[1]=0
/*
a[i]+x[i]+a[i+1]+x[i+1]=b[i] mod m
x[i]+x[i+1]=b[i]-a[i]-a[i+1] mod m
def c[i]=x[i]+x[i+1]=b[i]-a[i]-a[i+1] mod m
x[2]=(c[1]-x[1]) mod m
x[3]=(c[2]-x[2]) mod m
......
x[v]=(v+k[i]) mod m (i odd)
x[v]=(k[i]-v) mod m (i even)
*/
array<np,MAXN> event;
bool cmp(const np& a1,const np& a2)
{
    return a1.first<a2.first;
}
ll compute()
{
    for (int i=1;i<n;++i) 
    {
        c[i]=(b[i]-a[i]-a[i+1]+2*m)%m;
    }
    k[1]=0;
    for (int i=2;i<=n;++i)
    {
        k[i]=(c[i-1]-k[i-1]+m)%m;
    }
    ll ret=0;
    for (int i=1;i<=n;++i) ret+=k[i]; //v=0
    for (int i=1;i<=n;++i) 
    {
        if (i & 1) 
        {
            if (k[i] != 0)
                event[i]={m-k[i],-m};
        }
        else 
        {
            if (k[i] != m-1)
                event[i]={k[i]+1,m};
        }
    }
    int delta;
    if (n & 1) delta=1;
    else delta=0; //斜率
    sort(event.begin()+1,event.begin()+n+1,cmp);
    int prev=0;
    ll curr=ret;
    for (int i=1;i<=n;++i)
    {
        curr+=delta*(event[i].first-prev)+event[i].second;
        prev=event[i].first;
        while (i < n && event[i].first == event[i+1].first)
            curr+=event[++i].second;
        ret=min(ret,curr);
    }
    return ret;
}
int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;++i)
        cin>>a[i];
    for (int i=1;i<n;++i)
        cin>>b[i];
    cout<<compute();
    return 0;
}
