#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int n;
const int MAXN=1000005;
int arr[MAXN];
ll suma[MAXN];
ll sumb[MAXN];

bool compute()
{
    int mid=n/2+1;
    for (int i=1;i<mid;++i)
    {
        suma[i]=suma[i-1]+arr[i]; 
    }
    reverse(suma+1,suma+mid);
    for (int i=1;i<=n-mid;++i)
    {
        sumb[i]=sumb[i-1]+arr[n-i+1];
    }
    reverse(sumb+1,sumb+n-mid+1);
    int x=min(mid-1,n-mid);
    for (int i=1;i<=x;++i)
    {
        if (suma[i]>sumb[i]) return true;
        else if (suma[i]<sumb[i]) return false; 
    }
    return n & 1 ? false : true;
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
        for (int i=1;i<=n;++i) cin>>arr[i];
        if (compute()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
