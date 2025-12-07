#include <bits/stdc++.h>
using namespace std;

vector<int> appearMoreThanOnce(vector<int>& nums) {
    vector<int> temp;

    unordered_map<int, int> mpp;

    for(auto val : nums) {
        mpp[val]++;
    }

    for(auto pair : mpp) {
        if(pair.second > 1)
            temp.push_back(pair.first);
    }

    return temp;
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

    vector<int> res =appearMoreThanOnce(nums);

    cout << "Result: ";
    for(int i=0; i<res.size(); i++) {
        cout << res[i] << " ";
    }

    return 0;
}
