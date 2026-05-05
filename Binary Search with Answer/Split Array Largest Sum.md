# Split Array Largest Sum 🔢

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Hard
> **Leetcode:** #410

---

## Problem Statement

Given an integer array `nums` and integer `k`:
- Split array into `k` non-empty subarrays
- **Minimize** the maximum subarray sum
- Return that minimum value

**Example:**
```
nums = [7, 2, 5, 10, 8], k = 2
Output: 18  (split: [7,2,5] | [10,8] → max(14,18) = 18)
```

---

## The Soul of This Problem 🔥

> *"What is the minimum limit such that array can be divided into k parts without any part exceeding that limit?"*

This is IDENTICAL to:
- **Ship Packages** → minimum capacity per day
- **Book Allocation** → minimum pages per student
- **Split Array** → minimum sum per subarray

> 🔥 **All three are the same problem with different stories!**

---

## Why Binary Search Works Here?

As limit increases → splitting becomes easier:

```
limit:    5      9      15      18      25
works?:   ❌     ❌     ❌      ✅      ✅
```

**Monotonic pattern: FALSE → TRUE**
- Once a limit works → all higher limits also work ✅
- Once a limit fails → all lower limits also fail ❌

> 🔥 This monotonic behavior = Binary Search applicable!

---

## Search Space — Deep Intuition

| Bound | Value | Deep Reason |
|---|---|---|
| `low` | `max(nums)` | Minimum limit where EVERY element fits alone in its own subarray |
| `high` | `sum(nums)` | One subarray holds everything — worst case, always works |

```
nums = [7, 2, 5, 10, 8]
low  = max = 10   → below this, element 10 can never fit anywhere!
high = sum = 32   → everything in 1 subarray, always works
```

**Why `low = max(nums)`?**
> If limit < max(nums) → largest element can NEVER fit in any subarray → problem breaks!

**Why `high = sum(nums)`?**
> At limit = sum → 1 subarray holds everything → always works → no point going higher!

---

## isPossible() — The Bucket Intuition 🔥

> *"Can I fit array elements into k buckets without any bucket exceeding limit mid?"*

```
Greedy strategy:
→ Keep filling current bucket
→ When bucket overflows → open new bucket, put current element there
→ Count total buckets needed
→ Return buckets needed <= k
```

```
Walk array left to right:
sum += nums[i]
if sum > limit:
    → subarrays++ (new bucket!)
    → sum = nums[i]  ← current element goes to new bucket
after loop:
    → subarrays++    ← count last bucket!
return subarrays <= k
```

---

## Dry Run

```
nums = [7, 2, 5, 10, 8], limit = 18, k = 2
sum = 0, subarrays = 0
```

| i | nums[i] | sum | > 18? | subarrays |
|---|---|---|---|---|
| 0 | 7 | 7 | ❌ | 0 |
| 1 | 2 | 9 | ❌ | 0 |
| 2 | 5 | 14 | ❌ | 0 |
| 3 | 10 | 24 | ✅ new bucket! reset=10 | 1 |
| 4 | 8 | 18 | ❌ | 1 |

After loop → `subarrays++ = 2`
`2 <= 2` → ✅ **limit 18 works!**

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& nums, int k, int largest_sum) {
        int subarrays = 0;
        int sum       = 0;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (sum > largest_sum) {
                subarrays++;              // open new bucket
                sum = nums[i];            // current element goes to new bucket
            }
        }
        subarrays++;                      // count last bucket!

        return subarrays <= k;            // buckets needed <= buckets available?
    }

    int splitArray(vector<int>& nums, int k) {
        int low  = *max_element(nums.begin(), nums.end());
        int high = 0;
        for (auto val : nums) high += val;

        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(nums, k, mid)) {
                ans  = mid;
                high = mid - 1;           // minimize → go left
            } else {
                low  = mid + 1;           // too small → go right
            }
        }
        return ans;
    }
};
```

---

## Complexity Analysis

| | Value |
|---|---|
| Time | O(n log s) — log s iterations × O(n) isPossible |
| Space | O(1) |

Where `n` = size of nums, `s` = sum(nums)

---

## The Three Brothers 🔥

> Ship Packages, Book Allocation, Split Array — same soul, different story!

| | Ship Packages | Book Allocation | Split Array |
|---|---|---|---|
| Array | `weights` | `books` | `nums` |
| Constraint | `days` | `k students` | `k subarrays` |
| low | `max(weights)` | `max(books)` | `max(nums)` |
| high | `sum(weights)` | `sum(books)` | `sum(nums)` |
| Bucket | day | student | subarray |
| isPossible | `days <= d` | `students <= k` | `subarrays <= k` |
| Pattern | Minimize | Minimize | Minimize |

---

## Minimize vs Maximize — Once and For All 🎯

| | When TRUE | When FALSE | Hunting For |
|---|---|---|---|
| **Minimize** | `ans=mid, high=mid-1` | `low=mid+1` | First TRUE |
| **Maximize** | `ans=mid, low=mid+1` | `high=mid-1` | Last TRUE |

> 🔥 *"Minimize = go left when TRUE. Maximize = go right when TRUE."*

---

## Common Mistakes ⚠️

```cpp
// ❌ Forgetting to count last subarray
return subarrays <= k;   // last bucket never counted!

// ✅ Always increment after loop
subarrays++;
return subarrays <= k;

// ❌ Resetting sum to 0 on overflow
sum = 0;        // current element lost!

// ✅ Reset to current element
sum = nums[i];  // current element goes to new bucket

// ❌ Wrong direction for minimize
ans = mid; low = mid + 1;   // this is MAXIMIZE!

// ✅ Correct direction for minimize
ans = mid; high = mid - 1;  // go left to find smaller valid answer
```

---

## Key Takeaways 🔥

- *"Split Array = Book Allocation = Ship Packages — same problem, different story."*
- *"low = max(nums) because below this, largest element can never fit anywhere."*
- *"high = sum(nums) because at this limit, everything fits in 1 subarray."*
- *"isPossible() counts buckets needed — return true if buckets needed <= k."*
- *"Always count last bucket after loop — easiest bug to miss."*
- *"Minimize = go left when TRUE. Maximize = go right when TRUE."*
