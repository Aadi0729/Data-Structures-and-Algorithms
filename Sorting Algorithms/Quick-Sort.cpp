#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[low];

    int i = low;
    int j = high;

    while(i < j) {
        while(i <= high && nums[i] <= pivot) {
            i++;
        }
        while(j >= low && nums[j] > pivot) {
            j--;
        }
        if(i < j)
            swap(nums[i], nums[j]);
    }
    swap(nums[low], nums[j]);

    return j;
}

void quickSort(vector<int>& nums, int low, int high) {
    if(low >= high) return;

    int partitionIndex = partition(nums, low, high);
    quickSort(nums, low, partitionIndex-1);
    quickSort(nums, partitionIndex+1, high);
}

void printNums(vector<int>& nums) {
    int n = nums.size();

    for(auto val : nums)
        cout << val << " ";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    vector<int> nums(n);
    for(int i=0; i<n; i++) {
        cin >> nums[i];
    }

    quickSort(nums, 0, n-1);

    printNums(nums);

    return 0;
}