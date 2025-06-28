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
using namespace std::chrono;

/*void GetNewStates0(vector<int> curstate, vector<int> &newstate, vector<vector<int>> value, int size_retain, int size_value){
    newstate.clear();
    int size_now = curstate.size();
    vector<int> record(size_now);
    for(int i = 0; i < size_now; i++){
        record[i] = curstate[i];
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(record.begin(), record.end(), g);
    newstate.insert(newstate.end(), record.begin(), record.begin() + size_retain);
    int new_element_least = 10 - size_retain;
    int size_add = rand() % 10 + new_element_least; // 随机生成一个大于new_element_least的整数，最为新加入的元素个数
    // 随机从value中选取size_add个元素加入newstate
    for(int i = 0; i < size_add; i++){
        int index = rand() % size_value;
        for(int j = 0; j < newstate.size(); j++){
            if(index == newstate[j]){
                index = rand() % size_value;
                j = -1;
            }
        }
        newstate.push_back(index);
    }
    
}*/

void GetNewStates(vector<int> curstate, vector<int> &newstate, vector<vector<int>> value, int size_change){
    newstate.clear();
    int size_now = curstate.size();
    int size_value = value.size();
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dis(0, size_value - 1);
    vector<bool> flag(size_now, true);
    for(int i = 0; i < size_change; i++)
    {
        int index = dis(g);
        bool flag1 = true;
        for(int j = 0; j < curstate.size(); j++){
            if(index == curstate[j]){
                flag[j] = !flag[j];
                flag1 = false;
            }
        }
        if(flag1){
            curstate.push_back(index);
            flag.push_back(true);
        }
    }
    for(int i = 0; i < curstate.size(); i++){
        if(flag[i]){
            newstate.push_back(curstate[i]);
        }
    }
    // cout << "newstate.size: " << newstate.size() << endl;
    if(newstate.size() < 10)
    {
        cout << "in" << endl;
        int size_add = 10 - newstate.size();
        for(int i = 0; i < size_add; i++){
            int index = dis(g);
            for(int j = 0; j < newstate.size(); j++){
                if(index == newstate[j]){
                    index = dis(g);
                    j = -1;
                }
            }
            newstate.push_back(index);
        }
    }

}

void GetFirstState(vector<int> &firststate, vector<vector<int>> value, int begin){
    firststate.clear();
    int size_value = value.size();
    int sum_of_square = 0;
    int i = 0;
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dis(0, size_value - 1);
    for(int i = 0; i < 20; i++){
            int index = dis(g);
            for(int j = 0; j < firststate.size(); j++){
                if(index == firststate[j]){
                    index = dis(g);
                    j = -1;
                }
            }
            firststate.push_back(index);
            sum_of_square += pow(value[index][1], 2);
        }
    // while(i <= 20){
    /*while(sum_of_square < 200000000){
        firststate.push_back(i + begin);
        sum_of_square += pow(value[i + begin][1], 2);
        i++;
    }*/
    //sum_of_square -= pow(value[i + begin - 1][1], 2);
    //return (200000000 - sum_of_square);
    cout << "初始化完成," << "firststate.size=" << firststate.size() <<endl;
    cout << "初始结果为: " << 200000000 - sum_of_square << endl;
}

void CopyState(vector<int> &curstate, vector<int> newstate){
    curstate.clear();
    for(int i = 0; i < newstate.size(); i++){
        curstate.push_back(newstate[i]);
    }
}

vector<int> SimulatedAnnealing(vector<vector<int>> value, vector<int> firststate, vector<int> &error, int T_0, int IN_loop, int T_f){
    vector<int> curstate;
    vector<int> newstate;
    vector<int> beststate;
    int size_value = value.size();
    CopyState(curstate, firststate);
    int T = T_0;
    int size_change = 10;
    int delta = 0;
    int cursq = 0;
    int newsq = 0;
    for(int j = 0; j < newstate.size(); j++){
            cursq += pow(value[curstate[j]][1], 2);
        }
    cursq = abs(200000000 - cursq);
    int bestsq = cursq;
    cout << "cursq at first: " << cursq << endl;
    while(T >= T_f){
        for(int i = 0; i < IN_loop; i++){
            GetNewStates(curstate, newstate, value, size_change);
            delta = 0;
            newsq = 0;
            for(int j = 0; j < newstate.size(); j++){
                newsq += pow(value[newstate[j]][1], 2);
            }
            newsq = abs(200000000 - newsq);
            delta = newsq - cursq;
            if(delta < 0){
                CopyState(curstate, newstate);
                cursq = newsq;
            }
            else{
                random_device rd;
                mt19937 g(rd());
                uniform_real_distribution<double> dis(0, 1);
                double p = exp(-delta / T);
                if(dis(g) < p){
                    CopyState(curstate, newstate);
                    cursq = newsq;
                }
            }
        
            if(bestsq > cursq){
                CopyState(beststate, curstate);
                bestsq = cursq;
            }
            if(cursq == 0){
                cout << "cursq == 0" << endl;
                return beststate;
            }
            if(i % 10 == 0)
            {
                error.push_back(cursq);
            }
            /*if(i % 500 == 0)
            {
                cout << "cursq: " << cursq << endl;
            }*/
        }
        T = T * 0.9;
        if(size_change > 1){
            size_change--;
        }
        cout << "best now: " << bestsq << endl;
    }
    cout << "best: " << bestsq << endl;
    return beststate;
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

    GetFirstState(firststate, value, 0);
    int T_0 = 200000;
    int IN_loop = 5000;
    int T_f = 1000;
    vector<int> error;
    auto start = high_resolution_clock::now();
    vector<int> result = SimulatedAnnealing(value, firststate, error, T_0, IN_loop, T_f);
    auto end = high_resolution_clock::now();
    cout << "time: " << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
    cout << "result.size: " << result.size() << endl;

    // 将error写入文件error.txt
    FILE *fp1 = fopen("error1.txt", "w");
    for(int i = 0; i < error.size(); i++){
        fprintf(fp1, "%d\n", error[i]);
    }
    fclose(fp1);

    // 将result写入文件result.txt
    FILE *fp2 = fopen("result3.txt", "w");
    for(int i = 0; i < result.size(); i++){
        fprintf(fp2, "%d\n", result[i]);
    }
    fclose(fp2);

    return 0;


}
