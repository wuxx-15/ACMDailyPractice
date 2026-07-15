#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN=200001;
int n;
int val[MAXN];
int parent[MAXN];
struct NodeInfo
{
    int min_val;
    int max_val;
    int leafsize;
    bool isvalid;
};
//Graph
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cntg;
void addEdge(int u,int v)
{
    Next[cntg]=head[u];
    head[u]=cntg;
    to[cntg++]=v;
}
NodeInfo dfs(int u)
{
    if (val[u]>0) return {val[u],val[u],1,true}; //叶节点
    int total_size=0;
    int minv=1e9;
    int maxv=-1e9;
    vector<NodeInfo> children; //注意，不能设为全局数组（除非额外维护索引）
    for (int e=head[u],v;e != 0;e=Next[e])
    {
        v=to[e];
        auto res=dfs(v);
        if (!res.isvalid) return {0,0,0,false}; //非法情况
        children.push_back(res);
        total_size+=res.leafsize;
        minv=min(minv,res.min_val);
        maxv=max(maxv,res.max_val);
    }
    if (maxv-minv+1 != total_size) //必须连续
        return {0,0,0,false};
    int dropcnt=0; //下降突变计数
    int k=children.size();
    for (int i=0;i<k;++i)
    {
        if (children[i].max_val>children[(i+1)%k].min_val) ++dropcnt;
    }
    if (dropcnt>1) return {0,0,0,false};
    return {minv,maxv,total_size,true}; 
}
bool solve()
{
    auto ret=dfs(1);
    return ret.isvalid;
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
        for (int i=2;i<=n;++i) cin>>parent[i];
        for (int i=1;i<=n;++i) cin>>val[i];
        memset(head,0,sizeof(head));
        cntg=1;
        //倒着建图是为了以后在遍历子树时可以从左到右遍历
        for (int i=n;i>=2;--i) addEdge(parent[i],i);
        if (solve()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
