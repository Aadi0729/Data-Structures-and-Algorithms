#include <bits/stdc++.h>
using namespace std;

void reverseArray(vector<int>& nums, int start, int end) {
    if(start >= end)
        return;

    swap(nums[start], nums[end]);
    reverseArray(nums, start+1, end-1);
}

void printArray(vector<int> nums) {
    for(int i=0; i<nums.size(); i++) {
        cout << nums[i] << " ";
    }
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

    reverseArray(nums, 0, n-1);

    printArray(nums);

    return 0;
}
