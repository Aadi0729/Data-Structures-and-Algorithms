#include <bits/stdc++.h>
using namespace std;

bool checkDuplicate(vector<int>& nums, int n) {
    unordered_set<int> set;

    for(auto val : nums) {
        if(set.find(val) != set.end())
            return true;
        else
            set.insert(val);
    } 

    return false;
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

    bool isPresent = checkDuplicate(nums, n);

    if(isPresent)
        cout << "Duplicate present.";
    else
        cout << "Duplicate not present.";

    return 0;
}
