#include <iostream>
#include <climits>
#define ll long long
using namespace std;
const int MAXN=100001;
int nums[MAXN];
int n;
int cost(int x)
{
    int ret=-1;
    while (x)
    {
        if (x & 1) ret+=2;
        else ++ret;
        x>>=1;
    }
    return ret;
}
//只要有奇数，Bob就回把奇数放到第2位
ll compute()
{
    ll ret=LLONG_MAX;
    ll scost;
    int t;
    for (int g=0,base;g<=17;++g) //初始化为所有数二进制末尾至少g位全为0
    {
        ll tmp=0;
        for (int i=1,x;i<=n;++i) //解耦
        {
            x=nums[i];
            int scost=INT_MAX;
            for (int bit=g,stmp,t;bit<=17;++bit)
            {
                base=1<<bit;
                t=(x+base-1)/base;
                stmp=base*t-x+cost(base*t);
                scost=min(scost,stmp); 
            }
            tmp+=scost;
        }
        tmp-=g*(n-1);
        ret=min(ret,tmp);
    }
    return ret;
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    int t;
    cin>>t;
    while (t--)
    {
        cin>>n;
        for (int i=1;i<=n;++i) cin>>nums[i];
        cout<<compute()<<'\n';
    }
    return 0;
}
