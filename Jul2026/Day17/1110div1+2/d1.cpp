#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN=1001;
const int MAXM=500501;
int arr[MAXN];
int query[MAXM][3];
int n,m;
//Graph
int indegree[MAXN];
int head[MAXN];
int Next[MAXM]; 
int to[MAXM];
bool sign[MAXN];
int cntg=1;
queue<int> qi;
int cntn;

void addEdge(int u,int v)
{
    Next[cntg]=head[u];
    head[u]=cntg;
    to[cntg++]=v;
    ++indegree[v];
}
bool buildGraph()
{
    for (int i = 1; i <= m; ++i)
    {
        int o = query[i][0];
        int u = query[i][1];
        int v = query[i][2];
        if (u == v) continue; 

        if (o == 1) // u + v >= 0
        {
            if (sign[u] == false && sign[v] == false) return false; 
            if (sign[u] == true && sign[v] == true) continue;   
            
            if (sign[u] == true && sign[v] == false) addEdge(v, u); // |u| > |v|
            if (sign[u] == false && sign[v] == true) addEdge(u, v); // |v| > |u|
        }
        else // o == 2, u + v < 0
        {
            if (sign[u] == true && sign[v] == true) return false;  
            if (sign[u] == false && sign[v] == false) continue;  
            
            if (sign[u] == true && sign[v] == false) addEdge(u, v); // |v| > |u|
            if (sign[u] == false && sign[v] == true) addEdge(v, u); // |u| > |v|
        }
    }
    return true;
}
bool toposort()
{
    for (int i=1;i<=n;++i)
    {
        if (indegree[i]==0) 
        {
            arr[i]=(++cntn)*(sign[i]?1:-1);
            qi.push(i);
        }
    }
    while (!qi.empty())
    {
        int cur=qi.front();
        qi.pop();
        for (int e=head[cur],v;e != 0;e=Next[e])
        {
            v=to[e]; 
            if (--indegree[v]==0) 
            {
                arr[v]=(++cntn)*(sign[v]?1:-1);
                qi.push(v);
            }
        }
    }
    return cntn==n;
}
bool solve()
{
    cntn=0;
    cntg=1;
    memset(head,0,sizeof(head));
    memset(arr,0,sizeof(arr));
    memset(indegree,0,sizeof(indegree));
    if (!buildGraph()) return false;
    return toposort();
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
        cin>>n>>m;
        for (int i=1;i<=m;++i) 
        {
            cin>>query[i][0]>>query[i][1]>>query[i][2];
            if (query[i][1]==query[i][2]) 
            {
                if (query[i][0]==1) sign[query[i][1]]=true;
                else sign[query[i][1]]=false;
            }
        }
        if (solve())
        {
            cout<<"YES\n";
            for (int i=1;i<=n;++i) cout<<arr[i]<<' ';
            cout<<'\n';
        }
        else cout<<"NO\n";
    }
    return 0;
}
