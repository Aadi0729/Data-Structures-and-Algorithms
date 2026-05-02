# Ship Packages Within D Days 📦

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Medium
> **Leetcode:** #1011

---

## Problem Statement

Given an integer array `weights` and integer `days`:
- Ship all packages in **given order** within `days` days
- Each day load packages until capacity is exceeded
- Return **minimum weight capacity** of ship to ship all packages within `days` days

**Example:**
```
weights = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], days = 5
Output: 15
```

---

## Key Insight — Two Extreme Cases

```
capacity = max(weights) → maximum days needed (one package per day minimum)
capacity = sum(weights) → only 1 day needed (load everything at once)
```

> As capacity increases → days needed decreases → easier to ship on time.

---

## Why Binary Search Works Here?

As capacity increases → shipping becomes easier:

```
capacity:  10    15    20    30    55
works?:    ❌    ✅    ✅    ✅    ✅
```

**Monotonic pattern: FALSE → TRUE**
- Once a capacity works → all higher capacities also work ✅
- Once a capacity fails → all lower capacities also fail ❌

> 🔥 This monotonic behavior = Binary Search applicable!

---

## Search Space — NEW CONCEPT 🔥

> **For the first time — `low ≠ 1`!**

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(weights)` | Capacity less than heaviest package → can never load it |
| `high` | `sum(weights)` | Load everything in 1 day → no point going higher |
| `ans` | `high` | Always valid — gets minimized during search |

```
weights = [1,2,3,4,5,6,7,8,9,10]
low  = max = 10
high = sum = 55
```

> 🔥 **Rule:** *"low = can't go below this or problem breaks. high = no point going above this."*

---

## isPossible() Logic

> Given capacity `mid` — can we ship all packages within `days` days?

**Walk array left to right, accumulate load:**

```
currentLoad += weights[i]
if currentLoad > capacity:
    → start new day (day_count++)
    → reset currentLoad = weights[i]  ← package goes to new day!
after loop:
    → day_count++  ← count the last day!
return day_count <= days
```

**⚠️ Critical:** Packages must be loaded **in order** — you cannot skip or rearrange!

---

## Dry Run

```
weights = [1,2,3,4,5,6,7,8,9,10], capacity=15, days=5
```

| Package | currentLoad | day_count |
|---|---|---|
| 1 | 1 | 0 |
| 2 | 3 | 0 |
| 3 | 6 | 0 |
| 4 | 10 | 0 |
| 5 | 15 | 0 |
| 6 | 21>15 → new day! reset=6 | 1 |
| 7 | 13 | 1 |
| 8 | 21>15 → new day! reset=8 | 2 |
| 9 | 17>15 → new day! reset=9 | 3 |
| 10 | 19>15 → new day! reset=10 | 4 |

After loop → `day_count++ = 5`
`5 <= 5` → ✅ **capacity 15 works!**

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& weights, int days, int capacity) {
        int currentLoad = 0;
        int day_count   = 0;

        for (int i = 0; i < weights.size(); i++) {
            currentLoad += weights[i];

            if (currentLoad > capacity) {
                day_count++;                  // start new day
                currentLoad = weights[i];     // current package goes to new day
            }
        }
        day_count++;                          // count the last day!
        return day_count <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int low  = *max_element(weights.begin(), weights.end());
        int high = 0;
        for (auto val : weights)
            high += val;                      // actual sum — never use n*(n+1)/2!

        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(weights, days, mid)) {
                ans  = mid;
                high = mid - 1;               // minimize → go left
            } else {
                low  = mid + 1;               // too small → go right
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
| Time | O(n log s) — log s iterations × O(n) for isPossible |
| Space | O(1) — no extra space used |

Where `n` = size of weights, `s` = sum(weights)

---

## Common Mistakes ⚠️

```cpp
// ❌ Wrong sum formula — only works for [1,2,3...n]
int high = n * (n + 1) / 2;

// ✅ Always sum the actual array
int high = 0;
for (auto val : weights) high += val;

// ❌ Forgetting to count last day
return day_count <= days;  // last day never counted!

// ✅ Always increment after loop
day_count++;
return day_count <= days;

// ❌ Resetting currentLoad to 0 on new day
currentLoad = 0;  // loses current package!

// ✅ Reset to current package weight
currentLoad = weights[i];  // current package goes to new day
```

---

## Pattern Comparison So Far 🔥

| Problem | low | high | Pattern |
|---|---|---|---|
| Square Root | `1` | `n` | Maximize |
| Koko Bananas | `1` | `max(piles)` | Minimize |
| Min Days Bouquets | `1` | `max(bloomDay)` | Minimize |
| **Ship Packages** | **`max(weights)`** | **`sum(weights)`** | **Minimize** |

---

## Key Takeaways 🔥

- *"low doesn't have to be 1 — always derive from problem constraints."*
- *"low = minimum capacity that makes physical sense."*
- *"high = maximum capacity beyond which waiting is pointless."*
- *"Always count the last day after the loop — easiest bug to miss."*
- *"When capacity exceeded → new day starts, current package goes with it."*
- *"Never use n*(n+1)/2 formula blindly — always sum actual array."*
