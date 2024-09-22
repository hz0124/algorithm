// 本程序中会使用C++设计一段排序算法，生成1000个随机打乱的数保存在一个数组中，对其进行排序，分别用冒泡排序，插入排序，以及快速排序实现，并比较他们运行的时间

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
    clock_t start, end;
    start = clock();
    bubblesort(arr1);
    end = clock();
    std::cout << "冒泡排序用时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    start = clock();
    insertsort(arr2);
    end = clock();
    std::cout << "插入排序用时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    start = clock();
    quicksort(arr3, 0, arr3.size() - 1);
    end = clock();
    std::cout << "快速排序用时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    return 0;
}

// Output:
