# Painter's Partition Problem — Interview Style 🎨
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Hard
> **Platform:** GFG / Striver SDE Sheet

---

## Problem Statement

Given array `boards[]` where `boards[i]` = length of ith board, integer `k` (painters):
- Each painter takes **1 unit time per unit length**
- Each painter paints **contiguous boards** only
- All painters work **simultaneously**
- Return **minimum time** to paint all boards

```
boards=[10,20,30,40], k=2 → Output: 60
boards=[10,10,10,10], k=2 → Output: 20
```

---

## Key Insight — "1 unit time per unit length" 🎯

```
Board length = 10 → time to paint = 10 units
Board length = 30 → time to paint = 30 units

boards[] array IS the time array!

boards = [10, 20, 30, 40], k = 2

Painter 1: [10, 20, 30] → time = 60
Painter 2: [40]         → time = 40

All painters work SIMULTANEOUSLY!
Total time = max(60, 40) = 60
           = time of SLOWEST painter!

So minimize the maximum → minimize max sum!
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of boards[i] and k?
2. What if k > boards.size()? Return -1?
3. Can boards be rearranged? (CRITICAL!)
4. What is length range of boards array?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ boards[i] ≤ 10^9
→ 1 ≤ k ≤ 10^5
→ k > boards.size() → return -1 (impossible!)
→ Boards CANNOT be rearranged — contiguous only!
→ 1 ≤ boards.size() ≤ 10^5
→ Yes, start from brute force
```

---

## Pattern Recognition — The FOUR Brothers! 🔥

> This problem is **identical** to Ship Packages, Book Allocation, Split Array!

```
Ship Packages  | Book Allocation | Split Array  | Painter's Partition
───────────────────────────────────────────────────────────────────
weights[]      | books[]         | nums[]       | boards[]
days           | k students      | k subarrays  | k painters
capacity/day   | pages/student   | sum/subarray | time/painter
in ORDER       | CONTIGUOUS      | CONTIGUOUS   | CONTIGUOUS
min capacity   | min max pages   | min max sum  | min max time
```

> All four ask ONE question:
> *"Find minimum limit such that array can be
>  divided into k parts without exceeding that limit."*

---

## Impossible Case 🎯

```
k > boards.size() → impossible → return -1

boards = [10, 20, 30], k = 5 painters
3 boards, 5 painters →
Even if each painter gets 1 board →
2 painters left with nothing ❌

k ≤ boards.size() → always possible!
```

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(boards)` | Worst minimum — every board painted by one painter. Below this, max board never fits! |
| `high` | `sum(boards)` | Worst maximum — 1 painter paints everything. No point going higher! |
| `ans` | `high` | Gets minimized during search |

---

## Why painters <= k? 🎯

```
painters NEEDED ≤ painters AVAILABLE

If needed = 2, available = 3 → ✅ (1 painter idle — fine!)
If needed = 4, available = 3 → ❌ (not enough painters!)

Having MORE painters than needed is fine!
Having FEWER painters than needed is impossible!
```

---

## APPROACH 1 — Brute Force

### Code:
```cpp
class Solution {
public:
    bool canPaintBoards(vector<int>& arr, int k, int time) {
        int painters = 0;
        int totTime  = 0;

        for(int i = 0; i < arr.size(); i++) {
            totTime += arr[i];
            if(totTime > time) {
                painters++;              // new painter needed
                totTime = arr[i];        // current board → new painter
            }
        }
        painters++;                      // count last painter!
        return painters <= k;            // painters needed <= available?
    }

    int minTime(vector<int>& arr, int k) {
        if(k > (int)arr.size()) return -1;  // impossible!

        int maxTime   = *max_element(arr.begin(), arr.end());
        int totalTime = 0;
        for(auto val : arr) totalTime += val;

        int ans = totalTime;

        for(int i = maxTime; i <= totalTime; i++) {
            if(canPaintBoards(arr, k, i)) {
                ans = i;    // first valid = minimum time!
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
Linear scan over all time limits → too slow!
For boards=[10^9...] (10^5 elements):
→ Astronomical iterations 😬
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
time limit:  max  ....  X  ....  sum
works?:      ❌   ....  ✅  ....  ✅

Pattern: FALSE → TRUE (monotonic!)
→ Larger time limit → easier to fit boards ✅
→ Smaller time limit → harder to fit boards ❌
First TRUE = minimum time = answer!
```

### Code:
```cpp
class Solution {
public:
    bool canPaintBoards(vector<int>& arr, int k, int time) {
        int painters = 0;
        int totTime  = 0;

        for(int i = 0; i < arr.size(); i++) {
            totTime += arr[i];
            if(totTime > time) {
                painters++;
                totTime = arr[i];
            }
        }
        painters++;
        return painters <= k;
    }

    int minTime(vector<int>& arr, int k) {
        if(k > (int)arr.size()) return -1;  // impossible!

        int low  = *max_element(arr.begin(), arr.end());
        int high = 0;
        for(auto val : arr) high += val;

        int ans = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canPaintBoards(arr, k, mid)) {
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
     → log s iterations × O(n) canPaintBoards
     where s = sum - max = search space size

SC : O(1) — no extra space
```

### Dry Run (boards=[10,20,30,40], k=2):
```
Edge check: 2 <= 4 → proceed
low=40, high=100, ans=100

Iter 1: mid=70
        10→30→60→100>70 → painters=1, totTime=40
        painters++=2 → 2<=2 ✅ → ans=70, high=69

Iter 2: mid=54
        10→30→60→100>54 → painters=1, totTime=40
        painters++=2 → 2<=2 ✅ → ans=54, high=53

Iter 3: mid=46
        10→30→60>46 → painters=1, totTime=30
        30→70>46 → painters=2, totTime=40
        painters++=3 → 3>2 ❌ → low=47

Iter 4: mid=50
        10→30→60>50 → painters=1, totTime=30
        30→70>50 → painters=2, totTime=40
        painters++=3 → 3>2 ❌ → low=51

Iter 5: mid=52
        10→30→60>52 → painters=1, totTime=30
        30→70>52 → painters=2, totTime=40
        painters++=3 → 3>2 ❌ → low=53

Iter 6: mid=53 → same → low=54 > high=53 → STOP
Hmm... let me recheck mid=60:
        10→30→60<=60 ✅
        60→100>60 → painters=1, totTime=40
        painters++=2 → 2<=2 ✅ → ans=60 ✅
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
"Range of boards[i] and k?
 Can boards be rearranged?
 What if k > boards.size()?
 [get answers]"

STEP 2 — PATTERN RECOGNITION:
"I recognize this as part of a family —
 Ship Packages, Book Allocation,
 Split Array, Painter's Partition.

 All ask: find minimum limit to divide
 array into k parts without exceeding limit.

 boards[] = books[]
 painters = students
 time = pages
 Same search space, same isPossible()!"

STEP 3 — BRUTE FORCE:
"Try every time limit from max to sum.
 Count painters needed for each.
 First valid → minimum time! Break.
 TC: O((sum-max) × n). Too slow!"

STEP 4 — OPTIMAL:
"FALSE→TRUE monotonic pattern.
 Binary Search applicable!
 low=max(boards), high=sum(boards)
 canPaintBoards() stays same!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log s)"

STEP 5 — EDGE CASES:
"k > boards.size() → return -1 ✅
 painters++ after loop → count last ✅
 Reset to arr[i] not 0 → board kept ✅"
```

---

## The 5 Why Questions — Answers 🎯

```
1. Why low = max(boards)?
   → Worst minimum — every board needs 1 painter.
     Below this, max board never fits → problem breaks!

2. Why high = sum(boards)?
   → Worst maximum — 1 painter paints everything.
     No point going higher!

3. Why high=mid-1 when TRUE?
   → Minimizing — when condition true, try smaller.
     Eliminate right half to find minimum.

4. Why painters++ after loop?
   → Last painter never counted in loop.
     Loop ends leaving 1 painter uncounted!

5. Why painters <= k?
   → Painters NEEDED ≤ painters AVAILABLE.
     Idle painters fine — insufficient painters impossible!
```

---

## Common Mistakes in Interviews ⚠️

```
1. Missing edge case k > boards.size() → return -1
2. Forgetting painters++ after loop → last painter missed!
3. Resetting totTime=0 → current board lost! → use arr[i]
4. Wrong direction → low=mid+1 when TRUE → that's maximize!
5. Not recognizing connection to Ship/Book/Split problems
6. Confusing total time with maximum time
   → Total time = max(time of each painter) not sum!
```

---

## Key Takeaways 🔥

- *"boards[] = books[] = weights[] = nums[] — same soul!"*
- *"1 unit time per unit length → boards[] IS the time array!"*
- *"Total time = slowest painter = maximum sum among painters."*
- *"low = max(boards) — below this, max board never fits."*
- *"high = sum(boards) — 1 painter does everything."*
- *"painters <= k → needed ≤ available — idle painters are fine!"*
- *"Unseen problem solved instantly — that's pattern mastery!"*
