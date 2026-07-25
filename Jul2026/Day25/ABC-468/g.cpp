#include <iostream>
#include <string>
#define ll long long
using namespace std;
const ll MOD=998'244'353;
const int MAXN=2001;
string str;
int n;
ll frac[MAXN];
ll val[MAXN]; //1,2...n排列只有1~1,1~n的连续子串，1~2,..,1~n-1不连续
void prepare()
{
    frac[0]=1;
    for (int i=1;i<=n;++i) frac[i]=frac[i-1]*i%MOD;
    val[1]=1;
    val[2]=2;
    for (int i=3;i<=n;++i)
    {
        val[i]=frac[i]; //全排列数
        for (int j=2;j<i;++j)
            val[i]=(val[i]+MOD-val[j]*frac[i-j+1]%MOD)%MOD; //减去1,2..j形成连通块的情况
    }
}
ll compute()
{
    if (str[1]=='x' || str[n]=='x') return 0;
    ll ret=1;
    for (int l=1,r=2;r<=n;l=r++)
    {
        while (str[r]=='x') ++r;
        ret=ret*val[r-l+1]%MOD;
    }
    return ret;
}
int main()
{
    cin>>n;
    prepare();
    cin>>str;
    str.insert(0,"#");
    cout<<compute();
    return 0;
}
