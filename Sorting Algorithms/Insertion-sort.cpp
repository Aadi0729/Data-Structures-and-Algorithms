#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& nums) {
    int n = nums.size();

    for(int i=1; i<n; i++) {
        int key = nums[i];
        int j = i-1;
        while(j >= 0 && nums[j] > key) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = key;
    }
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

    insertionSort(nums);

    printNums(nums);

    return 0;
}