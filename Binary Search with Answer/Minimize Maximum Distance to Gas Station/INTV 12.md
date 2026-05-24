# Minimize Maximum Distance to Gas Station — All Approaches ⛽
## Brute Force → Better → Optimal

> **Pattern:** Simulation → Greedy + PQ → Binary Search on Answer
> **Difficulty:** Hard
> **Platform:** GFG / Leetcode #774

---

## Problem Statement

Given sorted array `stations[]` of gas station positions and integer `k`:
- Add `k` more gas stations anywhere on highway
- **Minimize** maximum distance between adjacent stations
- Return answer with 10^-6 precision

```
stations=[1,2,3,4,5,6,7,8,9,10], k=9  → Output: 0.500000
stations=[23,24,36,39,46,56,57,65,84,98], k=1 → Output: 14.000000
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of station positions?
2. What is the range of k?
3. Is array always sorted?
4. What precision is needed?
5. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ stations[i] ≤ 10^9
→ 1 ≤ k ≤ 10^6
→ Yes — always sorted
→ 10^-6 precision needed
→ Yes, start from brute force
```

---

## Key Insight — Section Length 🎯

```
When we place 'p' new stations in a gap:
gap is divided into (p+1) equal sections

section length = gap / (p+1)

Example:
gap = 9, p = 2 new stations:
section length = 9/(2+1) = 3

[1 ... 4 ... 7 ... 10]
    3     3     3    ✅
```

---

## APPROACH 1 — Brute Force (Simulation)

### Intuition:
```
Place one station at a time.
Each time → place in the section with maximum length.
After placing all k stations → find max section length.
```

### Key Observation:
```
For gap i with 'p' stations placed:
current section length = (stations[i+1]-stations[i]) / (p+1)

Always place next station in section with MAX current length!
This is GREEDY — always reduces the maximum!
```

### Code:
```cpp
class Solution {
public:
    double minMaxDist(vector<int>& stations, int K) {
        int n = stations.size();
        vector<int> gasStationsPlaced(n-1, 0);  // stations placed in each gap

        // Place k stations one by one
        for(int gasStations = 1; gasStations <= K; gasStations++) {
            long double maxSecLen = -1;
            int maxIndex = -1;

            // Find gap with maximum section length
            for(int i = 0; i < n-1; i++) {
                long double diff    = stations[i+1] - stations[i];
                long double secLen  = diff / (long double)(gasStationsPlaced[i] + 1);

                if(secLen > maxSecLen) {
                    maxSecLen = secLen;
                    maxIndex  = i;
                }
            }
            gasStationsPlaced[maxIndex]++;  // place station in max gap
        }

        // Find final maximum section length
        long double minMaxDistance = -1;
        for(int i = 0; i < n-1; i++) {
            long double diff   = stations[i+1] - stations[i];
            long double secLen = diff / (long double)(gasStationsPlaced[i] + 1);
            minMaxDistance = max(minMaxDistance, secLen);
        }

        return minMaxDistance;
    }
};
```

### Complexity:
```
TC : O(K × N)
     → K iterations of placing stations
     → each iteration → O(N) to find max gap

SC : O(N)
     → gasStationsPlaced array of size N-1
```

### Bottleneck:
```
For K=10^6, N=10^5:
→ 10^6 × 10^5 = 10^11 operations 😬
Way too slow!

Bottleneck: finding max gap takes O(N) every iteration.
Can we find max gap faster? → Priority Queue!
```

---

## APPROACH 2 — Better (Priority Queue / Max Heap)

### Intuition:
```
Bottleneck in brute force = finding max gap in O(N).
Use a MAX HEAP to always get max section in O(log N)!
```

### Key Insight:
```
Store {section_length, gap_index} in max heap.
Each time:
→ pop max section
→ add 1 station to that gap
→ recalculate section length
→ push back to heap

After k stations → top of heap = answer!
```

### Code:
```cpp
class Solution {
public:
    double minMaxDist(vector<int>& stations, int K) {
        int n = stations.size();
        vector<int> gasStationsPlaced(n-1, 0);

        // Max heap: {section_length, gap_index}
        priority_queue<pair<long double, int>> pq;

        // Initialize with original gaps
        for(int i = 0; i < n-1; i++) {
            pq.push({stations[i+1] - stations[i], i});
        }

        // Place k stations
        for(int gasStations = 1; gasStations <= K; gasStations++) {
            auto top     = pq.top();
            pq.pop();

            int secIndex = top.second;
            gasStationsPlaced[secIndex]++;

            // Recalculate section length for this gap
            long double diff   = stations[secIndex+1] - stations[secIndex];
            long double secLen = diff / (long double)(gasStationsPlaced[secIndex] + 1);

            pq.push({secLen, secIndex});
        }

        // Answer = top of heap after placing all stations
        return pq.top().first;
    }
};
```

### Complexity:
```
TC : O(N log N + K log N)
     → N log N to initialize heap
     → K log N for k insertions/deletions

SC : O(N)
     → priority queue of size N-1
     → gasStationsPlaced array of size N-1
```

### Why Not Good Enough?
```
For K=10^6, N=10^5:
TC → 10^6 × log(10^5) ≈ 1.7×10^7 ✅ (TC improved!)
SC → O(N) ❌ (still needs extra space)

TC improved significantly!
But SC still O(N).
Can we do O(1) space? → Binary Search on Answer!
```

---

## APPROACH 3 — Optimal (Binary Search on Answer)

### Key Insight:
```
Instead of simulating placement —
ask: "Is it POSSIBLE to achieve max distance ≤ mid
      using at most k stations?"

This is isPossible(mid) — Binary Search on Answer!
```

### New Stations Formula:
```
To split gap into parts each ≤ distance d:
parts needed    = ceil(gap/d)
new stations    = ceil(gap/d) - 1

gap=9, d=3: ceil(9/3)-1 = 3-1 = 2
gap=9, d=4: ceil(9/4)-1 = 3-1 = 2
gap=9, d=9: ceil(9/9)-1 = 1-1 = 0
```

### Monotonic Pattern:
```
distance:  0.5   1.0   2.0   3.0   4.0   5.0
works?:    ❌    ❌    ❌    ✅    ✅    ✅

FALSE → TRUE pattern → Minimize → Binary Search!
```

### Search Space:
```
low  = 0
     → minimum possible (infinite stations)
     → answer CAN be < 1 (like 0.5)!

high = max gap between adjacent stations
     → worst case with no stations added
```

### Termination Condition:
```
while(high - low > 1e-6)  ← BETTER than fixed iterations!

Why better?
→ Stops EXACTLY when precision reached
→ More mathematically precise
→ Doesn't waste iterations

vs fixed 100 iterations:
→ Always runs 100 times regardless of precision needed
→ Less elegant
```

### Code:
```cpp
class Solution {
public:
    bool canPlaceStations(vector<int>& stations, int K, long double distance) {
        int count = 0;
        for(int i = 0; i < stations.size()-1; i++) {
            long double diff = stations[i+1] - stations[i];
            count += (int)ceil(diff / distance) - 1;
        }
        return count <= K;
    }

    double minMaxDist(vector<int>& stations, int K) {
        long double low  = 0;
        long double high = 0;

        // high = max gap between adjacent stations
        for(int i = 0; i < stations.size()-1; i++) {
            high = max(high, (long double)(stations[i+1] - stations[i]));
        }

        long double precision = 1e-6;

        // Decimal binary search — stop when precision reached!
        while(high - low > precision) {
            long double mid = low + (high - low) / 2.0;

            if(canPlaceStations(stations, K, mid))
                high = mid;    // minimize → reduce upper bound
            else
                low  = mid;    // too small → increase lower bound
        }
        return high;
    }
};
```

### Complexity:
```
TC : O(N × log(range/ε))
     → log(range/ε) iterations of BS
     → range = max_gap ≤ 10^9
     → ε = 10^-6
     → log(10^9/10^-6) = log(10^15) ≈ 50 iterations
     → each iteration → O(N)
     → total: O(50N) = O(N log(range/ε))

SC : O(1) — no extra space! ✅
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | Notes |
|---|---|---|---|
| Brute Force | O(K×N) | O(N) | Simulation — too slow! |
| Priority Queue | O(KlogN + NlogN) | O(N) | Fast but needs space |
| **BS on Answer** | **O(N log(range/ε))** | **O(1)** | **Best both TC and SC!** |

### Numerical Comparison (K=10^6, N=10^5):
```
Brute Force : 10^6 × 10^5 = 10^11 ❌
Priority Queue: 10^6 × 17 ≈ 1.7×10^7 ✅
BS on Answer: 10^5 × 50 = 5×10^6 ✅✅
```

> 🔥 BS on Answer wins on BOTH TC and SC!

---

## Integer BS vs Decimal BS 🔥

| | Integer BS | Decimal BS |
|---|---|---|
| Answer type | int | double/long double |
| Loop | `while(low<=high)` | `while(high-low>1e-6)` |
| mid | `low+(high-low)/2` | `low+(high-low)/2.0` |
| When TRUE | `high=mid-1` | `high=mid` |
| When FALSE | `low=mid+1` | `low=mid` |
| Termination | `low>high` | `high-low≤precision` |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Range of stations and k?
 Precision needed?
 Array always sorted?
 [get answers]"

STEP 2 — BRUTE FORCE:
"Place one station at a time in max gap.
 Find max gap in O(N) each time.
 TC: O(K×N), SC: O(N). Too slow!"

STEP 3 — BETTER (PQ):
"Use max heap to find max gap in O(logN).
 TC: O(KlogN + NlogN), SC: O(N).
 TC improved but SC still O(N)!"

STEP 4 — OPTIMAL (BS):
"Instead of simulating —
 ask: can we achieve distance ≤ mid with k stations?
 FALSE→TRUE monotonic pattern!
 while(high-low > 1e-6) for decimal precision.
 TC: O(N log(range/ε)), SC: O(1). Best!"

STEP 5 — EDGE CASES:
"low=0 — answer can be < 1 ✅
 high=max gap — not max position ✅
 ceil(gap/distance)-1 for new stations ✅
 while(high-low>1e-6) better than fixed iterations ✅"
```

---

## Common Mistakes in Interviews ⚠️

```
1. Brute force: not resetting maxSecLen each iteration
2. PQ: forgetting to recalculate section length after placing
3. BS: low=1 instead of 0 → misses answers < 1!
4. BS: high=max(stations) → should be max GAP!
5. BS: using int instead of long double → precision loss
6. BS: fixed iterations instead of while(high-low>precision)
7. Formula: gap/distance instead of ceil(gap/distance)-1
```

---

## Key Takeaways 🔥

- *"Three approaches: simulation → greedy+PQ → BS on Answer."*
- *"section length = gap/(stations_placed+1)"*
- *"new stations needed = ceil(gap/distance) - 1"*
- *"while(high-low>1e-6) more elegant than fixed 100 iterations!"*
- *"BS on Answer wins on both TC AND SC over Priority Queue!"*
- *"low=0 — answer can be less than 1!"*
- *"high = max GAP — not max station position!"*
