#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=300001;
int n;
int a[MAXN];
int b[MAXN];
int ab[MAXN<<1];
int c[MAXN<<1];

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

bool check()
{
    solve();
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i)
    {
        if (a[i] != i) return false;
        ab[i]=a[i];
    }
    int lb=(n+1)/2;
    for (int i=1;i<=lb;++i)
        ab[i+n]=b[i];
    int len=n+lb;
    sort(ab+1,ab+len+1);
    sort(c+1,c+len+1);
    for (int i=1;i<=len;++i)
    {
        if (ab[i] != c[i]) return false;
    }
    return true;
}

int main(int argc,char** argv)
{
    ifstream fin1(argv[1]);
    ifstream fin2(argv[2]);

    int t;
    fin1>>t;
    while (t--)
    {
        fin1>>n;
        int len=(3*n+1)/2;
        for (int i=1;i<=len;++i)
            fin1>>c[i];
        fin2>>a[1];
        if (a[1] == -1) return 1;
        for (int i=2;i<=n;++i)
        {
            fin2>>a[i];
        }
        if (!check()) return 1;
    }
    return 0;
}
