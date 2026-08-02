#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int MAXN=200005;
int n,m;
struct game
{
    int x,y;
    game()=default;
    game(int x,int y):x(x),y(y){}
    friend bool operator==(const game& g1,const game& g2)
    {
        return g1.x == g2.x && g1.y == g2.y;
    }
};

bool cmp(const game& g1,const game& g2)
{
    if (g1.x != g2.x) return g1.x < g2.x;
    return g1.y<g2.y;
}

game games[MAXN];

bool test(int a,int b)
{
    for (int i=1,x,y;i<=m;++i)
    {
        x=games[i].x;
        y=games[i].y;
        if (x != a && x != b && y != a && y != b)
            return false;
    }
    return true;
}

vector<game> Valids;

void addAns(int a,int b)
{
    if (a>b) swap(a,b);
    Valids.emplace_back(a,b);
}

void solve(int a)
{
    int s1=0,s2=0;
    for (int i=2,x,y;i<=m;++i)
    {
        x=games[i].x;
        y=games[i].y;
        if (x != a && y != a)
        {
            s1=x;
            s2=y;
            break;
        }
    }
    if (s1 == 0)
    {
        for (int i=1;i<=n;++i)
        {
            if (i != a) 
                addAns(i,a);
        }
    }
    else
    {
        if (test(a,s1)) addAns(a,s1);
        if (test(a,s2)) addAns(a,s2);
    }
}

ll compute()
{
    int a=games[1].x;
    int b=games[1].y;
    solve(a);
    solve(b);
    sort(Valids.begin(),Valids.end(),cmp);
    auto it=unique(Valids.begin(),Valids.end());
    Valids.erase(it,Valids.end());
    return Valids.size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    for (int i=1,x,y;i<=m;++i)
    {
        cin>>x>>y;
        games[i].x=x;
        games[i].y=y;
    }
    cout<<compute();
    return 0;
}
