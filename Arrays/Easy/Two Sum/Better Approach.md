```
#include <bits/stdc++.h>
using namespace std;

pair<int, int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();

    unordered_map<int, int> mpp;

    for(int i=0; i<n; i++) {
        int val = target - nums[i];

        if(mpp.find(val) != mpp.end())
            return {i, mpp[val]};

        mpp[nums[i]] = i;
    }

    return {0,0};
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

    pair<int, int> res = twoSum(nums, target);

    if(res.first == 0 && res.second == 0)
        cout << "Doesn't exist...";
    else
        cout << "The indices of the two numbers which add up to " << target << " are [" << res.first << ", " << res.second << "]";

    return 0;
}
```

**Time Complexity (TC)**: ```O(n)```

The loop runs ```n``` times

Each operation on ```unordered_map``` (```find```, ```insert```) is:

- ***O(1)*** on average
- So total time = ```n × O(1)``` = ```O(n)```

**Space Complexity (SC): O(n)**

In the worst case, we store all ```n``` elements in the hash map

No other auxiliary structures grow with input size

So auxiliary space = ***O(n)***
