/*
其实这题压根不用CDQ分治，避免不了枚举，时间复杂度还是O(m*n)
对x排了序记录每行上的ymin,ymax即可
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXS=1000001;
const int NA=1e9;
vector<vector<int>> mark;
struct Node
{
    int x,y,val;
};
Node arr[MAXS];
bool cmpV(const Node& n1,const Node& n2)
{
    return n1.val<n2.val;
}
bool cmpX(const Node& n1,const Node& n2)
{
    if (n1.x != n2.x) return n1.x<n2.x;
    return n1.y<n2.y;
}
bool cmpY(const Node& n1,const Node& n2)
{
    return n1.y<n2.y;
}

struct Vertex
{
    int x;
    int y;
};
//Stack
Vertex upLeft[MAXS];
int cntu;
Vertex downRight[MAXS];
int cntd;

int n,m;

int id(int x,int y)
{
    return (x-1)*m+y;
}

void edit(int x1,int y1,int x2,int y2)
{
    if (x1 >= x2 || y1>=y2) return;
    ++mark[x1][y1];
    ++mark[x2+1][y2+1];
    --mark[x1][y2+1];
    --mark[x2+1][y1];
}

void merge(int l,int mid,int r)
{
    int p1,p2;
    cntu=cntd=0;
    upLeft[++cntu].x=arr[l].x;
    upLeft[cntu].y=arr[l].y;
    for (int i=l+1,x,y;i<=mid;++i)
    {
        x=arr[i].x;
        y=arr[i].y;
        if (x<upLeft[cntu].x)
        {
            upLeft[++cntu].x=x;
            upLeft[cntu].y=y;
        }
    }
    downRight[++cntd].x=arr[r].x;
    downRight[cntd].y=arr[r].y;
    for (int i=r-1,x,y;i>mid;--i)
    {
        x=arr[i].x;
        y=arr[i].y;
        if (x>downRight[cntd].x)
        {
            downRight[++cntd].x=x;
            downRight[cntd].y=y;
        }
    }
    for (int i=1;i<=cntu;++i)
    {
        for (int j=1;j<=cntd;++j)
        {
            edit(upLeft[i].x,upLeft[i].y,downRight[j].x,downRight[j].y);
        }
    }
    stable_sort(arr+l,arr+r+1,cmpY);
}

void CDQ(int l,int r)
{
    if (l==r) return;
    int mid=l+r>>1;
    CDQ(l,mid);
    CDQ(mid+1,r);
    merge(l,mid,r);
}

void solve()
{
    sort(arr+1,arr+n*m+1,cmpV);
    for (int l=1,r=1;r<=n*m;l=++r)
    {
        int cur=arr[l].val;
        while (r+1<=n*m && arr[r+1].val==cur)
        {
            ++r;
        }
        if (l==r) continue;
        sort(arr+l,arr+r+1,cmpX);
        CDQ(l,r);
    }
    for (int i=2;i<=n;++i) mark[i][1]+=mark[i-1][1];
    for (int i=2;i<=m;++i) mark[1][i]+=mark[1][i-1];
    for (int i=2;i<=n;++i)
    {
        for (int j=2;j<=m;++j)
        {
            mark[i][j]+=mark[i-1][j]+mark[i][j-1]-mark[i-1][j-1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    mark.assign(n+2,vector<int>(m+2,0));
    for (int i=1,id=1;i<=n;++i)
    {
        for (int j=1;j<=m;++j,++id)
        {
            cin>>arr[id].val;
            arr[id].x=i;
            arr[id].y=j;
        }
    }
    solve();
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=m;++j)
        {
            if (mark[i][j]>0)
                cout<<1;
            else
                cout<<0;
        }
        cout<<'\n';
    }
    return 0;
}
