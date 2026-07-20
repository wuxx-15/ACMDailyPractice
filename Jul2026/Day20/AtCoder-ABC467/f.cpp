//时间复杂度O((n+q)*log(n+q)+n+q)
#include <iostream>
#include <array>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=100001;
const int MAXT=200001;
int n,q;
//根据B值建立线段树
ll sum_A[MAXT<<2]; //区间内所有信件的Ai的总和
ll max_val[MAXT<<2]; //如果只考虑这个区间内的信件，按照Bi降序发送时，收到所有回复的最晚时间。
int email[MAXN][2];

int sorted[MAXT]; //离散化B值
int cnts;

int event[MAXN][3];

void up(int i)
{
    sum_A[i]=sum_A[i<<1]+sum_A[i<<1|1];
    max_val[i]=max(max_val[i<<1|1],max_val[i<<1]+sum_A[i<<1|1]);
}

int getRank(int x) //查B值排名
{
    int l=1;
    int r=cnts;
    int mid;
    while (l <= r)
    {
        mid=l+r>>1;
        if (sorted[mid]==x) return mid;
        else if (sorted[mid]>x) r=mid-1;
        else l=mid+1;
    }
    return -1;
}

void add(int jobi,int jobx,int l,int r,int i)
{
    if (l==r) 
    {
        sum_A[i]+=jobx;
        if (sum_A[i] > 0) max_val[i] = sum_A[i] + sorted[jobi]; //曾经出错！
        else max_val[i] = 0;
    }
    else
    {
        int mid=l+r>>1;
        if (mid >= jobi) add(jobi,jobx,l,mid,i<<1);
        else add(jobi,jobx,mid+1,r,i<<1|1);
        up(i);
    }
}

void build()
{
    for (int i=1,kth;i<=n;++i)
    {
        kth=getRank(email[i][1]);
        add(kth,email[i][0],1,cnts,1);
    }
}

void process1(int i,int x)
{
    int kth=getRank(email[i][1]);
    add(kth,x-email[i][0],1,cnts,1);
    email[i][0]=x;
}

void process2(int i,int x)
{
    int old_pos=getRank(email[i][1]);
    int new_pos=getRank(x);
    add(old_pos,-email[i][0],1,cnts,1);
    add(new_pos,email[i][0],1,cnts,1);
    email[i][1]=x;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>q;
    for (int i=1;i<=n;++i)
    {
        cin>>email[i][0];
    }
    for (int i=1,v;i<=n;++i)
    {
        cin>>v;
        sorted[++cnts]=v;
        email[i][1]=v;
    }
    for (int k=1,op,i,x;k<=q;++k)
    {
        cin>>op>>i>>x;
        event[k][0]=op;
        event[k][1]=i;
        event[k][2]=x;
        sorted[++cnts]=x;
    }
    sort(sorted+1,sorted+cnts+1);
    int tmp=1;
    for (int i=2;i<=cnts;++i)
    {
        if (sorted[i] != sorted[tmp])
            sorted[++tmp]=sorted[i];
    }
    cnts=tmp;
    build();
    for (int k=1,op,i,x;k<=q;++k)
    {
        op=event[k][0];
        i=event[k][1];
        x=event[k][2];
        if (op==1) process1(i,x);
        else process2(i,x);
        cout<<max_val[1]<<'\n';
    }
    return 0;
}
