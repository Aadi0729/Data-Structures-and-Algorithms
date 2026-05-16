# Aggressive Cows 🐄

> **Pattern:** Binary Search on Answer — Maximize
> **Difficulty:** Hard
> **Platform:** GFG / Striver SDE Sheet

---

## Problem Statement

Given an array `stalls[]` representing positions of stalls and integer `k` (number of cows):
- Place `k` cows in stalls
- **Maximize** the minimum distance between any two cows
- Return that maximum possible minimum distance

**Example:**
```
stalls = [1, 2, 4, 8, 9], k = 3
Output: 3  (place cows at 1, 4, 8)
```

---

## Key Insight — What Are We Maximizing?

> We want to spread cows as far apart as possible.
> But we measure success by the **minimum gap** between any two adjacent cows.
> So we maximize that minimum gap.

```
Placement [1, 2, 4] → min distance = 1  ❌ (cows too close)
Placement [1, 4, 9] → min distance = 3  ✅ (better spread)
Placement [1, 4, 8] → min distance = 3  ✅ (also valid)
```

> 🔥 **Key observation:** Minimum distance is always between **adjacent placed cows** — never need to check non-adjacent pairs!

---

## Why Brute Force is Painful?

```
Try every possible combination of k cows from n stalls:
→ C(n, k) combinations — exponentially slow!

For n=20, k=5 → C(20,5) = 15,504 combinations 😬
```

---

## Why Binary Search Works Here?

As minimum distance increases → harder to place all k cows:

```
distance:  1    2    3    4    5    6    7    8
works?:    ✅   ✅   ✅   ❌   ❌   ❌   ❌   ❌
```

**Monotonic pattern: TRUE → FALSE**
- If distance `d` works → all smaller distances also work ✅
- If distance `d` fails → all larger distances also fail ❌

> 🔥 This monotonic behavior = Binary Search applicable!

---

## Step 0 — Sort The Stalls First!

```cpp
sort(stalls.begin(), stalls.end());
```

**Why sort?**
- Positions need increasing order to calculate meaningful distances
- Greedy placement only works left to right on sorted array
- `stalls[i] - lastPlaced` must always be positive

> 🔥 *"Always sort stalls first — unsorted positions give meaningless distances."*

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `1` | Minimum meaningful distance — cows can't overlap |
| `high` | `max(stalls) - min(stalls)` | Maximum possible gap — placing 2 cows at extremes |
| `ans` | `high` | Gets maximized during search |

```
stalls = [1, 2, 4, 8, 9]
low  = 1
high = 9 - 1 = 8
```

---

## isPossible() Logic — Greedy Placement

> Given minimum distance `mid` — can we place `k` cows with every adjacent pair at least `mid` apart?

**Greedy Strategy:**
```
Place first cow at stalls[0] — always!
For each next stall:
    if stalls[i] - lastPlaced >= distance:
        → place cow here ✅
        → update lastPlaced = stalls[i]
        → cows++
    else:
        → skip this stall ❌ (too close to last cow)
return cows >= k
```

**Why greedy works?**
> Placing cow at earliest valid position **never hurts** — it only gives more room for future cows. Waiting longer never helps!

---

## Why Skip When `diff < distance`?

```
stalls = [1, 2, 4, 8, 9], distance = 3
lastPlaced = 1

stalls[1] = 2 → diff = 2-1 = 1 < 3 → SKIP!
```

> Placing cow at position 2 would create gap of only 1 — violates minimum distance requirement of 3!

```
positions: 1    2    3    4    5    6    7    8    9
           🐄   ❌             ✅             ✅
                ↑              ↑
          too close!     earliest valid (1+3=4)
```

---

## Dry Run

```
stalls = [1, 2, 4, 8, 9], k = 3, distance = 3
lastPlaced = 1, cows = 1
```

| i | stalls[i] | diff | diff >= 3? | cows | lastPlaced |
|---|---|---|---|---|---|
| 1 | 2 | 2-1=1 | ❌ skip | 1 | 1 |
| 2 | 4 | 4-1=3 | ✅ place! | 2 | 4 |
| 3 | 8 | 8-4=4 | ✅ place! | 3 | 8 |
| 4 | 9 | 9-8=1 | ❌ skip | 3 | 8 |

`cows = 3 >= k = 3` → ✅ **distance 3 works!**

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& stalls, int k, int distance) {
        int cows      = 1;           // always place first cow at stalls[0]
        int lastPlaced = stalls[0];  // track last placed position

        for (int i = 1; i < stalls.size(); i++) {
            int diff = stalls[i] - lastPlaced;

            if (diff >= distance) {  // gap is valid → place cow greedily
                cows++;
                lastPlaced = stalls[i];
            }
            // else: gap too small → skip this stall
        }
        return cows >= k;
    }

    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());  // MUST sort first!

        int low  = 1;
        int high = stalls.back() - stalls.front();  // max - min
        int ans  = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(stalls, k, mid)) {
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

---

## Complexity Analysis

| | Value |
|---|---|
| Time | O(n log n) sort + O(n log d) binary search |
| Space | O(1) |

Where `n` = number of stalls, `d` = max(stalls) - min(stalls)

---

## Common Mistakes ⚠️

```cpp
// ❌ Forgetting to sort
// distances become meaningless without sorted order!

// ❌ Comparing with adjacent stall difference
diff = stalls[i] - stalls[i-1];  // WRONG!

// ✅ Always compare with lastPlaced
diff = stalls[i] - lastPlaced;   // CORRECT!

// ❌ Starting cows = 0
int cows = 0;  // first cow at stalls[0] never counted!

// ✅ Always start with first cow placed
int cows = 1;
int lastPlaced = stalls[0];

// ❌ Wrong binary search direction (minimize instead of maximize)
ans = mid; high = mid - 1;  // WRONG for maximize!

// ✅ Maximize → go right when TRUE
ans = mid; low = mid + 1;   // CORRECT!
```

---

## Pattern Comparison So Far 🔥

| Problem | low | high | isPossible | Pattern |
|---|---|---|---|---|
| Square Root | `1` | `n` | `mid*mid <= n` | Maximize |
| Koko Bananas | `1` | `max(piles)` | `totalHours <= h` | Minimize |
| Min Days Bouquets | `1` | `max(bloomDay)` | `bouquets >= m` | Minimize |
| Ship Packages | `max(weights)` | `sum(weights)` | `days <= d` | Minimize |
| **Aggressive Cows** | **`1`** | **`max-min`** | **`cows >= k`** | **Maximize** |

---

## Key Takeaways 🔥

- *"Always sort stalls — greedy placement only works on sorted positions."*
- *"Track lastPlaced — not adjacent stall difference."*
- *"Greedy = place cow at earliest valid position — waiting longer never helps."*
- *"Minimum distance is always between adjacent placed cows — skip non-adjacent checks."*
- *"Maximize problems → TRUE→FALSE → save ans, go right (low = mid+1)."*
- *"First cow always goes at stalls[0] — start cows=1, not 0."*
