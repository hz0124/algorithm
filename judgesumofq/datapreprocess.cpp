#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <climits>
#include <stdio.h>
#include <chrono>
#include <cmath>

using namespace std;

int GetFirstState(vector<int> &firststate, vector<vector<int>> value, int begin){
    firststate.clear();
    int size_value = value.size();
    int sum_of_square = 0;
    int i = 0;
    while(sum_of_square < 200000000){
        firststate.push_back(i + begin);
        sum_of_square += pow(value[i + begin][1], 2);
        i++;
    }
    sum_of_square -= pow(value[i + begin - 1][1], 2);
    return (200000000 - sum_of_square);
}

int main()
{
    vector<vector<int>> value;
    int a, b;
    FILE *fp = fopen("vars.dat", "r");
    while(fscanf(fp, "%d %d", &a, &b) != EOF){
        vector<int> temp;
        temp.push_back(a);
        temp.push_back(b);
        value.push_back(temp);
    }
    fclose(fp);
    int size_value = value.size();
    cout << "size_value: " << size_value << endl;
    cout << "size_value[0]: " << value[0].size() << endl;
    vector<int> firststate;
    vector<int> T_sum;

    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dis(0, size_value - 1);
    vector<int> temp;
    for(int i = 0;i < 10; i++){
        temp.push_back(GetFirstState(firststate, value, i));
    }
    // 求temp方差
    int sum = 0;
    for(int i = 0; i < 10; i++){
        sum += temp[i];
    }
    int mean = sum / 10;
    long long int sum_of_square = 0;
    for(int i = 0; i < 10; i++){
        sum_of_square += pow(temp[i] - mean, 2);
    }
    int std = sqrt(sum_of_square / 10);
    cout << "标准差: " << std << endl;
    temp[0] = GetFirstState(firststate, value, 0);
    cout << "firststate.size: " << firststate.size() << endl;
    cout << "temp: " << temp[0] << endl;

}