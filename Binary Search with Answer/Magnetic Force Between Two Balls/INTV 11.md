# Magnetic Force Between Two Balls — Interview Style ⚡
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Maximize
> **Difficulty:** Medium
> **Leetcode:** #1552

---

## Problem Statement

Given array `position[]` representing basket positions and integer `m` (balls):
- Place `m` balls in baskets
- **Maximize** minimum magnetic force between any two balls
- Magnetic force between positions x and y = |x - y|
- Return that maximum minimum force

```
position=[1,2,3,4,7], m=3          → Output: 3
position=[5,4,3,2,1,1000000000], m=2 → Output: 999999999
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of position[i] and m?
2. Are positions sorted or unsorted?
3. Can positions have duplicates?
4. Is solution always guaranteed?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ position[i] ≤ 10^9
→ 2 ≤ m ≤ position.size()
→ Positions NOT sorted — must sort first!
→ All positions distinct
→ m ≤ position.size() → solution always exists!
→ Yes, start from brute force
```

---

## Pattern Recognition — Aggressive Cows Twin! 🔥

> This problem is **identical** to Aggressive Cows!

```
Aggressive Cows:          Magnetic Force:
──────────────────────────────────────────
stalls[]          →       position[]
k cows            →       m balls
distance          →       magnetic force = |x-y|
maximize min dist →       maximize min force
sort first        →       sort first
low = 1           →       low = 1
high = max-min    →       high = max-min
```

> 🔥 *"Literally identical solution — different variable names!"*

---

## Why Sort First? 🎯

```
Reason 1: Positive differences
→ Sorted positions → position[i]-lastPlaced always positive
→ Meaningful force calculation!

Reason 2: Greedy placement
→ Place ball at earliest valid position
→ Maximum room for future balls!
```

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `1` | Minimum meaningful force |
| `high` | `max-min` | Maximum possible gap between extreme positions |
| `ans` | `low` | Gets maximized during search |

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every possible force from max-min down to 1.
For each → check if m balls can be placed.
First valid force → maximum! Stop immediately.
```

### Code:
```cpp
class Solution {
public:
    bool isPossible(vector<int>& position, int m, int force) {
        int balls      = 1;
        int lastPlaced = position[0];

        for(int i = 1; i < position.size(); i++) {
            if(position[i] - lastPlaced >= force) {
                balls++;
                lastPlaced = position[i];
            }
        }
        return balls >= m;
    }

    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());

        int maxForce = position.back() - position.front();
        int ans      = 1;

        for(int force = maxForce; force >= 1; force--) {
            if(isPossible(position, m, force)) {
                ans = force;    // first valid = maximum!
                break;
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O(n log n) sort + O(maxForce × n)
SC : O(1)
```

### Bottleneck:
```
For max-min = 10^9:
→ 10^9 × n iterations 😬
Way too slow!
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
force:    1    2    3    4    5    6
works?:   ✅   ✅   ✅   ❌   ❌   ❌

Pattern: TRUE → FALSE (monotonic!)
→ Larger force → harder to place balls → ❌
→ Smaller force → easier to place balls → ✅
Last TRUE = maximum valid force = answer!
```

### Monotonic Pattern:
```
✅ ✅ ✅ ❌ ❌ ❌ ❌
         ↑
    BOUNDARY
  (last TRUE = answer)

Pattern   : TRUE → FALSE
Goal      : Find LAST TRUE
Type      : MAXIMIZE
Direction : when TRUE  → ans=mid, low=mid+1  (go right)
            when FALSE → high=mid-1           (go left)
```

### isPossible() Logic:
```
Sort positions first!
Place first ball at position[0] → balls=1
For each next position:
    if position[i] - lastPlaced >= force:
        → place ball! balls++, lastPlaced=position[i]
    else:
        → skip (too close)
return balls >= m
```

### Code:
```cpp
class Solution {
public:
    bool isPossible(vector<int>& position, int m, int force) {
        int balls      = 1;              // first ball at position[0]
        int lastPlaced = position[0];

        for(int i = 1; i < position.size(); i++) {
            if(position[i] - lastPlaced >= force) {
                balls++;
                lastPlaced = position[i];
            }
        }
        return balls >= m;
    }

    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());

        int low  = 1;
        int high = position.back() - position.front();
        int ans  = low;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(isPossible(position, m, mid)) {
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
     where d = max-min

SC : O(1) — no extra space
```

### Dry Run (position=[1,2,3,4,7], m=3):
```
After sort: [1,2,3,4,7]
low=1, high=6, ans=1

Iter 1: mid=3
        1→4: diff=3 >= 3 → balls=2, lastPlaced=4
        4→7: diff=3 >= 3 → balls=3
        balls=3 >= 3 ✅ → ans=3, low=4

Iter 2: mid=5
        1→7: diff=6 >= 5 → balls=2
        No more positions!
        balls=2 < 3 ❌ → high=3

low=4 > high=3 → STOP
return 3 ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Worst Case |
|---|---|---|---|
| Brute Force | O(maxForce × n) | O(1) | ~10^10 ❌ |
| **Optimal** | **O(n log n)** | **O(1)** | **~10^6** ✅ |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Range of position[i] and m?
 Are positions sorted?
 Any duplicates?
 [get answers]"

STEP 2 — PATTERN RECOGNITION:
"I immediately recognize this as
 identical to Aggressive Cows!

 stalls[]  → position[]
 k cows    → m balls
 distance  → magnetic force
 Same search space, same isPossible()!
 Sort first — two reasons:
 1. Positive differences
 2. Greedy placement works left to right"

STEP 3 — BRUTE FORCE:
"Try every force from max-min to 1.
 For each → greedy isPossible() check.
 First valid → maximum! Break.
 TC: O(maxForce × n). Too slow!"

STEP 4 — OPTIMAL:
"TRUE→FALSE monotonic pattern.
 Binary Search applicable!
 low=1, high=max-min
 Maximize → last TRUE → low=mid+1 when TRUE.
 TC: O(n log n)"

STEP 5 — EDGE CASES:
"m=2 → minimum case → always works ✅
 position.back()-position.front() → cleaner ✅
 balls=1 initially → first ball always placed ✅"
```

---

## Aggressive Cows vs Magnetic Force 🔥

```
Aggressive Cows:         Magnetic Force:
─────────────────────────────────────────
canPlaceCows()    →      isPossible()
stalls[]          →      position[]
k cows            →      m balls
distance          →      force
cows >= k         →      balls >= m
low=mid+1 TRUE    →      low=mid+1 TRUE
high=mid-1 FALSE  →      high=mid-1 FALSE
```

> 🔥 *"Literally identical code — different variable names!"*

---

## Common Mistakes in Interviews ⚠️

```
1. Forgetting to sort → distances meaningless!
2. Starting balls=0 → first ball never counted!
   Always: balls=1, lastPlaced=position[0]
3. Wrong direction → high=mid-1 when TRUE
   → That's minimize! Correct: low=mid+1 for maximize
4. Not recognizing connection to Aggressive Cows
   → Always mention pattern recognition!
5. Comparing adjacent positions instead of lastPlaced
   → position[i]-position[i-1] WRONG
   → position[i]-lastPlaced CORRECT
```

---

## Key Takeaways 🔥

- *"Magnetic Force = Aggressive Cows — identical solution!"*
- *"Sort for two reasons: positive differences + greedy placement."*
- *"TRUE→FALSE = maximize = last TRUE = go right when TRUE."*
- *"Track lastPlaced — not adjacent position difference."*
- *"Greedy: place ball at earliest valid position."*
- *"Pattern recognition in 1 second — that's true mastery!"*
