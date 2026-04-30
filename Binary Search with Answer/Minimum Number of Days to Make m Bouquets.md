# Minimum Days to Make Bouquets 🌸

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #1482

---

## Problem Statement

Given an integer array `bloomDay`, integers `m` and `k`:
- `bloomDay[i]` = day on which `i`th flower blooms
- Make `m` bouquets, each needing `k` **adjacent** bloomed flowers
- Return **minimum number of days** to make `m` bouquets
- Return `-1` if impossible

**Example:**
```
bloomDay = [1, 10, 3, 10, 2], m = 3, k = 1
Output: 3
```

---

## Key Insight — What does "day X" mean?

> On day X → all flowers where `bloomDay[i] <= X` have bloomed.

```
bloomDay = [1, 10, 3, 10, 2]
day = 3:

index    :  0   1   2   3   4
bloomDay : [1, 10,  3, 10,  2]
bloomed? : ✅  ❌  ✅  ❌  ✅
           (1≤3)(10>3)(3≤3)(10>3)(2≤3)
```

---

## Brute Force Thinking

```
Try every day from 1 to max(bloomDay):
  → check if we can make m bouquets on that day
  → return first day that works
Time: O(n × max(bloomDay)) — too slow!
```

---

## Why Binary Search Works Here?

As days increase → more flowers bloom → easier to make bouquets.

```
day:    1    2    3    4  ....  10
works?: ❌   ❌   ✅   ✅  ....  ✅
```

**Monotonic pattern: FALSE → TRUE**
- Once a day works → all later days also work ✅
- Once a day fails → all earlier days also fail ❌

> 🔥 This monotonic behavior = Binary Search applicable!

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `1` | Minimum meaningful day |
| `high` | `max(bloomDay)` | Last flower blooms here — no point waiting longer |
| `ans` | `-1` | Default if impossible |

---

## Edge Case — Impossible Check

```cpp
if ((long long)m * k > bloomDay.size())
    return -1;
```

> If total flowers needed (m × k) exceeds total flowers available → **impossible no matter how many days we wait.**

⚠️ Cast to `long long` — `m * k` can overflow `int`!

---

## isPossible() Logic

> Given day `mid` — can we make `m` bouquets of `k` adjacent flowers?

**Walk the array left to right:**

```
✅ bloomed     → count++
count == k     → bouquet++, count = 0   ← made one bouquet!
❌ not bloomed → count = 0              ← adjacency broken → reset!
end            → return bouquet >= m
```

**Dry Run:** `bloomDay = [1,10,3,10,2]`, day=3, k=1, m=3

| Index | bloomDay[i] | Bloomed? | Count | Bouquets |
|---|---|---|---|---|
| 0 | 1 | ✅ (1≤3) | 1→bouquet! → 0 | 1 |
| 1 | 10 | ❌ (10>3) | 0 | 1 |
| 2 | 3 | ✅ (3≤3) | 1→bouquet! → 0 | 2 |
| 3 | 10 | ❌ (10>3) | 0 | 2 |
| 4 | 2 | ✅ (2≤3) | 1→bouquet! → 0 | 3 |

`bouquets = 3 >= m = 3` → ✅ **day 3 works!**

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& bloomDay, long long m, long long k, int mid) {
        int count   = 0;
        int bouquet = 0;

        for (int i = 0; i < bloomDay.size(); i++) {
            if (bloomDay[i] <= mid) {
                count++;                 // flower bloomed → count adjacent
                if (count == k) {        // k adjacent found → one bouquet!
                    bouquet++;
                    count = 0;           // reset for next bouquet
                }
            } else {
                count = 0;               // adjacency broken → reset
            }
        }
        return bouquet >= m;
    }

    int minDays(vector<int>& bloomDay, long long m, long long k) {
        // Edge case — impossible
        if (m * k > (long long)bloomDay.size()) return -1;

        int low  = 1;
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        int ans  = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(bloomDay, m, k, mid)) {
                ans  = mid;
                high = mid - 1;          // minimize → go left
            } else {
                low  = mid + 1;          // too early → go right
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
| Time | O(n log d) — log d iterations × O(n) for isPossible |
| Space | O(1) — no extra space used |

Where `n` = size of bloomDay, `d` = max(bloomDay)

---

## Common Mistakes ⚠️

```cpp
// ❌ Integer overflow in edge case check
if (m * k > bloomDay.size())   // m*k overflows int!

// ✅ Cast to long long
if ((long long)m * k > bloomDay.size())

// ❌ Decrementing count on non-bloomed flower
count--;   // WRONG — adjacency is fully broken!

// ✅ Reset completely
count = 0;

// ❌ Missing curly braces — silent bug!
if (count == k)
    bouquet++;
    count = 0;    // runs always!

// ✅ Always use braces
if (count == k) {
    bouquet++;
    count = 0;
}
```

---

## Key Takeaways 🔥

- *"On day X → flowers where bloomDay[i] <= X have bloomed."*
- *"Adjacency breaks on non-bloomed flower → reset count to 0, not decrement."*
- *"Always check m*k > n impossibility before binary search."*
- *"Overflow hides in multiplication checks — always cast to long long."*
- *"Default ans = -1 handles the impossible case automatically."*
