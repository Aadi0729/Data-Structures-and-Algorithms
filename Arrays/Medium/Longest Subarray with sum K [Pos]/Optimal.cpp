/*
Time complexity: O(n)
Constant space: O(1)
*/

/*
Sliding Window – Empty Window Reminder

Window is [i … j]
j adds elements, i removes elements
i > j ⇒ empty window
Empty window is allowed
Never use empty window to:
access elements
calculate length
Window is always rebuilt first using j
Sliding window is safe only for non-negative arrays

 - Empty window may occur, but we never perform operations on it.
*/

#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int>& nums, int k) {
    int n = nums.size();

    int i = 0;
    int j = 0;

    int sum = 0;
    int maxLen = 0;

    while(j < n) {
        sum += nums[j];

        while (sum > k) {
            sum -= nums[i];
            i++;
        }
        
        if(sum == k) {
            maxLen = max(maxLen, j-i+1);
        }

        j++;
    }

    return maxLen;
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

    int k;
    cin >> k;

    cout << "The longest subarray is of length " << longestSubarray(nums, k);

    return 0;
}
