#include <iostream>
#define ll long long
using namespace std;
int main()
{
    int t;
    cin>>t;
    ll n,tmp;
    while (t--)
    {
        cin>>n;
        ll sum=0;
        bool isvalid=true;
        for (ll i=1;i<=n;++i)
        {
            cin>>tmp;
            sum+=tmp;
            if (sum < i*(i+1)/2)
            {
                isvalid=false;
            }
        }
        if (isvalid) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
