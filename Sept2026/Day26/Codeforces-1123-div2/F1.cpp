#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXC=4000005;
const int BIT=30;
const int MAXT=60005;
const int INF=1<<30;
int arr[MAXC];
int n,q;
int cntv;
int ansArr[BIT];

int trie[MAXT][2];
int pass[MAXT];
int cntn;

void insert(int num)
{
    int cur=1;
    for (int b=29;b>=0;--b)
    {
        int bit=num >> b & 1;
        if (trie[cur][bit]==0)
            trie[cur][bit]=++cntn;
        cur=trie[cur][bit];
        ++pass[cur];
    }
}

void dfs(int idx1,int idx2,int b,int val)
{
    if (idx1 == 0 || idx2 == 0)
        return;
    if (b < 0)
    {
        int cnt=0;
        if (idx1 == idx2)
            cnt=pass[idx1]*(pass[idx1]-1)/2;
        else
            cnt=pass[idx1]*pass[idx2];
        for (int i=1;i<=cnt;++i)
            arr[++cntv]=val;
        return;
    }
    int zero1=trie[idx1][0];
    int zero2=trie[idx2][0];
    int one1=trie[idx1][1];
    int one2=trie[idx2][1];
    dfs(zero1,zero2,b-1,val);
    dfs(one1,one2,b-1,val);
    if (idx1==idx2)
        dfs(zero1,one1,b-1,val | (1<<b));
    else
    {
        dfs(zero1,one2,b-1,val | (1<<b));
        dfs(one1,zero2,b-1,val | (1<<b));
    }
    if (cntv >= n) //由于递归的特性，提前剪枝是错误的，最后才能安全剪枝！
        return;
}

void calc()
{
    for (int b=0;b<BIT;++b)
    {
        int minv=INF;
        int maxv=0;
        for (int i=1;i<=n;++i)
        {
            minv=min(minv,arr[i]);
            maxv=max(maxv,arr[i]);
        }
        ansArr[b]=maxv-minv;
        memset(trie,0,sizeof(int)*(cntn+1)*2);
        memset(pass,0,sizeof(int)*(cntn+1));
        cntn=1;
        for (int i=1;i<=n;++i)
            insert(arr[i]);
        cntv=0;
        dfs(1,1,29,0);
        sort(arr+1,arr+cntv+1);
    }
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
        cin >> n >> q;
        for (int i=1;i<=n;++i)
            cin >> arr[i];  
        calc();
        int x;
        while (q--)
        {
            cin >> x;
            int ans = x < BIT ? ansArr[x] : 0;
            cout<<ans<<'\n';
        }
    }
    return 0;
}
