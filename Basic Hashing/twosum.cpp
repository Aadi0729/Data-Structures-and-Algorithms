#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mpp;
    int n = nums.size();

    for(int i=0; i<n; i++) {
        int need = target - nums[i];
        if(mpp.find(need) != mpp.end())
            return {mpp[need], i};
        else
            mpp[nums[i]] = i;
    }

    return {0};
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

    int target;
    cin >> target;

    vector<int> res = twoSum(nums, target);

    cout << "[ ";
    for(int i=0; i<res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << "]";
    cout << " are the values which sums upto " << target;

    return 0;
}
