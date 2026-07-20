//利用线段树支持高效的单点修改
#include <iostream>
#include <climits>
#include <cstring>
using namespace std;
const int MAXN=1000001;
const int BIT=20;
const int MAXD=1<<BIT;
int n,nx,q;
int hbit;
int arr[MAXN];
int msb[MAXD];

//Segmant Tree
int min_val[MAXD<<2];
int max_val[MAXD<<2];

int rev_count[BIT]; //根据索引的xor值的msb记录逆序对

void up(int i)
{
    int l=i<<1;
    int r=i<<1|1;
    min_val[i]=min(min_val[l],min_val[r]);
    max_val[i]=max(max_val[l],max_val[r]);
}

void build(int l,int r,int i,int bit)
{
    if (l==r) 
    {
        if (l<n)
            min_val[i]=max_val[i]=arr[l];
        else
        {
            min_val[i]=INT_MAX;
            max_val[i]=INT_MIN;
        }
    }
    else
    {
        int mid=l+r>>1;
        build(l,mid,i<<1,bit-1);
        build(mid+1,r,i<<1|1,bit-1);
        if (max_val[i<<1]>min_val[i<<1|1]) ++rev_count[bit-1];
        up(i);
    }
}

void update(int jobi,int jobv,int l,int r,int i,int bit)
{
    if (l==r) min_val[i]=max_val[i]=jobv;
    else
    {
        int mid=l+r>>1;
        bool before,after;
        before=max_val[i<<1]>min_val[i<<1|1];
        if (mid >=jobi) update(jobi,jobv,l,mid,i<<1,bit-1);
        else update(jobi,jobv,mid+1,r,i<<1|1,bit-1);
        after=max_val[i<<1]>min_val[i<<1|1];
        rev_count[bit-1]+=after-before;
        up(i);
    }
}

int compute()
{
    for (int b=hbit;b>=0;--b)
    {
        if (rev_count[b]>0) return 1<<b;
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin>>t;
    msb[0]=-1;
    msb[1]=0;
    for (int i=2;i<MAXD;++i)
        msb[i]=msb[i>>1]+1;
    while (t--)
    {
        memset(rev_count,0,sizeof(rev_count));
        cin>>n>>q;
        for (int i=0;i<n;++i)
            cin>>arr[i];
        if (n==1)
        {
            int di,dx;
            for (int i=1;i<=q;++i)
                cin>>di>>dx;
            for (int i=1;i<=q+1;++i) 
                cout<<0<<'\n';
            continue;
        }
        hbit=msb[n];
        if (n==(1<<hbit)) nx=n;
        else nx=1<<hbit+1; //扩充到2的幂
        hbit=msb[nx-1];
        build(0,nx-1,1,hbit+1);
        cout<<compute()<<'\n';
        int i,x;
        while (q--)
        {
            cin>>i>>x;
            update(i,x,0,nx-1,1,hbit+1);
            cout<<compute()<<'\n';
        }
    }
    return 0;
}
