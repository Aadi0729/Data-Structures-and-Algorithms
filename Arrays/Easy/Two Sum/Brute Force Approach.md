**1. Eliminating duplicate pair checks**

You correctly identified:

- ```(i, j)``` and ```(j, i)``` represent the same unordered pair
- Checking both is redundant

By starting ```j``` from ```i + 1```, you ensure:

- Every unordered pair is checked exactly once
- No symmetry duplication

**2. Eliminating the i == j condition**

Because:
```
j = i + 1;
```

- ```j``` can never equal ```i```
- The explicit if ```(i == j)``` check becomes unnecessary

```
#include <bits/stdc++.h>
using namespace std;

pair<int, int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {

            if(nums[i] + nums[j] == target)
                return {i,j};
        }
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

**Complexity**

Even though the number of comparisons is almost halved, the complexity remains:

*Time*: ```O(n²)```

*Space*: ```O(1)```

***Why?***

Because Big-O ignores constant factors.

This is an ***optimized brute-force***, not an optimal algorithm.
