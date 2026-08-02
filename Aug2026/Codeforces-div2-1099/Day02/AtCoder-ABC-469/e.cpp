//分数规划
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int MAXN=1000005;
string str;
int n,k,total;
int presum[MAXN];
int jump[MAXN];
double f[MAXN];
double sufmax[MAXN];
const double sml=1e-7;

void prepare()
{
    for (int i=1;i<=n;++i)
    {
        if (str[i]=='o')
            presum[i]=presum[i-1]+1;
        else
            presum[i]=presum[i-1];
    }
    total=presum[n];
    int r=1;
    while (presum[r]<k) ++r;
    int cur=k;
    for (int i=0;i<=n;++i)
    {
        if (str[i]=='x') continue;
        jump[i]=r;
        if (++cur>total)
        {
            for (int j=i+1;j<=n;++j)
                jump[j]=n+1;
            break;
        }
        while (presum[r]<cur)
            ++r;
    }
}

bool check(double x)
{
    for (int i=0;i<=n;++i)
        f[i]=presum[i]-i*x;
    sufmax[n+1]=-1e9;
    for (int i=n;i>=1;--i)
        sufmax[i]=max(sufmax[i+1],f[i]);
    for (int i=0;i<=n;++i)
    {
        if (str[i+1]=='x') continue;
        int tar=jump[i+1];
        if (tar==n+1) break;
        if (f[i]<sufmax[tar]) return true; 
    }
    return false;
}

double compute()
{
    prepare();
    double l=0.0;
    double r=1.0;
    double mid;
    double ans=0.0;
    while (r-l>sml)
    {
        mid=(l+r)/2.0;
        if (check(mid)) 
        {
            ans=mid;
            l=mid;
        }
        else
            r=mid;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>k;
    cin>>str;
    str.insert(0,"x");
    cout<<fixed<<setprecision(10)<<compute();
    return 0;
}
