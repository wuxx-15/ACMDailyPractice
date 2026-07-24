#include <iostream>
#include <vector>
#include <cstring>
#define ll long long
using namespace std;

typedef vector<vector<ll>> mat;
const int MAXN=10;
const int MAXS=1<<7;
const int MAXP=19683;
const ll MOD=998'244'353;
int pow3[MAXN];

mat base;

int n,m;

int stateNum; //状态数

int states[MAXS];
int id[MAXP];
int cnts=0;

void prepare()
{
    pow3[0]=1;
    for (int i=1;i<10;++i)
        pow3[i]=pow3[i-1]*3;
}

int getbit(int x,int bit)
{
    if (bit < 0) return -1;
    return x / pow3[bit] % 3;
}

int setbit(int x,int bit,int v)
{
    int v0=getbit(x,bit);
    return x+pow3[bit]*(v-v0);
}

//压缩状态数，不然TLE
int formalize(int bitmask)
{
    int mapping[3]={-1,-1,-1};
    int nextColor=0;
    int result=0;

    for (int i=0;i<n;++i)
    {
        int color=getbit(bitmask,i);

        if (mapping[color]==-1)
            mapping[color]=nextColor++;
        
        result+=mapping[color]*pow3[i];
    }
    return result;
}

void dfs2(int bitmask,int v,int i)
{
    if (i==n) 
    {
        v=formalize(v);
        ++base[id[v]][id[bitmask]];
        return;
    }
    for (int b=0;b<3;++b)
    {
        if (b != getbit(bitmask,i) && b != getbit(v,i-1))
        {
            dfs2(bitmask,setbit(v,i,b),i+1);
        }
    }
}

void dfs1(int bitmask,int i)
{
    if (i==n)
    {
        bitmask=formalize(bitmask);
        if (id[bitmask]==-1)
        {
            id[bitmask]=cnts;
            states[cnts++]=bitmask;
        }
        return;
    }
    for (int b=0;b<3;++b)
    {
        if (b != getbit(bitmask,i-1))
            dfs1(setbit(bitmask,i,b),i+1);
    }
}

mat multiply(const mat& m1,const mat& m2)
{
    mat ret(stateNum,vector<ll>(stateNum,0));
    for (int i=0;i<stateNum;++i)
    {
        for (int j=0;j<stateNum;++j)
        {
            for (int k=0;k<stateNum;++k)
            {
                ret[i][j]=(ret[i][j]+m1[i][k]*m2[k][j]%MOD)%MOD;
            }
        }
    }
    return ret;
}

mat powq(mat& base,int p)
{
    mat ret(stateNum,vector<ll>(stateNum,0));
    for (int i=0;i<stateNum;++i) ret[i][i]=1;
    while (p > 0)
    {
        if (p & 1) ret=multiply(ret,base);
        base=multiply(base,base);
        p >>= 1;
    }
    return ret;
}

ll powq(ll base,int p)
{
    ll ret=1;
    while (p > 0)
    {
        if (p & 1) ret=ret*base%MOD;
        base=base*base%MOD;
        p>>=1;
    }
    return ret;
}

ll compute()
{
    if (n==1) return 3*powq(2,m-1)%MOD;
    if (n==2) return 6*powq(3,m-1)%MOD;
    stateNum=1<<n-2;
    base.assign(stateNum,vector<ll>(stateNum,0));
    memset(id,-1,sizeof(id));
    dfs1(0,0); 
    for (int i=0;i<cnts;++i)
    {
        dfs2(states[i],0,0);
    }
    // for (int i=0;i<stateNum;++i)
    // {
    //     for (int j=0;j<stateNum;++j)
    //         cout<<base[i][j]<<' ';
    //     cout<<'\n';
    // }

    auto pmat=powq(base,m-1);
    ll ret=0;
    for (int i=0;i<stateNum;++i)
    {
        for (int j=0;j<stateNum;++j)
        {
            ret=(ret+pmat[i][j])%MOD;
        }
    }
    return 6*ret%MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    prepare();
    cin>>n>>m;
    cout<<compute();
    return 0;
}
