#include <iostream>
#define ll long long
using namespace std;
const int MAXN=200005;
const int MAXV=1000000;
int n;
int arr[MAXN];
bool emerged[MAXV+1];
//DSU
int father[MAXV+1];

int find(int x)
{
    if (x != father[x]) father[x]=find(father[x]);
    return father[x];
}

ll compute()
{
    ll ret=0;
    int cnt=0;
    for (int i=1;i<=MAXV;++i)
        father[i]=i;
    //从大到小枚举gcd
    for (int gcd=MAXV;gcd>=1;--gcd)
    {
        int lastNum=0;
        for (int j=1;j*gcd<=MAXV;++j)
        {
            if (emerged[j*gcd])
            {
                if (lastNum)
                {
                    int f1=find(lastNum);
                    int f2=find(j*gcd);
                    if (f1 != f2)
                    {
                        father[f1]=f2;
                        ret+=gcd;
                        if (++cnt==n-1) return ret;
                    }    
                }
                lastNum=j*gcd;
            }
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for (int i=1,v;i<=n;++i)
    {
        cin>>v;
        emerged[v]=true;
    }
    cout<<compute()<<'\n';
    return 0;
}
