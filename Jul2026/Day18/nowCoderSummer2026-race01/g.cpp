#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const double delta=0.01;
const double sml=1e-7;
int dist[5]={-1,0,1,0,-1};
int n;
void solve()
{
    double x,y;
    cout<<2*n<<'\n';
    x=y=0.0;
    cout<<fixed<<setprecision(9)<<x<<' '<<y<<' '<<0.0<<'\n';
    cout<<fixed<<setprecision(9)<<x<<' '<<y<<' '<<1.0<<'\n';
    int cnt=1;
    double r0=0.01+sml;
    for (int i=1;i<=7;++i)
    {
        double a=i*r0;
        x=a;
        y=-a;
        for (int j=0;j<4;++j)
        {
            for (int k=0;k<2*i;++k)
            {
                if (cnt==n) return;
                cout<<fixed<<setprecision(9)<<x<<' '<<y<<' '<<0.0<<'\n';
                cout<<fixed<<setprecision(9)<<x<<' '<<y<<' '<<1.0<<'\n';
                x+=r0*dist[j];
                y+=r0*dist[j+1];
                ++cnt;
            }
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        cin>>n;
        solve();
    }
    return 0;
}
