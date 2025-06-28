// 输入一组矩阵连乘的次序，求出最优的计算次序
// 采用动态规划的方法

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void matrix_chain_order(vector<int> &p, vector<vector<int>> &m, vector<vector<int>> &s){
    int n = p.size() - 1;
    for(int i = 0; i < n; i++){
        m[i][i] = 0;
    }
    for(int l = 2; l <= n; l++){
        for(int i = 0; i < n - l + 1; i++){
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for(int k = i; k < j; k++){
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parens(vector<vector<int>> &s, int i, int j){
    if(i == j){
        cout << "A" << i + 1;
    }else{
        cout << "(";
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main()
{
    vector<int> p = {7, 4, 20, 12, 5, 35, 17, 13, 3, 30};
    vector<vector<int>> m(p.size() - 1, vector<int>(p.size() - 1, 0));
    vector<vector<int>> s(p.size() - 1, vector<int>(p.size() - 1, 0));
    matrix_chain_order(p, m, s);
    cout << "m:" <<endl;
    for(int i = 0; i < p.size() - 1; i++){
        for(int j = 0; j < p.size() - 1; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << "s:" << endl;
    for(int i = 0; i < p.size() - 1; i++){
        for(int j = 0; j < p.size() - 1; j++){
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
    print_optimal_parens(s, 0, p.size()-2);
    return 0;
}