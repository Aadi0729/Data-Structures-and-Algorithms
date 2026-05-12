# Koko Eating Bananas — Interview Style 🍌
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #875

---

## Problem Statement

Given array `piles[]` where `piles[i]` = bananas in ith pile, and integer `h` (hours available):
- Koko eats `k` bananas/hour from one pile
- If pile has less than `k` bananas → finishes pile in 1 hour
- Return **minimum eating speed** `k` to finish all bananas within `h` hours

```
piles = [3,6,7,11], h = 8 → Output: 4
piles = [30,11,23,4,20], h = 5 → Output: 30
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of piles[i] and h?
2. Is h >= piles.size() always guaranteed?
   (if h < piles.size() → impossible!)
3. Can piles array be empty?
4. Is solution always guaranteed to exist?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ piles[i] ≤ 10^9
→ 1 ≤ h ≤ 10^9
→ h >= piles.size() always guaranteed
→ piles is always non-empty (1 ≤ piles.size() ≤ 10^4)
→ Solution always exists
→ Yes, start from brute force
```

> 🔥 **Key insight from clarification:**
> If h < piles.size() → impossible (each pile needs at least 1 hour)
> h >= piles.size() → solution always exists

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every possible speed from 1 to max(piles).
For each speed → calculate total hours needed.
First speed where totalHours <= h → minimum speed!
Stop immediately (no need to check further).
```

### isPossible() Logic:
```
For each pile → hours needed = ceil(pile / speed)
             = (pile + speed - 1) / speed  [ceiling division trick]
Sum all hours → return totalHours <= h
```

### Code:
```cpp
class Solution {
public:
    bool isPossible(vector<int>& piles, int hours, int k) {
        long long totalHours = 0;  // long long → overflow safe!
        for(int i = 0; i < piles.size(); i++) {
            totalHours += (piles[i] + k - 1) / k;  // ceiling division
        }
        return totalHours <= hours;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int maxSpeed = *max_element(piles.begin(), piles.end());
        int ans = maxSpeed;

        for(int i = 1; i <= maxSpeed; i++) {
            if(isPossible(piles, h, i)) {
                ans = i;    // first valid speed = minimum speed!
                break;      // no need to check further ✅
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(max(piles) × n)
     → outer loop runs max(piles) times
     → each iteration calls isPossible() → O(n)

SC : O(1) — no extra space
```

### Bottleneck:
```
For max(piles) = 10^9, n = 10^4:
→ 10^9 × 10^4 = 10^13 operations 😬
→ Way too slow — will TLE!

Bottleneck = trying every speed linearly
             even though most checks are unnecessary
```

### What to say in interview:
```
"Brute force tries every speed from 1 to max(piles).
 For each speed we calculate total hours using ceiling division.
 First valid speed is our answer — break immediately.

 TC: O(max(piles) × n), SC: O(1)

 Bottleneck: linear scan over speeds.
 For max(piles)=10^9, n=10^4 → 10^13 operations.
 Way too slow. Can I optimize?"
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
Look at speeds and whether they work:

speed:   1    2    3    4    5    6 .... max
works?:  ❌   ❌   ❌   ✅   ✅   ✅ .... ✅

Pattern: FALSE → TRUE (monotonic!)
→ Once a speed works → all higher speeds also work ✅
→ Once a speed fails → all lower speeds also fail ❌

Clean boundary exists → Binary Search applicable!
First TRUE = minimum speed = answer!
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
Direction : when TRUE  → ans=mid, high=mid-1 (go left)
            when FALSE → low=mid+1 (go right)
```

### Search Space:
```
low  = 1           → minimum meaningful speed (can't eat 0 bananas/hr)
high = max(piles)  → no benefit eating faster than largest pile
```

### isPossible(mid):
```
totalHours <= h     (same function as brute force!)
```

### Code:
```cpp
class Solution {
public:
    bool isPossible(vector<int>& piles, int hours, int k) {
        long long totalHours = 0;
        for(int i = 0; i < piles.size(); i++) {
            totalHours += (piles[i] + k - 1) / k;
        }
        return totalHours <= hours;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low  = 1;
        int high = *max_element(piles.begin(), piles.end());
        int ans  = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;  // overflow safe!

            if(isPossible(piles, h, mid)) {
                ans  = mid;
                high = mid - 1;    // minimize → go left (first TRUE)
            } else {
                low  = mid + 1;    // too slow → go right
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
     → total: O(n log m)
     where n = piles.size(), m = max(piles)

SC : O(1) — no extra space
```

### Dry Run (piles=[3,6,7,11], h=8):
```
low=1, high=11, ans=11

Iter 1: mid=6
        ceil(3/6)=1, ceil(6/6)=1, ceil(7/6)=2, ceil(11/6)=2
        total=6 <= 8 → ans=6, high=5

Iter 2: mid=3
        ceil(3/3)=1, ceil(6/3)=2, ceil(7/3)=3, ceil(11/3)=4
        total=10 > 8 → low=4

Iter 3: mid=4
        ceil(3/4)=1, ceil(6/4)=2, ceil(7/4)=2, ceil(11/4)=3
        total=8 <= 8 → ans=4, high=3

low=4 > high=3 → STOP
return 4 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case Operations |
|---|---|---|---|
| Brute Force | O(max(piles) × n) | O(1) | ~10^13 ❌ |
| **Optimal** | **O(n log m)** | **O(1)** | **~3×10^5** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Before coding — a few questions.
 What is range of piles[i] and h?
 Is h >= piles.size() always guaranteed?
 Can piles be empty?
 [get answers]
 Great. Starting with brute force."

STEP 2 — BRUTE FORCE:
"Try every speed from 1 to max(piles).
 For each speed → calculate total hours.
 Use ceiling division: (pile + k - 1) / k
 First speed where totalHours <= h → answer. Break!
 TC: O(max(piles) × n), SC: O(1)
 Bottleneck: linear scan → 10^13 ops. Too slow!"

STEP 3 — OPTIMAL:
"Key observation — speeds follow FALSE→TRUE pattern.
 Monotonic → Binary Search applicable!
 Search space: [1, max(piles)]
 isPossible(mid): totalHours <= h? (same function!)
 Minimize → first TRUE → high=mid-1 when TRUE.
 TC: O(n log m), SC: O(1)
 From 10^13 → ~3×10^5 operations!"

STEP 4 — CODE + DRY RUN:
[write code confidently]
[dry run with piles=[3,6,7,11], h=8]

STEP 5 — EDGE CASES:
"Overflow in totalHours → long long ✅
 mid = low+(high-low)/2 → no overflow ✅
 h >= piles.size() guaranteed → answer always exists ✅"
```

---

## Ceiling Division — Be Ready to Explain 🎯

```
"Why (pile + k - 1) / k?"

→ Integer division floors the result.
→ We need ceiling — round up.
→ Adding k-1 is the tightest value that:
   rounds up non-exact divisions ✅
   keeps exact divisions unchanged ✅

Example:
ceil(7/3) = 3
(7 + 3 - 1) / 3 = 9/3 = 3 ✅

ceil(6/3) = 2
(6 + 3 - 1) / 3 = 8/3 = 2 ✅
```

---

## Common Mistakes in Interviews ⚠️

```
1. Using 'max' as variable name → conflicts with std::max
2. int totalHours → overflows for large inputs → use long long
3. Forgetting early termination in brute force
4. Wrong ceiling division → using pile/k directly (floors!)
5. Wrong direction → low=mid+1 when TRUE (that's maximize!)
   Correct for minimize: high=mid-1 when TRUE
6. Not explaining WHY binary search works here
   Always mention monotonic behavior explicitly!
```

---

## Key Takeaways 🔥

- *"isPossible() is identical in brute force and optimal — only outer loop changes."*
- *"FALSE→TRUE pattern = minimize = first TRUE = high=mid-1 when TRUE."*
- *"Ceiling division (pile+k-1)/k — always explain why in interview."*
- *"long long totalHours — overflow is a common interview trap here."*
- *"No benefit eating faster than max(piles) — that's why high=max(piles)."*
- *"Binary search reuses isPossible() — no extra work needed!"*
