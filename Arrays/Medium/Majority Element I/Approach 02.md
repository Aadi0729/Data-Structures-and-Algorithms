## Majority Element (Boyer–Moore Voting Algorithm)

**Problem**

Find the element that appears more than ```⌊n/2⌋``` times in an array.
(The problem guarantees that such an element exists.)

**Key Idea:**

Different elements cancel each other out in pairs.
A majority element (> n/2 occurrences) *cannot be fully cancelled*, so it survives.

**Algorithm Intuition**

Maintain a ```candidate``` and a ```count```

If ```count == 0```, choose the current element as the new candidate

If current element == candidate → increment ```count```

Else → decrement ```count```

This simulates *pair cancellation* between different elements.

**Why It Works**

The majority element appears more times than all other elements combined

Even after cancelling with all non-majority elements, at least one occurrence remains

Hence, the final surviving ```candidate``` is the majority element

**Complexity**

**TC =** ```O(n)```

**SC =** ```O(1)```

```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;

        for(auto val : nums) {
            if(count == 0)
                candidate = val;
            
            count += (candidate == val) ? 1 : -1;
        }
        return candidate;
    }
};
```
