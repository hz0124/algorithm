# include <iostream>
# include <vector>
# include <algorithm>
# include <cstdlib>
# include <stdio.h>
# include <chrono>

using namespace std;
using namespace std::chrono;

void sort(vector<vector<int>>& num)
{
    int size = num.size();
    for (int i = 2; i < size; i++)
    {
        for(int j = i; j >= 1; j--){
            if(num[j][1] > num[j-1][1])
            {
                swap(num[j][1], num[j-1][1]);
                swap(num[j][0], num[j-1][0]);
            }
            else
            {
                break;
            }
        }
    }
}
vector<int> findbestshop(vector<vector<int>>& value)
{
    int money = value[0][1];
    int size = value.size();
    cout<<"size = "<<size<<endl;
    cout<<"money = "<<money<<endl;
    vector<int> result(size-1);
    cout<<"result.size() = "<<result.size()<<endl;
    int **dp = new int*[size-1];
    for(int i = 0; i < size-1; i++)
    {
        dp[i] = new int[money+1];
        for(int j = 0; j <= money; j++)
        {
            dp[i][j] = 0;
        }
    }
    for(int i = 0; i <= money; i++)
    {
        if(i < value[1][1])
        {
            dp[0][i] = 0;
        }
        else
        {
            dp[0][i] = value[1][1];
        }
    }
    for(int i = 1; i < size-1; i++)
    {
        dp[i][0] = 0;
        for(int j = 1; j <= money; j++)
        {
            if(j < value[i+1][1])
            {
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-value[i+1][1]] + value[i+1][1]);
            }
        }
    }
    int i = size-2;
    int j = money;
    while(i>0)
    {
        if(dp[i][j] == dp[i-1][j])
        {
            result[i] = 0;
        }
        else
        {
            result[i] = 1;
            j = j - value[i+1][1];
        }
        i--;
    }
    if(dp[i][j] == 0)
    {
        result[i] = 0;
    }
    else
    {
        result[i] = 1;
    }
    cout<<"剩余钱数为："<<money-dp[size-2][money]<<endl;
    for (int i = 0; i < size-1; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return result;

}

int main()
{
    //读入data1.dat文件至vector<vector<int>> value
    FILE *fp = fopen("data2.dat", "r");
    vector<vector<int>> value;
    int a, b;
    while(fscanf(fp, "%d %d", &a, &b) != EOF)
    {
        vector<int> temp;
        temp.push_back(a);
        temp.push_back(b);
        value.push_back(temp);
    }
    fclose(fp);
    cout << "value.size() = " << value.size() << endl;
    cout << "value[0].size() = " << value[0].size() << endl;
    //对value按照value[i][1]排序
    /*sort(value);
    cout << "After sort:" << endl;
    for(int i = 0; i < 4; i++)
    {
        cout << value[i][0] << " " << value[i][1] << endl;
    }*/
    //计时
    auto start = high_resolution_clock::now();
    //调用findbestshop函数
    vector<int> result = findbestshop(value);
    //输出结果
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    for(int i = 0; i < value.size()-1; i++)
    {
        if(result[i]==1)
            cout<<"shop "<<value[i+1][0]<<" ";
    }
    return 0;     
}