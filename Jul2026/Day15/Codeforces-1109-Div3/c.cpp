#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=200001;
int n,x,y;
int nums[MAXN];
vector<vector<int>> mod;
int gcd(int x,int y)
{
    if (x < y) swap(x,y);
    int tmp;
    while (y)
    {
        tmp=y;
        y=x%y;
        x=tmp;
    }
    return x;
}

bool solve()
{
    int c=gcd(x,y);
    if (c==1) return true;
    int t=n/c;
    int remain=n%c;
    mod.assign(c+1,vector<int>(t+2,MAXN));
    for (int i=1,m=1,cnt=1;i<=n;++i)
    {
        mod[m][cnt]=nums[i];
        if (m==c) 
        {
            m=1;
            ++cnt;
        }
        else ++m;
    }
    for (int i=1;i<=c;++i) 
        sort(mod[i].begin()+1,mod[i].end());
    for (int i=1;i<=t;++i)
    {
        for (int j=1;j<c;++j)
        {
            if (mod[j][i]>=mod[j+1][i]) return false;
        }
        if (mod[1][i+1]<=mod[c][i]) return false; //bu
    }
    for (int i=1;i<remain;++i)
    {
        if (mod[i][t+1]>=mod[i+1][t+1]) return false;
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
        cin>>n>>x>>y;
        for (int i=1;i<=n;++i) cin>>nums[i];
        if (solve()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
