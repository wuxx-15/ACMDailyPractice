#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=200005;
const int BIT=30;
int n;
int a[MAXN];
int b[MAXN];
/*
如果先后对索引i,j*(i != j)操作
对任意的k != i,k != j
a[k]->a[k]^a[i]^(a[k]^a[j])==a[k]^a[j]
a[i]->a[i]^a[j]
a[j]->a[j]
相当于只对索引j做了操作，但改变了元素次序（元素种类上没变化）
如果元素种类上a,b相同，则先后对i,j,i,j操作即可改变a[i],a[j]相对次序，完成元素交换
可见，交换元素可以对多个索引按一定次序做偶数步操作完成
如果要改变元素种类，则对一种（对多个索引做也等效为对1个索引做）元素做奇数次（1次）操作
由于n是偶数，可确定带操作的索引（可能不存在，返回NO）
最后检查元素种类
*/
bool solve()
{
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    bool same=true;
    for (int i=1;i<=n;++i)
    {
        if (a[i] != b[i])
        {
            same=false;
            break;
        }
    }
    if (same) return true;
    int xora=0;
    int xorb=0;
    for (int i=1;i<=n;++i)
    {
        xora ^= a[i];
        xorb ^= b[i];
    }
    int xorv=xorb ^ xora;
    int pos=-1;
    for (int i=1;i<=n;++i)
    {
        if (a[i]==xorv)
        {
            pos=i;
            break;
        }
    }
    if (pos==-1) return false;
    for (int i=1;i<=n;++i)
    {
        if (i != pos) 
            a[i]^=xorv;
    }
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    while (t--)
    {
        cin>>n;
        for (int i=1;i<=n;++i)
            cin>>a[i];
        for (int i=1;i<=n;++i)
            cin>>b[i];
        if (solve()) cout<<"YES\n";
        else cout<<"NO\n"; 
    }
    return 0;
}
