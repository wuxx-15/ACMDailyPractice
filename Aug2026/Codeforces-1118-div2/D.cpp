#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define ll long long
using namespace std;
const int MAXD=6005;
const int MAXN=12005;
typedef vector<ll> state;
int n,m;
state dp[MAXN];
ll sorted[MAXN];
int cnts;
struct block
{
    ll x;
    ll y;
};
bool cmp(const block& b1,const block& b2)
{
    if (b1.x != b2.x)
        return b1.x < b2.x;
    return b1.y > b2.y;
}
block arr[MAXD];
int cntb;

int getRank(ll x)
{
    int l=1;
    int r=cnts;
    int mid;
    while (l <= r)
    {
        mid=l+r>>1;
        if (sorted[mid]==x)
            return mid;
        else if (sorted[mid]>x)
            r=mid-1;
        else 
            l=mid+1;
    }
    return -1;
}
//一次性构造准确大小的候选状态，防止vector的capacity膨胀导致MLE
state addLength(const state& s,ll len)  
{
    int pos=lower_bound(s.begin(),s.end(),len,greater<ll>())-s.begin();
    state result(s.size()+1);
    copy(s.begin(),s.begin()+pos,result.begin());
    result[pos]=len;
    copy(s.begin()+pos,s.end(),result.begin()+pos+1);
    return result;
}

vector<int> jump[MAXN];

void solve(state& ans)
{
    sort(arr+1,arr+n+m+1,cmp);
    cntb=0;
    ll maxRight=-1;
    for (int i=1;i<=n+m;++i)
    {
        if (arr[i].y <= maxRight)
            continue;
        arr[++cntb]=arr[i];
        maxRight=arr[i].y;
    }

    cnts=0;
    for (int i=1;i<=cntb;++i)
    {
        sorted[++cnts]=arr[i].x;
        sorted[++cnts]=arr[i].y;
    }
    sort(sorted+1,sorted+cnts+1);
    int backup=cnts;
    cnts=1;
    for (int i=2;i<=backup;++i)
    {
        if (sorted[cnts] != sorted[i])
            sorted[++cnts]=sorted[i];
    }

    for (int i=1;i<=cnts;++i)
        jump[i].clear();
    for (int i=1;i<=cntb;++i)
    {
        int u=getRank(arr[i].x);
        int v=getRank(arr[i].y);
        for (int l=u;l<v;++l)
        {
            for (int r=l+1;r<=v;++r)
            {
                jump[r].push_back(l);
            }
        }
    }
    for (int r=1; r<=cnts; ++r) 
    {
        sort(jump[r].begin(),jump[r].end());
        auto it=unique(jump[r].begin(),jump[r].end());
        jump[r].erase(it,jump[r].end());
    }

    dp[1].clear();
    for (int i=2;i<=cnts;++i)
    {
        state bestCandidate;
        bool useCandidate=false;
        for (int j:jump[i])
        {
            state candidate=addLength(dp[j],sorted[i]-sorted[j]);
            if (candidate > dp[i-1] &&
                (!useCandidate || candidate > bestCandidate))
            {
                bestCandidate=move(candidate);
                useCandidate=true;
            }
        }
        if (useCandidate)
            dp[i]=move(bestCandidate);
        else
            dp[i]=dp[i-1];
    }
    ans=move(dp[cnts]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin>>T;
    while (T--)
    {
        cin>>n>>m;
        int idx=0;
        for (int i=1;i<=n;++i)
        {
            ++idx;
            cin>>arr[idx].x>>arr[idx].y;
            ++arr[idx].y;
        }
        for (int i=1;i<=m;++i)
        {
            ++idx;
            cin>>arr[idx].x>>arr[idx].y;
            ++arr[idx].y;
        }
        state ans;
        solve(ans);
        cout<<ans.size()<<'\n';
        for (ll len:ans)
            cout<<len<<' ';
        cout<<'\n';
    }
    return 0;
}
