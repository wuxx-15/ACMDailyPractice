#include <iostream>
using namespace std;
const int MAXN=200005;
const int MAXV=1<<18;
const int BIT=17;
int n;
int arr[MAXN];
int preXor[MAXN];

int Stack[MAXN];
int l_bound[MAXN];
int r_bound[MAXN];

int remain[MAXN];
int pos[MAXV];

bool check(int mask)
{
    for (int i=0;i<=n;++i)
        remain[i]=preXor[i] & mask;
    for (int i=0;i<=n;++i)
    {
        pos[remain[i]]=-1;
        pos[remain[i]^mask]=-1;
    }
    for (int i=1;i<=n;++i)
    {
        int lastPos=pos[remain[i-1]];
        pos[remain[i-1]]=i-1;
        if ((arr[i] & mask) != mask)
            continue;
        int l_len=i-l_bound[i]+1;
        int r_len=r_bound[i]-i+1;
        if (l_len <= r_len)
            continue;
        for (int j=i;j<=r_bound[i];++j)
        {
            int k =pos[remain[j]^mask];
            if (j==i && k==i-1) //去除l==r的情况
                k=lastPos;
            if (k >= l_bound[i]-1)
                return true;
        }
    }
    for (int i=0;i<=n;++i)
    {
        pos[remain[i]]=n+1;
        pos[remain[i]^mask]=n+1;
    }
    for (int i=n;i>=1;--i)
    {
        int lastPos=pos[remain[i]];
        pos[remain[i]]=i;
        if ((arr[i] & mask) != mask)
            continue;
        int l_len=i-l_bound[i]+1;
        int r_len=r_bound[i]-i+1;
        if (l_len > r_len)
            continue;
        for (int j=l_bound[i]-1;j<=i-1;++j)
        {
            int k=pos[remain[j]^mask];
            if (j==i-1 && k==i)
                k=lastPos;
            if (k <= r_bound[i])
                return true;
        }
    }
    return false;
}

int solve()
{
    for (int i=1;i<=n;++i)
        preXor[i]=preXor[i-1]^arr[i];
    int top=0;
    for (int i=1;i<=n;++i)
    {
        while (top > 0 && arr[Stack[top]] < arr[i])
            --top;
        l_bound[i] = top==0 ? 1:Stack[top]+1;
        Stack[++top]=i;
    }
    top=0;
    for (int i=n;i>=1;--i)
    {
        while (top > 0 && arr[Stack[top]] <= arr[i])
            --top;
        r_bound[i] = top==0 ? n:Stack[top]-1;
        Stack[++top]=i;
    }
    int ans=0;
    for (int b=BIT;b >= 0;--b) //按位贪心
    {
        int mask = ans | (1<<b);
        if (check(mask))
            ans = mask;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i=1;i<=n;++i)
            cin>>arr[i];
        int ans=solve();
        cout<<ans<<'\n';
    }
    return 0;
}
