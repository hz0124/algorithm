// 本程序中会使用C++设计一段排序算法，生成1000个随机打乱的数保存在一个数组中，对其进行排序，分别用冒泡排序，插入排序，以及快速排序实现，并比较他们运行的时间

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 冒泡排序
void bubblesort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertsort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 快速排序
void quicksort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left;
    int j = right;
    int key = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= key) {
            j--;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <= key) {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = key;
    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}

int main() {
    std::vector<int> arr;
    srand(time(0));
    for (int i = 0; i < 1000; i++) {
        arr.push_back(rand() % 1000);
    }
    std::vector<int> arr1 = arr;
    std::vector<int> arr2 = arr;
    std::vector<int> arr3 = arr;
    // 显示数组的前10个元素
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    auto start = system_clock::now();
    bubblesort(arr1);
    auto end = system_clock::now();
    std::cout << "冒泡排序用时：" << duration<double>(end - start).count() << "s" << std::endl;
    start = system_clock::now();
    insertsort(arr2);
    end = system_clock::now();
    std::cout << "插入排序用时：" << duration<double>(end - start).count() << "s" << std::endl;
    start = system_clock::now();
    quicksort(arr3, 0, arr3.size() - 1);
    end = system_clock::now();
    std::cout << "快速排序用时：" << duration<double>(end - start).count() << "s" << std::endl;
    return 0;
}

// Output:
