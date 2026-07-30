#include <iostream>
#include <chrono>
#include <random>
#include <queue>
using namespace std;
const int MAXN=300005;
int n,len;
int a[MAXN];
int b[MAXN>>1];
priority_queue<int,vector<int>,greater<int>> minheap;
priority_queue<int> maxheap;

void solve()
{
    for (int i=1;i<=n;++i)
    {
        if (i & 1)
        {
            minheap.push(a[i]);
            int tmp=minheap.top();
            minheap.pop();
            maxheap.push(tmp);
            int id=(i+1)/2;
            b[id]=maxheap.top();
        }
        else
        {
            maxheap.push(a[i]);
            int tmp=maxheap.top();
            maxheap.pop();
            minheap.push(tmp);
        }
    }
    while (!minheap.empty()) minheap.pop();
    while (!maxheap.empty()) maxheap.pop();
}
int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> int_v1(99999,299999);
    int t=1;
    cout<<t<<'\n';
    //构造一定能构造成功的例子
    while (t--)
    {
        n=int_v1(rng);
        while (n % 2 == 0) 
            n=int_v1(rng);
        cout<<n<<'\n';
        len=(3*n+1)/2;
        for (int i=1;i<=n;++i)
            a[i]=i;
        shuffle(a+1,a+n+1,rng);
        for (int i=1;i<=n;++i)
            cout<<a[i]<<' ';
        solve();
        int lb=(n+1)/2;
        shuffle(b+1,b+lb+1,rng);
        for (int i=n+1;i<=len;++i)
            cout<<b[i-n]<<' ';
        cout<<'\n';
    }
    return 0;
}
