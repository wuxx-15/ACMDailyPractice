#include <iostream>
#include <unordered_map>
using namespace std;
int n;
const int MAXN=100001;
int arr[MAXN];

//可能的最佳目标值
int choice[MAXN];
int cntc;

//统计中间状态出现次数
unordered_map<int,int> stateCnt;

int f1(int num,int tar)
{
    int ret=0;
    if (++stateCnt[num]==n) 
        choice[++cntc]=num;
    while (num != tar)
    {
        ++ret;
        if (num & 1) ++num;
        else num/=2;
        if (++stateCnt[num]==n) 
            choice[++cntc]=num;
    }
    return ret;
}

int f2(int num,int tar)
{
    int ret=0;
    while (num != tar)
    {
        ++ret;
        if (num & 1) ++num;
        else num/=2;
    }
    return ret;
}

int compute()
{
    cntc=0;
    stateCnt.clear();
    int ans;
    int tmp=0;
    int tar=1;
    for (int i=1;i<=n;++i)
    {
        tmp += f1(arr[i],tar);
    }
    ans=tmp;

    tar=2;
    tmp=0;
    for (int i=1;i<=n;++i)
    {
        tmp+=f2(arr[i],tar);
    }
    ans=min(ans,tmp);

    for (int i=1;i<=cntc;++i)
    {
        tar=choice[i];
        tmp=0;
        for (int i=1;i<=n;++i)
        {
            tmp += f2(arr[i],tar);
        }
        ans=min(ans,tmp);
    }
    return ans;
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
            cin>>arr[i];
        cout<<compute()<<'\n';
    }
    return 0;
}
