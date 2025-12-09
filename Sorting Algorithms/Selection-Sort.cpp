#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int>& nums) {
    int n = nums.size();

    for(int i=0; i<=n-2; i++) {
        int minIndex = i;
        for(int j=i+1; j<n; j++) {
            if(nums[j] < nums[minIndex])
                minIndex = j;
        }
        swap(nums[i], nums[minIndex]);
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

    selectionSort(nums);

    printNums(nums);

    return 0;
}