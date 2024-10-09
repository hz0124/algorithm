// 在这个程序中，我们将随机生成一组数，并找寻其中第k小数,k由用户输入，统计程序运行时间
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;



// 编写插入排序算法
void insertSort(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

// 编写归并排序算法
void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> leftPart(nums.begin() + left, nums.begin() + mid + 1);
    vector<int> rightPart(nums.begin() + mid + 1, nums.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] < rightPart[j]) {
            nums[k++] = leftPart[i++];
        } else {
            nums[k++] = rightPart[j++];
        }
    }
    while (i < leftPart.size()) {
        nums[k++] = leftPart[i++];
    }
    while (j < rightPart.size()) {
        nums[k++] = rightPart[j++];
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

// 先归并排序，再找第k大的数
int findaftersort(vector<int>& nums, int k) {
    mergeSort(nums, 0, nums.size() - 1);
    return nums[k-1];
}

int findKthSmallest(vector<int>& nums, int k) {
    if (nums.size() < 20)
    {
        insertSort(nums);
        return nums[k - 1];
    }
    else
    {
        // 将数组分为5个一组，找到每组的中位数
        vector<int> midNums;
        for (int i = 0; i < nums.size(); i += 5) {
            vector<int> temp(nums.begin() + i, nums.begin() + min(i + 5, (int)nums.size()));
            insertSort(temp);
            midNums.push_back(temp[temp.size() / 2]);
        }
        int midNum = findKthSmallest(midNums, midNums.size() / 2);
        vector<int> leftPart, rightPart;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < midNum) {
                leftPart.push_back(nums[i]);
            } else if (nums[i] > midNum) {
                rightPart.push_back(nums[i]);
            }
        }
        if(k <= leftPart.size()) {
            return findKthSmallest(leftPart, k);
        } else if (k > nums.size() - rightPart.size()) {
            return findKthSmallest(rightPart, k - (nums.size() - rightPart.size()));
        } else {
            return midNum;
        }
    }
}

int main() {
    vector<int> nums;
    srand(time(0));
    for (int i = 0; i < 1000000; i++) {
        nums.push_back(rand() % 1000000);
    }
    vector<int> nums1 = nums;
    vector<int> nums2 = nums;
    int k;
    cout << "请输入k值：";
    cin >> k;
    auto start = high_resolution_clock::now();
    cout << "第" << k << "小的数为：" << findaftersort(nums, k) << endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "排序后查找所用时间：" << duration.count() << "ms" << endl;
    start = high_resolution_clock::now();
    cout << "第" << k << "小的数为：" << findKthSmallest(nums1, k) << endl;
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "分治查找所用时间：" << duration.count() << "ms" << endl;
    start = high_resolution_clock::now(); // 调用stl库函数
    nth_element(nums2.begin(), nums2.begin() + k - 1, nums2.end());
    cout << "第" << k << "小的数为：" << nums2[k - 1] << endl;
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "STL库函数所用时间：" << duration.count() << "ms" << endl;
    return 0;
}
