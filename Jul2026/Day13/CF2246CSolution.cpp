//link:https://codeforces.com/contest/2246/problem/C
#include <iostream>
#define ll long long
using namespace std;
const ll MOD=1e9+7;
const int MAXN=200001;
int n,m; //n:题目给的数字数量；m:正数数量
int nums[MAXN];
int val[MAXN];
int cnt=0; //不同的正数数量

ll pow2[MAXN];

//预处理
void preCalc()
{
    pow2[0]=1;
    for (int i=1;i<MAXN;++i) pow2[i]=pow2[i-1]*2%MOD;
}

ll solve() //选奇数个-1=>正数凑1;选偶数个-1=>正数凑0
{
    ll r1=0,r2=0;
    int cur=nums[1];
    cnt=0;
    for (int i=2;i<=m;++i) //分块统计
    {
        if (nums[i] != cur)
        {
            val[++cnt]=cur;
            cur=nums[i];
        }
    }
    val[++cnt]=cur;
    r1=pow2[m-cnt]%MOD; //每种数字都选偶数个
    
    int near=0;
    for (int i=1;i<cnt;++i)
    {
        if (val[i+1]-val[i]==1) ++near; //统计相邻对数目
    }
    r2=near*pow2[m-cnt]%MOD; //一对相邻对选奇数个，其余选偶数个
    int mv=n-m;
    if (mv==0) return r1;
    else return pow2[mv-1]*(r1+r2)%MOD; 
}
int main()
{
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    int t;
    cin>>t;
    preCalc();
    while (t--)
    {
        cin>>n;
        m=0;
        for (int i=1,tmp;i<=n;++i) 
        {
            cin>>tmp;
            if (tmp != -1) nums[++m]=tmp;
        }
        cout<<solve()<<'\n';
    }
    return 0;
}
