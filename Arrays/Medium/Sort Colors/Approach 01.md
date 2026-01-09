**Time Complexity:** ```O(n)```

**Space Complexity:** ```O(1)```

One traversal, fully in-place 

Takes 2 pass
- One pass for counting
- One pass for overwriting

```
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count0 = 0, count1 = 0, count2 = 0;

        for (int x : nums) {
            if (x == 0) count0++;
            else if (x == 1) count1++;
            else count2++;
        }

        int i = 0;
        while (count0--) nums[i++] = 0;
        while (count1--) nums[i++] = 1;
        while (count2--) nums[i++] = 2;
    }
};
```
