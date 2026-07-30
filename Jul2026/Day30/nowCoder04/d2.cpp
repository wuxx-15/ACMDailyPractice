#include <iostream>
#include <string>
using namespace std;

const int MAXN=500001;
int arr[MAXN];
int n;

void solve()
{
    if (n==1)
    {
        arr[1]=1;
        return;
    }
    int k=n/2;
    if (n&1) 
    {
        arr[1]=1;
        arr[3]=2;
        for (int v=k+3,id=5;v<=n;++v,id+=2)
            arr[id]=v;
        for (int v=k+2,id=2;v>1;--v,id+=2)
            arr[id]=v;
    }
    else
    {
        arr[1]=1;
        for (int v=k,id=3;v>=2;--v,id+=2)
            arr[id]=v;
        for (int v=k+1,id=2;v<=n;++v,id+=2)
            arr[id]=v;
    }
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
        solve();
        for (int i=1;i<=n;++i)
            cout<<arr[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
