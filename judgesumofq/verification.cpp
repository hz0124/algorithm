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
    vector<int> result;
    FILE *fp1 = fopen("result.txt", "r");
    while(fscanf(fp, "%d", &a) != EOF){
        result.push_back(a);
    }
    fclose(fp1);
    int sumofsquare = 0;
    for(int i = 0; i < result.size(); i++){
        sumofsquare += pow(value[result[i]][1], 2);
    }
    cout << "sumofsquare: " << sumofsquare << endl;
    return 0;
}