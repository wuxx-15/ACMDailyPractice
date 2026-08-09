#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN=205;

int a[MAXN];
int n,l;

double dp[MAXN][MAXN][MAXN]; //全部,已知,HP，dp值为配对数

double compute()
{
    
    double mid=0.0;
    for (int i=1;i<=n;++i)
        mid += a[i];
    mid /= n;
    for (int i=1;i<=n;++i)
    {
        for (int h=1;h<=l;++h)
        {
            for (int j=0;j<=i;++j)
            {
                if (j==i)
                {
                    dp[i][j][h]=dp[i-1][j-1][h]+1.0;
                    continue;
                }
                int unknown=2*i-j;
                double ans=0.0;

                //第一张是见过的
                if (j > 0)
                {
                    ans+=1.0*j/unknown*(1.0+dp[i-1][j-1][h]);
                }

                //第一张没见过
                double tmp=0;

                //碰巧配对
                tmp+=1.0/(unknown-1)*(1.0+dp[i-1][j][h]);

                //第二张见过
                if (h >= 2)
                    tmp+=1.0*j/(unknown-1)*(1.0+dp[i-1][j][h-1]);

                tmp+=2.0*(i-j-1)/(unknown-1)*dp[i][j+2][h-1];

                ans+=2.0*(i-j)/unknown*tmp;
                dp[i][j][h]=ans;
            }
        }
    }
    return dp[n][0][l]*mid;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>l;
    for (int i=1;i<=n;++i)
        cin>>a[i];
    cout<<fixed<<setprecision(15)<<compute()<< '\n';
    return 0;
}
