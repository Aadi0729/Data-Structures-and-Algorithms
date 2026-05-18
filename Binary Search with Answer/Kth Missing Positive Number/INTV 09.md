# Kth Missing Positive Number — Interview Style 🔢
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Find Last TRUE
> **Difficulty:** Easy-Medium
> **Leetcode:** #1539

---

## Problem Statement

Given a **sorted** array of distinct positive integers and integer `k`:
- Return the **kth missing positive number**

```
arr=[2,3,4,7,11], k=5  → Output: 9
arr=[1,2,3,4],    k=2  → Output: 6
arr=[1,3],        k=1  → Output: 2
```

---

## Understanding The Problem 🧠

```
arr = [2, 3, 4, 7, 11]

Check each positive number:
1  → missing ✅ (1st missing)
2  → present ❌
3  → present ❌
4  → present ❌
5  → missing ✅ (2nd missing)
6  → missing ✅ (3rd missing)
7  → present ❌
8  → missing ✅ (4th missing)
9  → missing ✅ (5th missing) ← ANSWER for k=5!
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of arr[i] and k?
2. Is array always sorted?
3. Are all elements distinct?
4. Can k be larger than arr.size()?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ arr[i] ≤ 1000
→ 1 ≤ k ≤ 1000
→ Yes — always sorted
→ Yes — all distinct
→ Yes — k can exceed arr.size()
→ Yes, start from brute force
```

---

## KEY DIFFERENCE From Other Problems 🎯

```
Previous problems:
→ Search space = range of VALUES [low, high]
→ low/high derived from constraints

This problem:
→ Search space = INDICES of array [0, n-1]
→ Answer derived from formula after binary search!
```

---

## The Missing Count Formula 🔥

> **How many numbers are missing before arr[i]?**

```
If NO numbers were missing:
arr[0] should be 1
arr[1] should be 2
arr[i] should be i+1  ← "perfect value"

Actual value = arr[i]
Perfect value = i+1

Missing count before arr[i] = arr[i] - (i+1)
```

**Verification:**
```
arr = [2, 3, 4, 7, 11]

index 0: arr[0]-(0+1) = 2-1  = 1 missing  {1}
index 1: arr[1]-(1+1) = 3-2  = 1 missing  {1}
index 2: arr[2]-(2+1) = 4-3  = 1 missing  {1}
index 3: arr[3]-(3+1) = 7-4  = 3 missing  {1,5,6}
index 4: arr[4]-(4+1) = 11-5 = 6 missing  {1,5,6,8,9,10}
```

---

## APPROACH 1 — Brute Force

### Intuition:
```
Walk through positive integers 1, 2, 3...
Track position in arr using pointer.
Count missing numbers.
When count reaches k → return current number!
```

### Code:
```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int count = 0;   // missing numbers found
        int num   = 0;   // current number being checked
        int i     = 0;   // pointer into arr

        while(count < k) {
            num++;

            if(i < arr.size() && arr[i] == num)
                i++;        // num present → skip, move pointer
            else
                count++;    // num missing → count it!
        }
        return num;
    }
};
```

### Complexity:
```
TC : O(n + k)
     → n for traversing array elements
     → k for counting missing numbers

SC : O(1) — no extra space
```

### Bottleneck:
```
For very large k → num goes up to k + arr.size() 😬
For k = 10^9 → too slow!
Can we use the missing count formula to do better?
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
Missing count arr[i]-(i+1) is MONOTONICALLY INCREASING!

index:          0    1    2    3    4
missing count:  1    1    1    3    6
missing < k=5?: ✅   ✅   ✅   ✅   ❌

Pattern: TRUE → FALSE
We want: LAST TRUE (last index where missing < k)
Type: Find last TRUE → go right when TRUE
```

### Why Last TRUE? 🎯
```
Last TRUE index (high) tells us:
→ kth missing lies AFTER arr[high]
→ We can calculate exact answer using formula!
```

### The Answer Formula 🔥
```
After binary search:
high = last index where missing count < k

Missing found so far   = arr[high] - (high+1)
Still need             = k - (arr[high] - (high+1))
Answer                 = arr[high] + (k - missingCount)

Simplify:
= arr[high] + k - arr[high] + high + 1
= k + high + 1          ← arr[high] cancels out!
```

**Verification:**
```
arr=[2,3,4,7,11], k=5
high=3 (last index where missing < 5)

answer = k + high + 1
       = 5 + 3    + 1
       = 9 ✅
```

### Edge Case — k smaller than all missing before arr[0]:
```
arr=[3,4,5], k=1
high=-1 after binary search (all indices have missing >= k)

answer = k + high + 1
       = 1 + (-1) + 1
       = 1 ✅ (1 is the 1st missing!)
```

### Code:
```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int low  = 0;
        int high = arr.size() - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(arr[mid] - (mid + 1) < k) {
                low = mid + 1;   // missing < k → go right (last TRUE)
            } else {
                high = mid - 1;  // missing >= k → go left
            }
        }
        return k + high + 1;     // formula for exact answer!
    }
};
```

### Complexity:
```
TC : O(log n) — binary search on indices
SC : O(1)     — no extra space
```

### Dry Run (arr=[2,3,4,7,11], k=5):
```
low=0, high=4

Iter 1: mid=2 → arr[2]-(2+1)=1 < 5 → low=3
Iter 2: mid=3 → arr[3]-(3+1)=3 < 5 → low=4
Iter 3: mid=4 → arr[4]-(4+1)=6 >= 5 → high=3

low=4 > high=3 → STOP
answer = k + high + 1 = 5 + 3 + 1 = 9 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | For k=10^9 |
|---|---|---|---|
| Brute Force | O(n+k) | O(1) | Too slow ❌ |
| **Optimal** | **O(log n)** | **O(1)** | ~30 iterations ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Is array always sorted?
 All elements distinct?
 Can k exceed array size?
 [get answers]"

STEP 2 — BRUTE FORCE:
"Walk through 1,2,3... counting missing numbers.
 When count=k → return current number.
 TC: O(n+k), SC: O(1)
 Bottleneck: large k → too slow!"

STEP 3 — KEY INSIGHT:
"Missing count before arr[i] = arr[i] - (i+1)
 This is monotonically increasing!
 TRUE→FALSE pattern → Binary Search applicable!"

STEP 4 — OPTIMAL:
"Search over indices [0, n-1].
 Find last index where missing count < k.
 Answer = k + high + 1 (derived formula)
 TC: O(log n), SC: O(1)"

STEP 5 — EDGE CASES:
"high=-1 → k missing before arr[0]
 answer = k + (-1) + 1 = k ✅
 k larger than all missing → handled by formula ✅"
```

---

## This Problem vs Previous Problems 🎯

```
Previous Problems:              Kth Missing:
────────────────────────────────────────────
Search space = [low, high]  →  Search space = indices
low/high = constraint based →  low=0, high=n-1
Answer = mid at boundary    →  Answer = formula k+high+1
isPossible checks value     →  checks missing count formula
```

> 🔥 *"Binary Search on Answer doesn't always search over values —
>      sometimes it searches over INDICES with a derived formula!"*

---

## Common Mistakes in Interviews ⚠️

```
1. Forgetting arr[i]-(i+1) formula → missing count wrong
2. Using wrong formula for answer → not simplifying correctly
3. Missing edge case high=-1 → verify formula handles it!
4. Searching over values instead of indices
5. Wrong direction → high=mid-1 when TRUE
   Correct: low=mid+1 when TRUE (last TRUE pattern)
```

---

## Key Takeaways 🔥

- *"Missing count before arr[i] = arr[i] - (i+1)"*
- *"Missing count is monotonically increasing → BS applicable!"*
- *"Search over indices [0,n-1] not values!"*
- *"Answer = k + high + 1 — arr[high] cancels out beautifully!"*
- *"Edge case high=-1 handled automatically by formula."*
- *"This proves BS on Answer works beyond just splitting problems!"*
