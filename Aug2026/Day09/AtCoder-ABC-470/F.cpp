#include <iostream>
#include <string>
#define ll long long
using namespace std;
const int MAXN=200005;
const ll MOD=998'244'353;
const int ALPHA=26;
int n,m;
string str;

ll frac[MAXN];
ll inv[MAXN];

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
    for (int i=1;i<=n;++i)
        frac[i]=frac[i-1]*i%MOD;
    inv[n]=powq(frac[n],MOD-2);
    for (int i=n-1;i>=0;--i)
        inv[i]=inv[i+1]*(i+1)%MOD;
}

int father[MAXN];
int AlphaCnt[MAXN][ALPHA];

int find(int i)
{
    if (i != father[i])
        father[i]=find(father[i]);
    return father[i];
}

void merge(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if (fx != fy)
    {
        father[fy]=fx;
        for (int i=0;i<26;++i)
            AlphaCnt[fx][i]+=AlphaCnt[fy][i];
    }
}

void init()
{
    for (int i=1;i<=n;++i)
    {
        father[i]=i;
        int ch=str[i]-'a';
        AlphaCnt[i][ch]=1;
    }
}

ll compute()
{
    prepare();
    ll ret=1;
    bool half=true;
    for (int i=1;i<=n;++i)
    {
        if (father[i]==i)
        {
            int sum=0;
            for (int c=0;c<26;++c)
            {
                int v=AlphaCnt[i][c];
                if (v > 1) half=false;
                sum+=v;
                ret=ret*inv[v]%MOD;
            }
            ret=ret*frac[sum]%MOD;
        }
    }
    if (half) ret=ret*inv[2]%MOD;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    cin>>str;
    str.insert(0,"#");
    init();
    for (int i=1,a,b;i<=m;++i)
    {
        cin>>a>>b;
        merge(a,b);
    }
    cout<<compute();
    return 0;
}
