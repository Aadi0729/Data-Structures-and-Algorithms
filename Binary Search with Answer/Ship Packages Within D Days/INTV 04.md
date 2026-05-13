# Ship Packages in D Days — Interview Style 📦
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #1011

---

## Problem Statement

Given array `weights[]` where `weights[i]` = weight of ith package, and integer `days`:
- Ship all packages in **given order** within `days` days
- Each day load packages until capacity exceeded
- Return **minimum weight capacity** to ship all packages within `days` days

```
weights=[1,2,3,4,5,6,7,8,9,10], days=5 → Output: 15
weights=[3,2,2,4,1,4], days=3          → Output: 6
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of weights[i] and days?
2. Can packages be rearranged? (CRITICAL!)
3. What if weights array is empty?
4. Is solution always guaranteed to exist?
5. Are there any impossible cases?
6. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ weights[i] ≤ 500
→ 1 ≤ days ≤ 5×10^4
→ Packages CANNOT be rearranged — must ship in order!
→ weights always non-empty (1 ≤ weights.size() ≤ 5×10^4)
→ Solution ALWAYS exists — no impossible case!
→ Yes, start from brute force
```

> 🔥 **Key insight from clarification:**
> No impossible case here — unlike Bouquets!
> Capacity can always be increased to compensate for fewer days.
> Even if days=1 → capacity=sum(weights) → ships everything in 1 day!

---

## Why No Impossible Case? 🧠

```
Bouquets:                          Ship Packages:
m*k > n → IMPOSSIBLE               days < weights.size() → STILL POSSIBLE!
Flowers are fixed —                Just increase capacity to fit
can't change positions!            multiple packages per day!

Even days=1 works:
→ capacity = sum(weights)
→ ship everything in 1 day ✅
```

> 🔥 *"In Ship Packages — capacity is flexible.
>      You can always adjust it to compensate for fewer days."*

---

## Search Space — NEW CONCEPT 🔥

> **For the first time — `low ≠ 1`!**

```
low  = max(weights)
     → below this, heaviest package can NEVER be loaded → problem breaks!

high = sum(weights)
     → load everything in 1 day → no point going higher
```

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(weights)` | Min capacity where every package can fit |
| `high` | `sum(weights)` | Max capacity needed — 1 day shipping |

> 🔥 **Universal Rule:**
> *"low = below this, problem breaks.
>  high = above this, pointless."*

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every capacity from max(weights) to sum(weights).
For each capacity → check if all packages ship in days days.
First valid capacity → minimum capacity! Stop immediately.
```

### canShipPackages() Logic:
```
Walk array left to right, accumulate load:
totalWeight += weights[i]
if totalWeight > capacity:
    → new day (count_days++)
    → reset totalWeight = weights[i]  ← current package goes to new day!
after loop:
    → count_days++  ← count last day!
return count_days <= days
```

### Code:
```cpp
class Solution {
public:
    bool canShipPackages(vector<int>& weights, int days, int weight_capacity) {
        int count_days       = 0;
        long long totalWeight = 0;

        for(int i = 0; i < weights.size(); i++) {
            totalWeight += weights[i];

            if(totalWeight > weight_capacity) {
                count_days++;                    // new day needed
                totalWeight = weights[i];        // current package → new day
            }
        }
        count_days++;                            // count last day!
        return count_days <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int maxWeight   = *max_element(weights.begin(), weights.end());
        int totalWeight = 0;
        for(auto val : weights) totalWeight += val;

        int ans = totalWeight;

        for(int i = maxWeight; i <= totalWeight; i++) {
            if(canShipPackages(weights, days, i)) {
                ans = i;        // first valid capacity = minimum!
                break;          // no need to check further
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O((sum - max) × n)
     → outer loop runs (sum-max) times
     → each iteration → canShipPackages() → O(n)

SC : O(1) — no extra space
```

### Bottleneck:
```
For weights=[500,500,...500] (50000 elements):
sum = 25,000,000, max = 500
range = 24,999,500 × 50,000 = ~10^12 ops 😬
Way too slow!
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
Look at capacities and whether they work:

capacity: max  ....  X  ....  sum
works?:   ❌   ....  ✅  ....  ✅

Pattern: FALSE → TRUE (monotonic!)
→ More capacity → fewer days → easier to ship ✅
→ Once capacity works → all higher capacities work ✅
→ Once capacity fails → all lower capacities fail ❌

Clean boundary → Binary Search applicable!
First TRUE = minimum capacity = answer!
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

### Code:
```cpp
class Solution {
public:
    bool canShipPackages(vector<int>& weights, int days, int weight_capacity) {
        int count_days        = 0;
        long long totalWeight = 0;

        for(int i = 0; i < weights.size(); i++) {
            totalWeight += weights[i];

            if(totalWeight > weight_capacity) {
                count_days++;
                totalWeight = weights[i];
            }
        }
        count_days++;
        return count_days <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int low  = *max_element(weights.begin(), weights.end());
        int high = 0;
        for(auto val : weights) high += val;

        int ans = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;   // overflow safe!

            if(canShipPackages(weights, days, mid)) {
                ans  = mid;
                high = mid - 1;                  // minimize → go left
            } else {
                low  = mid + 1;                  // too small → go right
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log s)
     → log s iterations of binary search
     → each iteration → canShipPackages() → O(n)
     → total: O(n log s)
     where n = weights.size()
           s = sum - max = search space size

SC : O(1) — no extra space
```

### Dry Run (weights=[1,2,3,4,5,6,7,8,9,10], days=5):
```
low=10, high=55, ans=55

Iter 1: mid=32
        All packages fit in 2 days → 2<=5 ✅ → ans=32, high=31

Iter 2: mid=20
        Fits in 3 days → 3<=5 ✅ → ans=20, high=19

Iter 3: mid=14
        Fits in 6 days → 6>5 ❌ → low=15

Iter 4: mid=17
        Fits in 4 days → 4<=5 ✅ → ans=17, high=16

Iter 5: mid=15
        Fits in 5 days → 5<=5 ✅ → ans=15, high=14

low=15 > high=14 → STOP
return 15 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| Brute Force | O((sum-max) × n) | O(1) | ~10^12 ❌ |
| **Optimal** | **O(n log s)** | **O(1)** | **~7×10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Few questions first.
 Range of weights[i] and days?
 Can packages be rearranged?
 Any impossible case?
 [get answers]
 Key insight: no impossible case —
 capacity adjusts for any days!"

STEP 2 — BRUTE FORCE:
"Try every capacity from max(weights) to sum(weights).
 For each → accumulate load, new day when exceeded.
 Count last day after loop!
 First valid capacity → return immediately.
 TC: O((sum-max) × n), SC: O(1)
 Bottleneck: linear scan → ~10^12 ops. Too slow!"

STEP 3 — OPTIMAL:
"Capacities follow FALSE→TRUE monotonic pattern.
 More capacity → fewer days → easier!
 Binary Search applicable!
 low=max(weights) ← not 1 this time!
 high=sum(weights)
 canShipPackages() stays exactly same!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log s) → ~7×10^6 ops!"

STEP 4 — CODE + DRY RUN:
[write code confidently]
[dry run with weights=[1..10], days=5]

STEP 5 — EDGE CASES:
"No impossible case → capacity always adjustable ✅
 Count last day after loop ✅
 Reset to weights[i] not 0 on new day ✅
 low=max not 1 — derived from constraints ✅
 mid = low+(high-low)/2 → no overflow ✅"
```

---

## Two Things to Highlight in Interview 🎯

```
Highlight 1 — Why low ≠ 1:
"Notice low = max(weights), not 1.
 Below this → heaviest package can never load!
 low is always derived from constraints —
 never assume it's always 1!"

Highlight 2 — No Impossible Case:
"Unlike Bouquets — no -1 case here.
 Capacity is flexible — always adjustable.
 Even days=1 works with capacity=sum(weights)."
```

---

## Common Mistakes in Interviews ⚠️

```
1. low = 1 instead of max(weights)
   → Always derive low from constraints!

2. high = n*(n+1)/2
   → WRONG — only works for [1,2,3...n]
   → Always sum actual array!

3. Forgetting count last day after loop
   → count_days++ after loop is critical!

4. Resetting totalWeight = 0 instead of weights[i]
   → Current package gets lost!

5. Assuming impossible case exists
   → Ship Packages always has valid answer!
```

---

## Key Takeaways 🔥

- *"low = max(weights) — below this, heaviest package never loads."*
- *"high = sum(weights) — above this, answer never improves."*
- *"No impossible case — capacity is flexible unlike bouquets."*
- *"Always count last day after loop — easiest bug to miss."*
- *"Reset to weights[i] not 0 — current package goes to new day."*
- *"canShipPackages() identical in brute force and optimal."*
- *"low ≠ 1 — always derive search space from constraints!"*
