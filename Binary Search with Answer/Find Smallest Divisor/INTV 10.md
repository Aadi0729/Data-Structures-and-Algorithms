# Find Smallest Divisor — Interview Style 🔢
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #1283

---

## Problem Statement

Given array `nums[]` and integer `threshold`:
- Find **smallest divisor** such that sum of division results ≤ threshold
- Each division result rounded UP (ceiling division)

```
nums=[1,2,5,9], threshold=6  → Output: 5
nums=[2,3,5,7], threshold=11 → Output: 1
```

---

## Understanding The Problem 🧠

```
nums=[1,2,5,9], threshold=6

divisor=5:
ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5)
= 1+1+1+2 = 5 ≤ 6 ✅ → valid!

divisor=4:
ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4)
= 1+1+2+3 = 7 > 6 ❌ → invalid!

Answer = 5 (minimum valid divisor)
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of nums[i] and threshold?
2. Is solution always guaranteed to exist?
3. Can divisor be 0 or negative?
4. What is length range of nums array?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ nums[i] ≤ 10^6
→ 1 ≤ threshold ≤ 10^6
→ Solution always exists (divisor=max gives minimum sum)
→ Divisor must be positive integer ≥ 1
→ 1 ≤ nums.size() ≤ 5×10^4
→ Yes, start from brute force
```

---

## Pattern Recognition 🔥

> This problem is **identical** to Koko Eating Bananas!

```
Koko Eating Bananas:     Smallest Divisor:
─────────────────────────────────────────────
piles[]           →      nums[]
eating speed k    →      divisor d
ceil(pile/speed)  →      ceil(num/divisor)
totalHours <= h   →      result <= threshold
minimize speed    →      minimize divisor
low = 1           →      low = 1
high = max(piles) →      high = max(nums)
```

> 🔥 *"Same soul — different story!"*

---

## Search Space 🎯

```
low  = 1
     → divisor 0 undefined, negative meaningless
     → minimum valid divisor = 1

high = max(nums)
     → at divisor=max(nums), every element rounds to 1
     → result = nums.size() (minimum possible!)
     → going higher gives SAME result → pointless!
```

**Why high = max(nums)?**
```
divisor = max(nums) = 9:
ceil(1/9)=1, ceil(2/9)=1, ceil(5/9)=1, ceil(9/9)=1
result = 4 ← minimum possible!

divisor = 100, 1000...:
result = 4 ← same! Never improves!

So no point going beyond max(nums)!
```

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every divisor from 1 to max(nums).
For each → calculate sum of ceiling divisions.
First valid divisor → minimum! Return immediately.
```

### Code:
```cpp
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int maxVal = *max_element(nums.begin(), nums.end());

        for(int divisor = 1; divisor <= maxVal; divisor++) {
            long long result = 0;          // reset for each divisor!

            for(int i = 0; i < nums.size(); i++) {
                result += (nums[i] + divisor - 1) / divisor;
            }

            if(result <= threshold)
                return divisor;            // first valid = minimum!
        }
        return maxVal;                     // always valid fallback
    }
};
```

### Complexity:
```
TC : O(max(nums) × n)
     → outer loop runs max(nums) times
     → each iteration → O(n) calculation

SC : O(1) — no extra space
```

### Bottleneck:
```
For max(nums)=10^6, n=5×10^4:
→ 10^6 × 5×10^4 = 5×10^10 operations 😬
Way too slow!
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
As divisor increases → sum of results decreases:

divisor:  1    2    3    4    5    ...  max
works?:   ❌   ❌   ❌   ❌   ✅   ...  ✅

Pattern: FALSE → TRUE (monotonic!)
→ Larger divisor → smaller sum → easier ✅
→ Smaller divisor → larger sum → harder ❌
First TRUE = minimum valid divisor = answer!
```

### Monotonic Pattern:
```
❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
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
    bool isPossible(vector<int>& nums, int threshold, int divisor) {
        long long result = 0;          // long long → overflow safe!
        for(int i = 0; i < nums.size(); i++) {
            result += (nums[i] + divisor - 1) / divisor;
        }
        return result <= threshold;
    }

    int smallestDivisor(vector<int>& nums, int threshold) {
        int low  = 1;
        int high = *max_element(nums.begin(), nums.end());
        int ans  = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(isPossible(nums, threshold, mid)) {
                ans  = mid;
                high = mid - 1;    // minimize → go left
            } else {
                low  = mid + 1;    // too large sum → go right
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log m)
     → log m iterations of binary search
     → each iteration → isPossible() → O(n)
     where n = nums.size(), m = max(nums)

SC : O(1) — no extra space
```

### Dry Run (nums=[1,2,5,9], threshold=6):
```
low=1, high=9, ans=9

Iter 1: mid=5
        ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5)
        = 1+1+1+2 = 5 ≤ 6 ✅ → ans=5, high=4

Iter 2: mid=2
        ceil(1/2)+ceil(2/2)+ceil(5/2)+ceil(9/2)
        = 1+1+3+5 = 10 > 6 ❌ → low=3

Iter 3: mid=3
        ceil(1/3)+ceil(2/3)+ceil(5/3)+ceil(9/3)
        = 1+1+2+3 = 7 > 6 ❌ → low=4

Iter 4: mid=4
        ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4)
        = 1+1+2+3 = 7 > 6 ❌ → low=5

low=5 > high=4 → STOP
return 5 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| Brute Force | O(max(nums) × n) | O(1) | ~5×10^10 ❌ |
| **Optimal** | **O(n log m)** | **O(1)** | **~10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Range of nums[i] and threshold?
 Solution always guaranteed?
 [get answers]"

STEP 2 — PATTERN RECOGNITION:
"I recognize this as identical to
 Koko Eating Bananas!
 Speed → Divisor
 Hours → Division results
 h → threshold
 Same search space, same isPossible()!"

STEP 3 — BRUTE FORCE:
"Try every divisor from 1 to max(nums).
 Sum ceiling divisions for each.
 First valid → return immediately.
 TC: O(max(nums) × n). Too slow!"

STEP 4 — OPTIMAL:
"FALSE→TRUE monotonic pattern.
 Binary Search applicable!
 low=1, high=max(nums)
 Why high=max(nums)?
 → Beyond this, every element rounds to 1
 → Result never improves!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log m)"

STEP 5 — EDGE CASES:
"long long result → overflow safe ✅
 divisor=1 → max possible sum ✅
 divisor=max → min possible sum ✅"
```

---

## Ceiling Division Reminder 🎯

```cpp
// ceil(a/b) without math library:
(a + b - 1) / b

// Why b-1?
// → Tightest value that:
//   rounds up non-exact divisions ✅
//   keeps exact divisions unchanged ✅
```

---

## Common Mistakes in Interviews ⚠️

```
1. int result instead of long long → overflow!
   For divisor=1, result can reach 10^5 × 10^6 = 10^11

2. result not reset between divisors in brute force
   → keeps accumulating wrong values!

3. high = some arbitrary large number
   → Should be max(nums) — derive it!

4. Not recognizing connection to Koko
   → Always mention pattern recognition!

5. Wrong direction → low=mid+1 when TRUE
   → That's maximize! Correct: high=mid-1
```

---

## Key Takeaways 🔥

- *"Smallest Divisor = Koko Eating Bananas — same soul!"*
- *"high = max(nums) — beyond this, result never improves."*
- *"long long result — divisor=1 causes overflow with int!"*
- *"Ceiling division (nums[i]+divisor-1)/divisor — always explain why!"*
- *"FALSE→TRUE = minimize = first TRUE = high=mid-1 when TRUE."*
- *"Pattern recognition from first glance — highest interview skill!"*
