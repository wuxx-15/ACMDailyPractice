#include <iostream>
#include <string>
#include <cstring>
#define ll long long
using namespace std;
ll x,y;
const int MAXN=200001;

int getN(int d)
{
    int l=1;
    int r=2e4;
    int ans=0;
    int mid;
    while (l <= r)
    {
        mid=l+r>>1;
        if (mid*(mid+1)<=2*d)
        {
            ans=mid;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return ans;
}

bool state[MAXN];

string solve()
{
    memset(state,0,sizeof(state));
    string str;
    int all=x+y;
    int n=getN(all);
    int d=n*(n+1)/2;
    int delta=(all-d)/2;
    int x1=x-delta;
    int y1=d-x1;
    for (int i=n;i>=1;--i)
    {
        if (y1>=i)
        {
            y1-=i;
            state[n-i+1]=true;
        }
        else
            break;
    }
    state[n-y1+1]=true;
    for (int i=1;i<=n;++i)
    {
        if (state[i]) str.push_back('Y');
        else str.push_back('X');
    }
    return str;
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
        cin>>x>>y;
        cout<<solve()<<'\n';
    }
    return 0;
}
