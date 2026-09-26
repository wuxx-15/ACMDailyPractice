#include <iostream>
#include <string>
#define ll long long
using namespace std;
int n,q;
string str;
ll curAns;
int one=0;
int zero=0;

//B(L,R)=(c(L,R)+(str[L] != str[R]))/2
void prepare()
{
    curAns=0;
    one=0;
    zero=0;
    if (n==1)
        return;
    for (int i=1;i<=n;++i)
    {
        if (str[i]=='0')
            ++zero;
        else
            ++one;
    }
    for (int i=1;i<n;++i)
    {
        if (str[i] != str[i+1])
            curAns += 1LL*i*(n-i);
    }
}

void modify(int i)
{
    if (n==1)
        return;
    if (i > 1 && str[i] != str[i-1])
        curAns -= 1LL*(i-1)*(n-i+1);
    if (i < n && str[i] != str[i+1])
        curAns -= 1LL*i*(n-i);
    if (str[i]=='0')
    {
        str[i]='1';
        ++one;
        --zero;
    }
    else
    {
        str[i]='0';
        --one;
        ++zero;
    }
    if (i > 1 && str[i] != str[i-1])
        curAns += 1LL*(i-1)*(n-i+1);
    if (i < n && str[i] != str[i+1])
        curAns += 1LL*i*(n-i);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> q;
        cin >> str;
        str.insert(0,"#");
        prepare();
        ll ans=(curAns+1LL*one*zero)/2;
        cout<<ans<<' ';
        int idx;
        while (q--)
        {
            cin >> idx;
            modify(idx);
            ans=(curAns+1LL*one*zero)/2;
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
