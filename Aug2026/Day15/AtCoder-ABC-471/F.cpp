#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN=100005;
int k,n;
string nums[MAXN];

string trans(const string& str)
{
    int idx=-1;
    int len=str.length();
    for (int i=0;i<len;++i)
    {
        if (str[i] != '0')
        {
            idx=i;
            break;
        }
    }
    if (idx==-1)
        return "";
    return str.substr(idx);
}
bool cmp3(const string& s1, const string& s2)
{
    string t1 = trans(s1);
    string t2 = trans(s2);

    if (t1.length() != t2.length())
        return t1.length() > t2.length();

    return t1 > t2;
}
bool cmp(const string& s1, const string& s2)
{
    if (s1.length() != s2.length()) 
        return s1.length() > s2.length();

    return cmp3(s1, s2);
}
bool cmp2(const string& s1, const string& s2)
{
    return s1 + s2 > s2 + s1;
}

bool greaterInteger(const string& s1, const string& s2)
{
    if (s1.length() != s2.length())
        return s1.length() > s2.length();
    return s1 > s2;
}

string build(vector<string>& selected)
{
    sort(selected.begin(),selected.end(),cmp2);
    string ret;
    for (const string& str:selected)
        ret+=str;
    ret=trans(ret);
    if (ret.empty())
        return "0";
    return ret;
}
/*
INT(Sx+T)=INT(Sx)×10 ∣T∣+INT(T)
先保证位数尽可能大，还要保证首位串代表的数字尽可能大
再最优化拼接
*/

string solve()
{
    sort(nums+1,nums+n+1,cmp);
    vector<string> candidate1;
    for (int i=1;i<=k;++i)
        candidate1.push_back(nums[i]);
    int best=k;
    for (int i=k+1;i<=n;++i)
    {
        if (cmp3(nums[i],nums[best]))
            best=i;
    }
    vector<string> candidate2;
    for (int i=1;i<k;++i)
        candidate2.push_back(nums[i]);
    candidate2.push_back(nums[best]);
    string ans1=build(candidate1);
    string ans2=build(candidate2);
    return greaterInteger(ans1, ans2) ? ans1 : ans2;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>k;
    for (int i=1;i<=n;++i)
        cin>>nums[i];
    cout<<solve()<<'\n';
    return 0;
}
