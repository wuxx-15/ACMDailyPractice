#include <iostream>
#include <array>
#include <algorithm>
/*
当k=2^m时，会形成一个大小为2^(m+1)的联通块
当 k 处于[2^m,2^(m+1)-1]范围时，图的连通块结构不会发生任何跨越性的改变
对于每一逆序（i，j），必须满足m>=msb(i xor j)
m最小值>=msb(i xor j)最大值(必要性)
当m最小值==msb(i xor j)最大值（k=2^m），可以将原数组变换为不递减数组(充分性)
*/
using namespace std;
const int MAXN=1000001;
const int BIT=20;
const int MAXD=1<<BIT;
int msb[MAXD]; //最高有效位
int diff[MAXN];
int cntd;
int n,q;

int arr[MAXN];
int minv[MAXN];
int maxv[MAXN];
int compute()
{
    if (n==1) return 0;
    for (int i=0;i<n;++i)
    {
        minv[i]=maxv[i]=arr[i];
    }
    int ret=-1;
    for (int b=0;(1<<b)<n;++b)
    {
        int base=1<<b;
        for (int i=0;i+base<n;i+=base*2)
        {
            if (maxv[i]>minv[i+base]) ret=b; //出现逆序对
            minv[i]=min(minv[i],minv[i+base]);
            maxv[i]=max(maxv[i],maxv[i+base]);
        }
    }
    return ret==-1?0:(1<<ret);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    msb[0]=-1;
    msb[1]=0;
    for (int i=2;i<MAXD;++i)
        msb[i]=msb[i>>1]+1;
    int t;
    cin>>t;
    while (t--)
    {
        cin>>n>>q;
        for (int i=0;i<n;++i) cin>>arr[i];
        cout<<compute()<<'\n';
    }
    return 0;
}
