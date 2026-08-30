#include <iostream>
using namespace std;
int n;
int sign;
void query(int u,int v,int d)
{
    cout<<"? "<<u<<' '<<v<<' '<<d<<'\n';
    cout.flush();
    cin>>sign;
}
int root1;
int root2;
int maxd;
//实质：两次DFS求直径
void solve()
{
    maxd=1;
    for (int i=2;i<=n;++i)
    {
        query(1,i,maxd);
        if (sign==0)
            continue;
        root1=i;
        while (sign==1)
        {
            ++maxd;
            query(1,i,maxd);
        }
    }
    --maxd;
    for (int i=1;i<=n;++i)
    {
        if (i==root1)
            continue;
        query(root1,i,maxd);
        if (sign==0)
            continue;
        root2=i;
        while (sign==1)
        {
            ++maxd;
            query(root1,i,maxd);
        }
    }
    --maxd;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin>>T;
    while (T--)
    {
        cin>>n;
        solve();
        cout<<"! "<<root1<<' '<<root2<<' '<<maxd<<'\n';
        cout.flush();
    }
    return 0;
}
