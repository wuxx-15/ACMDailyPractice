#include <iostream>
#include <string>
using namespace std;
const int MAXN=200001;
string blobs;
int n,q;
int l,r,k;
int isdiff1[MAXN];
int diffsum1[MAXN];
int isdiff0[MAXN];
int diffsum0[MAXN];
void prepare()
{
    for (int i=1,b1=1;i<=n;++i,b1^=1)
    {
        if (blobs[i]-'0' == b1) 
        {
            isdiff1[i]=0;
            isdiff0[i]=1;
        }
        else
        {
            isdiff1[i]=1;
            isdiff0[i]=0;
        }
    }
    for (int i=1;i<=n;++i)
    {
        if (isdiff1[i]==1 && isdiff1[i-1]==0) 
            diffsum1[i]=diffsum1[i-1]+1;
        else 
            diffsum1[i]=diffsum1[i-1];
        if (isdiff0[i]==1 && isdiff0[i-1]==0) 
            diffsum0[i]=diffsum0[i-1]+1;
        else 
            diffsum0[i]=diffsum0[i-1];
    }
}
bool solve()
{
    int diffcnt1=diffsum1[r]-diffsum1[l-1];
    if (isdiff1[l]==1 && isdiff1[l-1]==1) ++diffcnt1;
    if (diffcnt1<=k) return true;

    int diffcnt0=diffsum0[r]-diffsum0[l-1];
    if (isdiff0[l]==1 && isdiff0[l-1]==1) ++diffcnt0;
    if (diffcnt0<=k) return true;
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
        cin>>n>>q;
        cin>>blobs;
        blobs.insert(0,"0");
        prepare();
        while (q--)
        {
            cin>>l>>r>>k;
            if (solve()) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}
