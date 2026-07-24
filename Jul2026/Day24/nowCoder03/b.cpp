#include <iostream>
#define ll long long
/*
Raney引理
对于一个每项不超过 1、总和为正整数 n 的序列，
它的 m 个循环移位中，恰好有 n 个循环移位的所有前缀和均为正。
本题中,从花完钱到初始状态，步长有1和1-c两种，总和为n
m次有x次中奖，n/m*C(x,m)*pow(p,x)*pow(1-p,m-x);
即n*pow(m,-1)*C(m,x)*pow(a,x)*pow(b-a,m-x)*pow(b,-m)
*/
using namespace std;
const int MAXN=2000001;
const ll MOD=998'244'353ll;

int n,m,c,a,b;

ll frac[MAXN];
ll inv[MAXN]; //阶乘逆元

ll powq(ll base,int p)
{
    ll ret=1;
    while (p > 0)
    {
        if (p & 1) ret=ret*base%MOD;
        base=base*base%MOD;
        p >>= 1;
    }
    return ret;
}

void prepare()
{
    frac[0]=1;
    for (int i=1;i<MAXN;++i)
    {
        frac[i]=frac[i-1]*i%MOD;
    }
    inv[MAXN-1]=powq(frac[MAXN-1],MOD-2);
    for (int i=MAXN-2;i>=0;--i)
        inv[i]=inv[i+1]*(i+1)%MOD;
}

ll C(int m,int n)
{
    return frac[m]*inv[n]%MOD*inv[m-n]%MOD;
}

ll compute()
{
    int x=(m-n)/c; //中奖次数
    ll invm=powq(m,MOD-2);
    ll invp=powq(powq(b,m),MOD-2);
    ll p3=powq(a,x);
    ll p4=powq(b-a,m-x);
    ll p5=C(m,x);
    cout<<n<<' '<<invm<<' '<<invp<<' '<<p3<<' '<<p4<<' '<<p5<<'n';
    return n*invm%MOD*C(m,x)%MOD*powq(a,x)%MOD*powq(b-a,m-x)
        %MOD*invp%MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    prepare();
    while (t--)
    {
        cin>>n>>m>>c>>a>>b;
        cout<<compute()<<'\n';
    }
    return 0;
}
