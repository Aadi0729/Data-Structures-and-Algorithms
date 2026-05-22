# Minimize Maximum Distance to Gas Station — Interview Style ⛽
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize (Decimal)
> **Difficulty:** Hard
> **Platform:** GFG / Leetcode #774

---

## Problem Statement

Given sorted array `stations[]` of gas station positions and integer `k`:
- Add `k` more gas stations anywhere
- **Minimize** maximum distance between adjacent stations
- Return answer with 10^-6 precision

```
stations=[1,2,3,4,5,6,7,8,9,10], k=9  → Output: 0.500000
stations=[23,24,36,39,46,56,57,65,84,98], k=1 → Output: 14.000000
```

---

## KEY DIFFERENCE From All Previous Problems 🎯

```
Previous problems:        This problem:
──────────────────────────────────────────
Answer is INTEGER    →    Answer is DECIMAL
Discrete search      →    Continuous search
while(low<=high)     →    fixed 100 iterations
mid = int formula    →    mid = (low+high)/2.0
high=mid-1/low=mid+1 →    high=mid / low=mid
```

---

## Search Space

```
low  = 0
     → minimum possible distance (infinite stations added)
     → answer CAN be less than 1 (e.g. 0.5)!

high = max gap between adjacent stations
     → worst case — no stations added
     → answer never exceeds this!
```

---

## New Stations Formula 🔥

```
To split gap into parts each ≤ distance d:
new stations needed = ceil(gap/d) - 1

gap=9, d=3: ceil(9/3)-1 = 3-1 = 2 ✅
gap=9, d=4: ceil(9/4)-1 = 3-1 = 2 ✅
gap=9, d=9: ceil(9/9)-1 = 1-1 = 0 ✅
```

---

## Why Fixed 100 Iterations? 🎯

```
Need precision: 10^-6
Max gap: up to 10^9

Minimum iterations needed:
log2(10^9 / 10^-6) = log2(10^15) ≈ 50

Use 100 for safety:
→ precision = 10^9/2^100 ≈ 10^-21 ✅

Why NOT while(low<=high)?
→ Floating point comparison unreliable!
→ Loop might never terminate!
→ Fixed iterations always safe!
```

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& stations, int k, double distance) {
        int count = 0;
        for(int i = 1; i < stations.size(); i++) {
            double gap = stations[i] - stations[i-1];
            count += (int)ceil(gap / distance) - 1;
        }
        return count <= k;
    }

    double minMaxDist(vector<int>& stations, int k) {
        double low  = 0;
        double high = 0;

        for(int i = 1; i < stations.size(); i++) {
            high = max(high, (double)(stations[i] - stations[i-1]));
        }

        for(int iter = 0; iter < 100; iter++) {
            double mid = (low + high) / 2.0;

            if(isPossible(stations, k, mid))
                high = mid;    // minimize → reduce upper bound
            else
                low  = mid;    // too small → increase lower bound
        }
        return high;
    }
};
```

---

## Integer BS vs Decimal BS 🔥

| | Integer BS | Decimal BS |
|---|---|---|
| Answer type | int | double |
| Loop | `while(low<=high)` | `for(iter<100)` |
| mid | `low+(high-low)/2` | `(low+high)/2.0` |
| When TRUE | `high=mid-1` | `high=mid` |
| When FALSE | `low=mid+1` | `low=mid` |

---

## Complexity

```
TC : O(n × 100) = O(n)
SC : O(1)
```

---

## Common Mistakes ⚠️

```
1. while(low<=high) → infinite loop for decimals!
2. int distance → truncates decimals!
3. low=1 → answer can be < 1!
4. high=max(stations) → should be max GAP!
5. < 50 iterations → insufficient precision!
```

---

## Key Takeaways 🔥

- *"Decimal answer → fixed 100 iterations, never while loop!"*
- *"high = max gap — not max position!"*
- *"new stations = ceil(gap/distance) - 1"*
- *"low=0 — answer can be less than 1!"*
- *"50 iterations minimum for 10^-6 — use 100 for safety!"*
