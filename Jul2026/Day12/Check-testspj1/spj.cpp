#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
using namespace std;
int main()
{
    //随机数生成
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> int_v1(1,1000);
    int n=int_v1(rng);
    cout<<n<<' ';
    uniform_int_distribution<int> int_v2(1,n);
    int k=int_v2(rng);
    cout<<k<<'\n';
    for (int i=1,tmp;i<=n;++i)
    {
        tmp=int_v2(rng);
        cout<<tmp<<' ';
    }
    return 0;
}
