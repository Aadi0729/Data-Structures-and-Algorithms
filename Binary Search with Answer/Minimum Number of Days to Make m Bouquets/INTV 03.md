# Minimum Days to Make Bouquets — Interview Style 🌸
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #1482

---

## Problem Statement

Given array `bloomDay[]` where `bloomDay[i]` = day ith flower blooms,
integers `m` (bouquets needed) and `k` (adjacent flowers per bouquet):
- Return **minimum number of days** to make `m` bouquets
- Return `-1` if impossible

```
bloomDay=[1,10,3,10,2], m=3, k=1 → Output: 3
bloomDay=[1,10,3,10,2], m=3, k=2 → Output: -1
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of bloomDay[i], m and k?
2. What if m*k > bloomDay.size()? Return -1?
3. What is the length range of bloomDay array?
4. Should I start from brute force?
5. Can bloomDay array be empty?
```

**Interviewer Answers:**
```
→ 1 ≤ bloomDay[i] ≤ 10^9
→ 1 ≤ m, k ≤ 10^5
→ m*k > size → return -1 (impossible)
→ 1 ≤ bloomDay.size() ≤ 10^5
→ Yes, start from brute force
→ Empty array covered by m*k > size check!
```

> 🔥 **Sharp observation:**
> Empty array → size=0 → m*k > 0 → returns -1 automatically!
> ONE condition handles TWO edge cases!

---

## Key Insight — What does "day X" mean?

```
On day X → all flowers where bloomDay[i] <= X have bloomed.

bloomDay = [1, 10, 3, 10, 2], day = 3:
index    :  0   1   2   3   4
bloomed? : ✅  ❌  ✅  ❌  ✅
           (1≤3)(10>3)(3≤3)(10>3)(2≤3)
```

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every day from 1 to max(bloomDay).
For each day → check if m bouquets can be made.
First valid day → minimum days! Stop immediately.
```

### Search Space:
```
Min day = 1           → minimum meaningful day
Max day = max(bloomDay) → all flowers bloomed, no point going further
```

### canMakeBouquets() Logic:
```
Walk array left to right:
✅ bloomed     → count++
count == k     → bouquet++, count=0  (made one bouquet!)
❌ not bloomed → count=0             (adjacency broken → reset!)
return bouquets >= m
```

### Code:
```cpp
class Solution {
public:
    bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int day) {
        int count    = 0;
        int bouquets = 0;

        for(int i = 0; i < bloomDay.size(); i++) {
            if(bloomDay[i] <= day) {
                count++;
                if(count == k) {       // k adjacent found → bouquet!
                    bouquets++;
                    count = 0;         // reset for next bouquet
                }
            }
            else {
                count = 0;             // adjacency broken → reset!
            }
        }
        return bouquets >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        if((long long)m * k > bloomDay.size())
            return -1;                 // impossible!

        int maxDay = *max_element(bloomDay.begin(), bloomDay.end());
        int ans    = maxDay;

        for(int i = 1; i <= maxDay; i++) {
            if(canMakeBouquets(bloomDay, m, k, i)) {
                ans = i;               // first valid day = minimum!
                break;                 // no need to check further
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(max(bloomDay) × n)
     → outer loop runs max(bloomDay) times
     → each iteration → canMakeBouquets() → O(n)

SC : O(1) — no extra space
```

### Bottleneck:
```
For max(bloomDay) = 10^9, n = 10^5:
→ 10^9 × 10^5 = 10^14 operations 😬
→ Way too slow — will TLE!

Bottleneck = linear scan over all days
```

### What to say in interview:
```
"Brute force tries every day from 1 to max(bloomDay).
 For each day we count bouquets using adjacent flower logic.
 First valid day → return immediately.

 TC: O(max(bloomDay) × n), SC: O(1)
 Bottleneck: linear scan → 10^14 ops. Too slow!"
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
Look at days and whether they work:

day:     1    2    3    4  ....  10
works?:  ❌   ❌   ✅   ✅  ....  ✅

Pattern: FALSE → TRUE (monotonic!)
→ More days → more flowers bloom → easier to make bouquets ✅
→ Once a day works → all later days also work ✅
→ Once a day fails → all earlier days also fail ❌

Clean boundary exists → Binary Search applicable!
First TRUE = minimum days = answer!
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
low  = 1                              → minimum meaningful day
high = max(bloomDay)                  → all flowers bloomed
ans  = high (or -1 after edge check)  → gets minimized
```

### Code:
```cpp
class Solution {
public:
    bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int day) {
        int count    = 0;
        int bouquets = 0;

        for(int i = 0; i < bloomDay.size(); i++) {
            if(bloomDay[i] <= day) {
                count++;
                if(count == k) {
                    bouquets++;
                    count = 0;
                }
            }
            else {
                count = 0;             // adjacency broken → reset!
            }
        }
        return bouquets >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        // Edge case — impossible
        if((long long)m * k > bloomDay.size())
            return -1;

        int low  = 1;
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        int ans  = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canMakeBouquets(bloomDay, m, k, mid)) {
                ans  = mid;
                high = mid - 1;        // minimize → go left
            } else {
                low  = mid + 1;        // too early → go right
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log d)
     → log d iterations of binary search
     → each iteration → canMakeBouquets() → O(n)
     → total: O(n log d)
     where n = bloomDay.size(), d = max(bloomDay)

SC : O(1) — no extra space
```

### Dry Run (bloomDay=[1,10,3,10,2], m=3, k=1):
```
Edge check: 3*1=3 <= 5 → proceed
low=1, high=10, ans=10

Iter 1: mid=5
        bloomed: ✅❌✅❌✅ → bouquets=3 >= 3 → ans=5, high=4

Iter 2: mid=2
        bloomed: ✅❌❌❌✅ → bouquets=2 < 3 → low=3

Iter 3: mid=3
        bloomed: ✅❌✅❌✅ → bouquets=3 >= 3 → ans=3, high=2

low=3 > high=2 → STOP
return 3 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| Brute Force | O(max(bloomDay) × n) | O(1) | ~10^14 ❌ |
| **Optimal** | **O(n log d)** | **O(1)** | **~1.7×10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Few questions first.
 Range of bloomDay[i], m, k?
 What if m*k > size? Return -1?
 [get answers]
 Note: empty array covered by m*k > size check!"

STEP 2 — BRUTE FORCE:
"Try every day from 1 to max(bloomDay).
 For each day → adjacent flower counting.
 First valid day → return immediately.
 TC: O(max(bloomDay) × n), SC: O(1)
 Bottleneck: linear scan → 10^14 ops. Too slow!"

STEP 3 — OPTIMAL:
"Days follow FALSE→TRUE monotonic pattern.
 More days → more flowers bloom → easier!
 Binary Search applicable!
 low=1, high=max(bloomDay)
 canMakeBouquets() stays exactly same!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log d) → ~1.7×10^6 ops!"

STEP 4 — CODE + DRY RUN:
[write code confidently]
[dry run with bloomDay=[1,10,3,10,2], m=3, k=1]

STEP 5 — EDGE CASES:
"m*k > n → return -1 ✅
 long long for m*k overflow ✅
 empty array → covered by m*k > size ✅
 mid = low+(high-low)/2 → no overflow ✅"
```

---

## Common Mistakes in Interviews ⚠️

```
1. count = 0 outside else block → resets on every iteration!
   Always put count=0 in ELSE branch only.

2. int m*k overflow → (long long)m*k cast needed

3. Decrementing count on ❌ instead of resetting
   count-- is WRONG → count=0 is CORRECT
   Adjacency is completely broken!

4. Forgetting impossible case check before binary search

5. Wrong function name conflict (minDays for both functions)
   Use descriptive names: canMakeBouquets() vs minDays()
```

---

## Key Takeaways 🔥

- *"On day X → flowers where bloomDay[i] <= X have bloomed."*
- *"Adjacency breaks → reset count to 0, never decrement."*
- *"Empty array edge case covered by m*k > size check."*
- *"canMakeBouquets() identical in brute force and optimal."*
- *"ONE condition handles TWO edge cases — shows sharp thinking."*
- *"FALSE→TRUE = minimize = first TRUE = high=mid-1 when TRUE."*
