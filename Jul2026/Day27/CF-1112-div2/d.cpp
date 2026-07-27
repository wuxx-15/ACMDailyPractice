#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const ll MOD=998'244'353;
const int MAXN=1000005;
int arr[MAXN];
int p[MAXN];

ll lval[MAXN];
ll rval[MAXN]; //n在哪里

ll frac[MAXN];
ll inv[MAXN];
int n;
bool existed[MAXN];

int key[MAXN];
int cntk;

struct event
{
    int val;
    int gap;
};
bool eventCmp(const event& e1,const event& e2)
{
    return e1.val < e2.val;
}

vector<event> events;
vector<int> leftPos;
vector<int> rightPos;

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

void prepare()
{
    frac[0]=1;
    for (int i=1;i<=1000000;++i)
        frac[i]=frac[i-1]*i%MOD;
    inv[1000000]=powq(frac[1000000],MOD-2);
    for (int i=1000000-1;i>=0;--i)
        inv[i]=inv[i+1]*(i+1)%MOD;
}

ll A(int n,int m)
{
    assert(m>=0 && n>=m);
    return frac[n]*inv[n-m]%MOD;
}

ll compute()
{
    /*
    arr先不递减再不递增，必有最大值n-1,没有n,
    排列中n和n-1只能出现在两个边界上
    */
    bool ismax=false; //有没有n-1
    bool isup=true;
    int prev=0;
    for (int i=1;i<n;++i)
    {
        if (arr[i]==n) return 0;
        if (arr[i]==n-1) ismax=true;
        if (arr[i]>prev)
        {
            if (!isup) return 0;
        }
        else if (arr[i]<prev)
        {
            isup=false;
        }
        prev=arr[i];
    }
    if (!ismax) return 0;

    int lbound=1;
    int rbound=n-1;
    while (arr[lbound] != n-1) ++lbound; //n,n-1
    while (arr[rbound] != n-1) --rbound;
    ++rbound;

    memset(existed,0,sizeof(existed));
    for (int i=1;i<lbound;++i)
        existed[arr[i]]=true;
    for (int i=n;i>=rbound;--i)
    {
        if (existed[arr[i]]) return 0;
    }

    memset(p,0,sizeof(p));
    prev=0;
    for (int i=1;i<lbound;++i)
    {
        if (arr[i]>prev) 
        {
            p[i]=arr[i];
            prev=arr[i];
        }
    }
    prev=0;
    for (int i=n-1;i>=rbound;--i)
    {
        if (arr[i]>prev)
        {
            p[i+1]=arr[i];
            prev=arr[i];
        }
    }

    events.clear();
    //左侧固定点
    leftPos.clear();
    for (int i=1;i<lbound;++i)
    {
        if (p[i] != 0) leftPos.push_back(i);
    }
    for (int i=0;i<leftPos.size();++i)
    {
        int pos=leftPos[i];
        int nx;

        if (i+1<leftPos.size())
            nx=leftPos[i+1];
        else
            nx=lbound;
        events.emplace_back(p[pos],nx-pos-1);
    }

    //右侧固定点
    rightPos.clear();
    for (int i=n;i>rbound;--i)
    {
        if (p[i] != 0)
            rightPos.push_back(i);
    }
    for (int i=0;i<rightPos.size();++i)
    {
        int pos=rightPos[i];
        int nx;

        if (i+1<rightPos.size())
            nx=rightPos[i+1];
        else
            nx=rbound;
        events.emplace_back(p[pos],pos-nx-1);
    }

    sort(events.begin(),events.end(),eventCmp);

    ll ret=2; //n,n-1只能放在lbound,rbound上
    int fixed=0;

    for (const auto& e:events)
    {
        int cur=e.val;
        int gap=e.gap;

        int free=cur-1-fixed;

        if (free<gap) return 0;

        ret=ret*A(free,gap)%MOD;
        fixed+=gap+1;
    }

    ret=ret*frac[rbound-lbound-1]%MOD;

    return ret;
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
        cin>>n;
        for (int i=1;i<n;++i) cin>>arr[i];
        arr[n]=0;
        cout<<compute()<<'\n';
    }
    return 0;
}
