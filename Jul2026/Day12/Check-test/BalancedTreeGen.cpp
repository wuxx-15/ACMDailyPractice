#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int main()
{
    // 使用 mt19937 获得高质量随机数
    random_device rd;
    mt19937 gen(rd());

    // 对拍时 N 不需要太大，1000 组数据足以揪出绝大多数 Bug，且运行极快
    int n = 1000;
    cout << n << "\n";

    vector<int> v;
    uniform_int_distribution<> dis_val(-2000, 2000);

    for (int i = 0; i < n; i++)
    {
        int op;
        if (v.empty())
        {
            op = 1; // 空树时必须插入
        }
        else
        {
            // 设定操作概率：1(插入):35%, 2(删除):25%, 3~6(查询):各10%
            uniform_int_distribution<> dis_op(1, 100);
            int r_op = dis_op(gen);
            if (r_op <= 35)
                op = 1;
            else if (r_op <= 60)
                op = 2;
            else if (r_op <= 70)
                op = 3;
            else if (r_op <= 80)
                op = 4;
            else if (r_op <= 90)
                op = 5;
            else
                op = 6;
        }

        if (op == 1)
        {
            int x = dis_val(gen);
            v.push_back(x);
            sort(v.begin(), v.end());
            cout << "1 " << x << "\n";
        }
        else if (op == 2)
        {
            uniform_int_distribution<> dis_idx(0, v.size() - 1);
            int idx = dis_idx(gen);
            int x = v[idx];
            v.erase(v.begin() + idx);
            cout << "2 " << x << "\n";
        }
        else if (op == 3)
        {
            int x = (gen() % 2 == 0) ? v[gen() % v.size()] : dis_val(gen);
            cout << "3 " << x << "\n";
        }
        else if (op == 4)
        {
            uniform_int_distribution<> dis_idx(1, v.size());
            cout << "4 " << dis_idx(gen) << "\n";
        }
        else if (op == 5)
        {
            int x = dis_val(gen);
            while (v[0] >= x)
                x = dis_val(gen);
            cout << "5 " << x << "\n";
        }
        else if (op == 6)
        {
            int x = dis_val(gen);
            while (v.back() <= x)
                x = dis_val(gen);
            cout << "6 " << x << "\n";
        }
    }
    return 0;
}
