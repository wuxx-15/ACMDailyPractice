#include <iostream>
#include <cstring> 
using namespace std;
const int MAXN=200001;
const int BIT=20;
int n,k;
int arr[MAXN];
int highbit[MAXN<<1]; //最高位
int prenum[MAXN<<1]; //非零非2的非负整数次幂的数
int cntn=0;
bool isset[BIT];
bool check()
{ 
    if (n==1)
    {
        if (k==1)
        {
            arr[0]=0;
            return true;
        }
        else return false;
    }
    k^=n; //mex[p0,p0,...,pn-1]=n
    memset(isset,0,sizeof(isset));
    if (k >= 2*MAXN || highbit[k] > highbit[n-1]) return false;
    int maxb=highbit[n-1];
    for (int b=maxb;b>=0;--b)
    {
        if (k >> b & 1)
        {
            isset[b]=true;
        }
    }
    int cur=0;
    for (int i=0;i<cntn;++i)
    {
        if (prenum[i]<n) arr[cur++]=prenum[i];
    }
    for (int b=maxb;b>=0;--b)
    {
        if (!isset[b]) 
        {
            arr[cur++]=1<<b;
        }
    }
    arr[cur++]=0;
    cur=n-1;
    for (int b=maxb;b>=0;--b)
    {
        if (isset[b]) 
        {
            arr[cur--]=1<<b;
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
    highbit[0]=-1;
    highbit[1]=0;
    for (int i=2;i<2*MAXN;++i) 
    {
        highbit[i]=highbit[i>>1]+1;
        if (i != (1<<highbit[i])) prenum[cntn++]=i;
    }
    while (t--)
    {
        cin>>n>>k;
        if (check()) 
        {
            cout<<"YES\n";
            for (int i=0;i<n;++i) cout<<arr[i]<<' ';
            cout<<'\n';
        }
        else cout<<"NO\n";
    }
    return 0;
}
