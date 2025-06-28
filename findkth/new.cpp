# include <iostream>
# include <vector>
# include <algorithm>
# include <cstdlib>
#include <ctime>

using namespace std;

void merge(vector<int> &v, int l, int mid, int r) {
    vector<int> left(v.begin() + l, v.begin() + mid + 1);
    vector<int> right(v.begin() + mid + 1, v.begin() + r + 1);
    left.push_back(INT_MAX);
    right.push_back(INT_MAX);
    int i = 0, j = 0, k = l;
    while (k <= r){
        if(left[i] <= right[j]){
            v[k] = left[i];
            i++;
        }
        else{
            v[k] = right[j];
            j++;
        }
        k++;
    }
}

void mergesort(vector<int> &v, int l, int r) {
    int mid = (l + r) / 2;
    if (l < r) {
        mergesort(v, l, mid);
        mergesort(v, mid + 1, r);
        merge(v, l, mid, r);
    }
}

void insertsort(vector<int> &v) {
    if(v.size() == 0) return;
    for(int i = 1; i < v.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(v[j] <v[j - 1])
                swap(v[j], v[j - 1]);
            else
                break;
        }
    }
}

void findaftersort(vector<int> &v, int k) {
    mergesort(v, 0, v.size() -  1);
    cout << "The " << k << "th smallest number is: " << v[k - 1] << endl;
}

int findkth(vector<int> &v, int k) {
    if(v.size() < 20) {
        insertsort(v);
        return v[k - 1];
    }
    else {
        vector<int> midNums;
        for(int i = 0; i < v.size(); i += 5) {
            vector<int> temp(v.begin() + i, v.begin() + min(i + 5, (int)v.size()));
            insertsort(temp);
            midNums.push_back(temp[temp.size() / 2]);
        }
        int mid = findkth(midNums, midNums.size() / 2);
        vector<int> left, right;
        for(int i = 0; i < v.size(); i++) {
            if(v[i] < mid) {
                left.push_back(v[i]);
            }
            else if(v[i] > mid) {
                right.push_back(v[i]);
            }
        }
        if(left.size() > k)
            return findkth(left, k);
        else if(k > v.size() - right.size())
            return findkth(right, k - v.size() + right.size());
        else
            return mid;
    }
}

int main() {
    vector<int> v = {3, 2, 1, 5, 4};
    mergesort(v, 0, v.size() - 1);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    vector<int> v1 = {3, 2, 1, 5, 4};
    insertsort(v1);
    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << " ";
    }
    cout << endl;
    vector<int> v2;
    srand(time(0));
    int num = 10;
    for (int i = 0; i < num; i++) {
        v2.push_back(rand() % (10 * num));
    }
    cout << "The original array is: ";
    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << " ";
    }
    cout << endl;
    findaftersort(v2, 3);
    int kth = findkth(v2, 3);
    cout << "The 3rd smallest number is: " << kth << endl;
    return 0;
}