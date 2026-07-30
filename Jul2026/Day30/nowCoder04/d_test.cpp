#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;
int n;
vector<int> p;

vector<int> normalize()
{
    int pos=find(p.begin(),p.end(),1)-p.begin();
    vector<int> res;
    for (int i=0;i<n;++i)
        res.push_back(p[(pos+i)%n]);
    return res;
}

bool used[15];

vector<int> dfs(int dep)
{
    if (dep==n) return normalize();
    bool alice=(dep%2==0);
    vector<int> best;
    bool first=true;

    for (int x=1;x<=n;++x)
    {
        if (used[x]) continue;
        used[x]=true;
        p.push_back(x);

        vector<int> now=dfs(dep+1);

        p.pop_back();
        used[x]=false;

        if (first || (alice && now<best) ||
        (!alice && now>best))
        {
            best=move(now);
            first=false;
        }
    }
    return best;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (n=1;n<=11;++n)
    {
        memset(used,false,sizeof(used));
        p.clear();

        vector<int> ans=dfs(0);

        cout<<setw(3)<<n<<": ";
        for (int x:ans) cout<<x<<' ';
        cout<<'\n';
    }
}
