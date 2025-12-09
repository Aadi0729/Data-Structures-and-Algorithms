#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& nums) {
    int n = nums.size();

    for(int i=n-1; i>=1; i--) {
        for(int j=0; j<i; j++) {
            if(nums[j] > nums[j+1])
                swap(nums[j], nums[j+1]);
        }
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

    bubbleSort(nums);

    printNums(nums);

    return 0;
}