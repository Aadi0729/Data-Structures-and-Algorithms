# Split Array Largest Sum — Interview Style 🔢
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Hard
> **Leetcode:** #410

---

## Problem Statement

Given integer array `nums` and integer `k`:
- Split array into `k` non-empty subarrays
- **Minimize** the largest subarray sum
- Return that minimized value

```
nums=[7,2,5,10,8], k=2 → Output: 18
nums=[1,2,3,4,5],  k=2 → Output: 9
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of nums[i] and k?
2. Can subarrays be rearranged or must be contiguous?
3. Is solution always guaranteed to exist?
4. What is length range of nums array?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ nums[i] ≤ 10^9
→ 1 ≤ k ≤ nums.size()
→ Subarrays must be CONTIGUOUS — no rearranging!
→ Solution ALWAYS exists — no impossible case!
→ 1 ≤ nums.size() ≤ 10^4
→ Yes, start from brute force
```

> 🔥 **Key difference from Book Allocation:**
> No impossible case here!
> k ≤ nums.size() always guaranteed → solution always exists!

---

## Pattern Recognition — The THREE BROTHERS 🔥

> This problem is **identical** to Ship Packages AND Book Allocation!

```
Ship Packages:    Book Allocation:    Split Array:
──────────────────────────────────────────────────
weights[]    →    books[]        →    nums[]
days         →    k students     →    k subarrays
capacity/day →    pages/student  →    sum/subarray
in ORDER     →    CONTIGUOUS     →    CONTIGUOUS
min capacity →    min max pages  →    min max sum
```

> All three ask ONE question:
> *"Find minimum limit such that array can be
>  divided into k parts without exceeding that limit."*

```
Only differences:
Book Allocation: k > n → impossible → -1
Split Array    : k ≤ n always → no impossible case!
Ship Packages  : no impossible case!
```

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(nums)` | Below this, largest element can never fit |
| `high` | `sum(nums)` | Everything in 1 subarray — no point going higher |
| `ans` | `high` | Gets minimized during search |

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every sum limit from max(nums) to sum(nums).
For each limit → count subarrays needed.
First valid limit → minimum! Stop immediately.
```

### Code:
```cpp
class Solution {
public:
    bool canSplitArray(vector<int>& nums, int k, int sum) {
        int subarrays = 0;
        int totSum    = 0;

        for(int i = 0; i < nums.size(); i++) {
            totSum += nums[i];
            if(totSum > sum) {
                subarrays++;              // new subarray needed
                totSum = nums[i];         // current element → new subarray
            }
        }
        subarrays++;                      // count last subarray!
        return subarrays <= k;
    }

    int splitArray(vector<int>& nums, int k) {
        int maxSum   = *max_element(nums.begin(), nums.end());
        int totalSum = 0;
        for(auto val : nums) totalSum += val;

        int ans = totalSum;

        for(int i = maxSum; i <= totalSum; i++) {
            if(canSplitArray(nums, k, i)) {
                ans = i;    // first valid = minimum!
                break;
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O((sum-max) × n)
SC : O(1)
```

### Bottleneck:
```
Linear scan over all sum limits → too slow!
Can we eliminate half the search space
with one comparison? → YES! Monotonic pattern!
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
sum limit:  max  ....  X  ....  sum
works?:     ❌   ....  ✅  ....  ✅

Pattern: FALSE → TRUE (monotonic!)
→ Larger limit → easier to fit elements ✅
→ Smaller limit → harder to fit elements ❌
First TRUE = minimum valid limit = answer!
```

### Monotonic Pattern:
```
❌ ❌ ❌ ✅ ✅ ✅ ✅
         ↑
    BOUNDARY
  (first TRUE = answer)

Pattern   : FALSE → TRUE
Goal      : Find FIRST TRUE
Type      : MINIMIZE
Direction : when TRUE  → ans=mid, high=mid-1
            when FALSE → low=mid+1
```

### Code:
```cpp
class Solution {
public:
    bool canSplitArray(vector<int>& nums, int k, int sum) {
        int subarrays = 0;
        int totSum    = 0;

        for(int i = 0; i < nums.size(); i++) {
            totSum += nums[i];
            if(totSum > sum) {
                subarrays++;
                totSum = nums[i];
            }
        }
        subarrays++;
        return subarrays <= k;
    }

    int splitArray(vector<int>& nums, int k) {
        int low  = *max_element(nums.begin(), nums.end());
        int high = 0;
        for(auto val : nums) high += val;

        int ans = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canSplitArray(nums, k, mid)) {
                ans  = mid;
                high = mid - 1;    // minimize → go left
            } else {
                low  = mid + 1;    // too small → go right
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log s)
     → log s iterations × O(n) isPossible
     where s = sum - max = search space size

SC : O(1) — no extra space
```

### Dry Run (nums=[7,2,5,10,8], k=2):
```
low=10, high=32, ans=32

Iter 1: mid=21
        7→9→14→24>21 → sub=1, totSum=10
        10→18<=21 ✅
        sub++=2 → 2<=2 ✅ → ans=21, high=20

Iter 2: mid=15
        7→9→14→24>15 → sub=1, totSum=10
        10→18>15 → sub=2, totSum=8
        sub++=3 → 3>2 ❌ → low=16

Iter 3: mid=18
        7→9→14→24>18 → sub=1, totSum=10
        10→18<=18 ✅
        sub++=2 → 2<=2 ✅ → ans=18, high=17

low=18 > high=17 → STOP
return 18 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| Brute Force | O((sum-max) × n) | O(1) | Astronomical ❌ |
| **Optimal** | **O(n log s)** | **O(1)** | **~10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Range of nums[i] and k?
 Must subarrays be contiguous?
 Any impossible case?
 [get answers]"

STEP 2 — PATTERN RECOGNITION (MOST IMPORTANT!):
"I immediately recognize this as part of
 a family of problems —
 Ship Packages, Book Allocation, Split Array.

 All three ask:
 'Find minimum limit such that array
  can be divided into k parts
  without exceeding that limit.'

 Same search space: [max(nums), sum(nums)]
 Same isPossible() logic
 Same binary search direction

 Only difference from Book Allocation:
 No impossible case — k ≤ n always guaranteed!"

STEP 3 — BRUTE FORCE:
"Try every sum limit from max to sum.
 Count subarrays needed for each.
 First valid → minimum! Break.
 TC: O((sum-max) × n). Too slow!"

STEP 4 — OPTIMAL:
"FALSE→TRUE monotonic pattern.
 Binary Search applicable!
 low=max(nums), high=sum(nums)
 canSplitArray() stays same!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log s)"

STEP 5 — EDGE CASES:
"No impossible case → k ≤ n always ✅
 subarrays++ after loop → count last ✅
 Reset to nums[i] not 0 → element kept ✅"
```

---

## The Three Brothers — Final Comparison 🔥

| | Ship Packages | Book Allocation | Split Array |
|---|---|---|---|
| Array | `weights` | `books` | `nums` |
| Divider | `days` | `k students` | `k subarrays` |
| low | `max(weights)` | `max(books)` | `max(nums)` |
| high | `sum(weights)` | `sum(books)` | `sum(nums)` |
| Impossible | None | `k > n → -1` | None |
| Pattern | Minimize | Minimize | Minimize |

---

## Common Mistakes in Interviews ⚠️

```
1. Not recognizing connection to Ship/Book problems
   → Always mention pattern recognition!

2. Forgetting subarrays++ after loop → last subarray missed!

3. Resetting totSum=0 → current element lost! → use nums[i]

4. Wrong direction → low=mid+1 when TRUE → that's maximize!
   Correct: high=mid-1 when TRUE for minimize

5. Assuming impossible case exists
   → k ≤ nums.size() always → always solvable!
```

---

## Key Takeaways 🔥

- *"Split Array = Book Allocation = Ship Packages — three brothers!"*
- *"All three: find minimum limit to divide array into k parts."*
- *"No impossible case — k ≤ nums.size() always guaranteed."*
- *"canSplitArray() identical in brute force and optimal."*
- *"Pattern recognition is the highest interview skill — mention it!"*
- *"A Leetcode Hard solved in 5 minutes — because you saw it twice before!"*
