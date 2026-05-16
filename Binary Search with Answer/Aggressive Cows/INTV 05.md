# Aggressive Cows — Interview Style 🐄
## Brute Force → Better → Optimal

> **Pattern:** Binary Search on Answer — Maximize
> **Difficulty:** Hard
> **Platform:** GFG / Striver SDE Sheet

---

## Problem Statement

Given array `stalls[]` representing positions of stalls and integer `k` (cows):
- Place `k` cows in stalls
- **Maximize** minimum distance between any two cows
- Return that maximum possible minimum distance

```
stalls=[1,2,4,8,9], k=3 → Output: 3  (place at 1,4,8)
stalls=[1,2,3], k=2     → Output: 2  (place at 1,3)
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of stalls[i] and k?
2. Can stalls have duplicate positions?
   (Two cows can't be at same position!)
3. Are stalls sorted or unsorted?
   (CRITICAL — drives entire solution!)
4. What if k > stalls.size()?
5. Is solution always guaranteed to exist?
6. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ stalls[i] ≤ 10^9
→ 2 ≤ k ≤ stalls.size()
→ Stalls can have duplicates
→ Stalls are NOT sorted — must sort first!
→ k ≤ stalls.size() always → solution always exists
→ Yes, start from brute force
```

> 🔥 **Key constraint:** 2 ≤ k ≤ stalls.size()
> → At least 2 cows → minimum distance always meaningful
> → k never exceeds stalls → always placeable
> → No impossible case!

---

## Why Sort First? — TWO Reasons 🎯

```
Reason 1: Positive differences
"Sorted positions → stalls[i] - lastPlaced always positive
 → meaningful distance calculation"

Reason 2: Greedy placement
"Sorted order → place cow at earliest valid position
 → maximum room for future cows"
```

> 🔥 *"Always explain WHY you sort — not just THAT you sort.
>      Two reasons shows deep understanding!"*

---

## APPROACH 1 — True Brute Force

### Intuition:
```
Try every possible combination of k cows from n stalls.
For each combination → find minimum distance between adjacent cows.
Track maximum of all minimum distances.
Return that maximum.
```

### Example:
```
stalls = [1,2,4,8,9], k = 3

All combinations:
[1,2,4] → min dist = 1
[1,2,8] → min dist = 1
[1,4,8] → min dist = 3 ← best so far!
[1,4,9] → min dist = 3
[2,4,8] → min dist = 2
...

Answer = 3
```

### Complexity:
```
TC : O(C(n,k) × k) → EXPONENTIAL 😬
     C(n,k) combinations × k for min distance

SC : O(k) — store current combination
```

### What to say in interview:
```
"True brute force tries every combination of k cows
 from n stalls — that's C(n,k) combinations.
 For each → find minimum distance.
 Track maximum across all.

 TC: O(C(n,k) × k) → exponential.
 For n=10^5, k=50 → astronomically large.
 Clearly too slow.

 But there's a smarter way —
 instead of trying every placement,
 can I search over possible DISTANCES directly?"
```

---

## APPROACH 2 — Better (Search Over Distances)

### Key Insight:
```
Instead of trying every placement —
ask: "Can I place k cows with minimum distance d?"

Try every distance from maxDistance down to 1.
First distance that works → maximum valid distance!
```

### canPlaceCows() Logic:
```
Sort stalls first!
Place first cow at stalls[0] → cows=1, lastPlaced=stalls[0]
For each next stall:
    if stalls[i] - lastPlaced >= distance:
        → place cow! cows++, lastPlaced=stalls[i]
    else:
        → skip (too close)
return cows >= k
```

### Code:
```cpp
class Solution {
public:
    bool canPlaceCows(vector<int>& stalls, int k, int distance) {
        int cows       = 1;              // first cow at stalls[0]
        int lastPlaced = stalls[0];

        for(int i = 1; i < stalls.size(); i++) {
            if(stalls[i] - lastPlaced >= distance) {
                cows++;
                lastPlaced = stalls[i];  // update last placed position
            }
        }
        return cows >= k;
    }

    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());  // MUST sort first!

        int maxDistance = stalls.back() - stalls.front();
        int ans         = 1;

        for(int i = maxDistance; i >= 1; i--) {  // search from max to 1
            if(canPlaceCows(stalls, k, i)) {
                ans = i;    // first valid distance = maximum!
                break;
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log n) sort + O(maxDistance × n) search
     → O(maxDistance × n) dominates

SC : O(1) — no extra space
```

### Bottleneck:
```
For maxDistance = 10^9, n = 10^5:
→ 10^9 × 10^5 = 10^14 operations 😬
Way too slow!
```

---

## APPROACH 3 — Optimal (Binary Search on Answer)

### Key Observation:
```
Look at distances and whether they work:

distance:  1    2    3    4    5    6    7    8
works?:    ✅   ✅   ✅   ❌   ❌   ❌   ❌   ❌

Pattern: TRUE → FALSE (monotonic!)
→ Larger distance → harder to place cows → ❌
→ Once fails → all larger distances also fail ❌
→ Once works → all smaller distances also work ✅

Last TRUE = maximum valid distance = answer!
```

### Monotonic Pattern:
```
✅ ✅ ✅ ❌ ❌ ❌ ❌ ❌
         ↑
    BOUNDARY
  (last TRUE = answer)

Pattern   : TRUE → FALSE
Goal      : Find LAST TRUE
Type      : MAXIMIZE
Direction : when TRUE  → ans=mid, low=mid+1  (go right)
            when FALSE → high=mid-1           (go left)
```

### Why TRUE→FALSE = MAXIMIZE? 🎯
```
"Till the point it's TRUE — we can place cows
 at that minimum distance.
 Once FALSE — distance is too large to place cows.
 So last TRUE = maximum possible minimum distance!"
```

### Search Space:
```
low  = 1                           → minimum meaningful distance
high = max(stalls) - min(stalls)   → maximum possible gap
```

### Code:
```cpp
class Solution {
public:
    bool canPlaceCows(vector<int>& stalls, int k, int distance) {
        int cows       = 1;
        int lastPlaced = stalls[0];

        for(int i = 1; i < stalls.size(); i++) {
            if(stalls[i] - lastPlaced >= distance) {
                cows++;
                lastPlaced = stalls[i];
            }
        }
        return cows >= k;
    }

    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());  // MUST sort first!

        int low  = 1;
        int high = stalls.back() - stalls.front();
        int ans  = 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canPlaceCows(stalls, k, mid)) {
                ans = mid;
                low = mid + 1;   // maximize → go right (last TRUE)
            } else {
                high = mid - 1;  // too large → go left
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log n) sort + O(n log d) binary search
     → O(n log n) dominates
     where n = stalls.size()
           d = max(stalls) - min(stalls)

SC : O(1) — no extra space
```

### Dry Run (stalls=[1,2,4,8,9], k=3):
```
After sort: [1,2,4,8,9]
low=1, high=8, ans=1

Iter 1: mid=4
        Place at 1, skip 2, skip 4(1+4=5>4? no wait...)
        1→4: diff=3 < 4 → skip
        1→8: diff=7 >= 4 → place! cows=2, lastPlaced=8
        8→9: diff=1 < 4 → skip
        cows=2 < 3 → ❌ → high=3

Iter 2: mid=2
        1→2: diff=1 < 2 → skip
        1→4: diff=3 >= 2 → place! cows=2, lastPlaced=4
        4→8: diff=4 >= 2 → place! cows=3, lastPlaced=8
        cows=3 >= 3 → ✅ → ans=2, low=3

Iter 3: mid=3
        1→4: diff=3 >= 3 → place! cows=2, lastPlaced=4
        4→8: diff=4 >= 3 → place! cows=3, lastPlaced=8
        cows=3 >= 3 → ✅ → ans=3, low=4

low=4 > high=3 → STOP
return 3 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| True Brute Force | O(C(n,k) × k) | O(k) | Exponential 😬 |
| Better | O(maxDistance × n) | O(1) | ~10^14 ❌ |
| **Optimal** | **O(n log n)** | **O(1)** | **~10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Range of stalls[i] and k?
 Can stalls have duplicates?
 Are stalls sorted or unsorted?
 [get answers]"

STEP 2 — TRUE BRUTE FORCE:
"Try every combination of k cows from n stalls.
 C(n,k) combinations → exponential TC.
 Clearly too slow.
 But smarter approach — search over distances directly!"

STEP 3 — BETTER:
"Search every distance from max-min to 1.
 For each → greedy canPlaceCows() check.
 TC: O(maxDistance × n), SC: O(1)
 Still too slow → 10^14 ops!"

STEP 4 — OPTIMAL:
"Distances follow TRUE→FALSE monotonic pattern.
 Larger distance → harder to place → fails.
 Binary Search applicable!
 Sort first — two reasons:
 1. Positive differences for meaningful distances
 2. Greedy placement works left to right
 low=1, high=max-min
 Maximize → last TRUE → low=mid+1 when TRUE.
 TC: O(n log n), SC: O(1)"

STEP 5 — EDGE CASES:
"k=2 → minimum case ✅
 All same positions → high=0, ans=0 ✅
 stalls.back()-stalls.front() → cleaner ✅"
```

---

## Common Mistakes in Interviews ⚠️

```
1. Forgetting to sort → distances meaningless!
2. i++ instead of i-- in better approach → infinite loop!
3. high = low-1 instead of high = mid-1 → wrong elimination!
4. Comparing adjacent stalls instead of lastPlaced
   stalls[i]-stalls[i-1] WRONG → stalls[i]-lastPlaced CORRECT
5. Starting cows=0 → first cow never counted!
   Always: cows=1, lastPlaced=stalls[0]
6. Saying "monotonically decreasing" for TRUE→FALSE pattern
   Correct: "monotonic condition with TRUE→FALSE flip"
```

---

## Key Takeaways 🔥

- *"Three levels: exponential → linear → log. Most dramatic optimization!"*
- *"Sort for two reasons: positive differences + greedy placement."*
- *"TRUE→FALSE = maximize = last TRUE = go right when TRUE."*
- *"Track lastPlaced — not adjacent stall difference."*
- *"Greedy: place at earliest valid position — waiting longer never helps."*
- *"Minimum distance always between adjacent placed cows — skip non-adjacent!"*
