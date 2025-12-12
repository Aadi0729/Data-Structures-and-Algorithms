#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& nums, int low, int mid, int high) {
    int left = low;
    int right = mid+1;

    vector<int> temp;

    while(left <= mid && right <= high) {
        if(nums[left] < nums[right]) {
            temp.push_back(nums[left]);
            left++;
        }
        else {
            temp.push_back(nums[right]);
            right++;
        }
    }
    while(left <= mid) {
        temp.push_back(nums[left]);
        left++;
    }
    while(right <= high) {
        temp.push_back(nums[right]);
        right++;
    }

    for(int i=low; i<=high; i++) {
        nums[i] = temp[i-low];
    }
}

void mergeSort(vector<int>& nums, int low, int high) {
    if(low == high) return;

    int mid = (low+high)/2;

    mergeSort(nums, low, mid);
    mergeSort(nums, mid+1, high);
    merge(nums, low, mid, high);
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

    mergeSort(nums, 0, n-1);

    printNums(nums);

    return 0;
}