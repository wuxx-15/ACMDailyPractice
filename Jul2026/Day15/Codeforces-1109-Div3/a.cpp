#include <iostream>
#include <string>
using namespace std;
int main()
{
    int t;
    cin>>t;
    string str;
    int n;
    while (t--)
    {
        cin>>n;
        cin>>str;
        int ans=0;
        int tmp=0;
        for (int i=0;i<n;++i)
        {
            if (str[i]=='#') ++tmp;
            else
            {
                ans=max(ans,tmp);
                tmp=0;
            }
        }
        ans=max(ans,tmp);
        ans=(ans+1)/2;
        cout<<ans<<'\n';
    }
    return 0;
}   
