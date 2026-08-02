#include <iostream>
#include <string>
#include <cstring>
using namespace std;
const int MAXN=200005;
int n,q;
string s,t;
int precnt[MAXN][4]; //11,10,01,00
int tmpcnt[4];

void prepare()
{
    memset(precnt,0,sizeof(precnt));
    for (int i=1;i<=n;++i)
    {
        int b=0;
        if (s[i]=='1') b+=2;
        if (t[i]=='1') ++b;
        ++precnt[i][b];
    }
    for (int i=1;i<=n;++i)
    {
        for (int b=0;b<4;++b)
            precnt[i][b]+=precnt[i-1][b];
    }   
}

bool solve(int l,int r)
{
    for (int b=0;b<4;++b)
        tmpcnt[b]=precnt[r][b]-precnt[l-1][b];
    bool ret=true;
    int need=0;
    need+=abs(tmpcnt[1]-tmpcnt[2]);
    return tmpcnt[0]+tmpcnt[3]>=need;
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
        cin>>n>>q;
        cin>>s>>t;
        s.insert(0,"#");
        t.insert(0,"#");
        prepare();
        int l,r;
        while (q--)
        {
            cin>>l>>r;
            if (solve(l,r)) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}
