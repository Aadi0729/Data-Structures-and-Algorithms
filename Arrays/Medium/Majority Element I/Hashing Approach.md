```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, int> mpp;

        for(auto val : nums)
            mpp[val]++;

        for(auto pair : mpp) {
            if(pair.second > n/2)
                return pair.first;
        }

        return -1;
    }
};
```

**Time Complexity:**

- Counting frequencies: O(n)
- Iterating over the map: O(m) where m = number of unique elements
O(n + m)
Overall: ```O(n)``` (since m ≤ n)

**Space Complexity:**

```O(m)``` for the hash map

In the worst case (all elements unique): ```O(n)```
