# Binary Search on Answer 🔍

> **Core Idea:** Not about finding a key in an array — it's about finding the boundary where a condition flips from TRUE to FALSE (or FALSE to TRUE).

---

## When to Use This Pattern?

Ask yourself these 3 questions:
1. Am I asked to **minimize or maximize** some value?
2. Does the answer lie in a **definable numeric range**?
3. Is there a **monotonic condition** — if X works, do all values before/after X also work?

If all 3 → **Binary Search on Answer.**

---

## Classic BS vs BS on Answer

| | Classic Binary Search | Binary Search on Answer |
|---|---|---|
| Input | Sorted array | Any problem |
| Search space | The array itself | Range YOU define |
| Question | `arr[mid] == key?` | `isPossible(mid)?` |

---

## Two Monotonic Patterns

```
Case 1 — Maximize (last TRUE):
✅ ✅ ✅ ✅ ❌ ❌ ❌
           ↑
      answer here

Case 2 — Minimize (first TRUE):
❌ ❌ ❌ ✅ ✅ ✅ ✅
        ↑
   answer here
```

---

## Universal Template (C++)

```cpp
int binarySearchOnAnswer(vector<int>& input) {
    int low  = minimum_possible_answer;
    int high = maximum_possible_answer;
    int ans  = low; // or high, depending on problem

    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoids overflow

        if (isPossible(mid)) {
            ans  = mid;
            high = mid - 1;  // minimize → go left
            // low = mid + 1 → maximize → go right
        } else {
            low  = mid + 1;  // minimize
            // high = mid - 1 → maximize
        }
    }
    return ans;
}
```

> **Maximize:** when TRUE → `ans = mid, low = mid + 1`
> **Minimize:** when TRUE → `ans = mid, high = mid - 1`

---

## Ceiling Division Trick

```cpp
// ceil(a / b) without math library
int result = (a + b - 1) / b;

// Why b-1?
// → Adding less: some fractions don't round up correctly ❌
// → Adding more: exact divisions get pushed up wrongly ❌
// → b-1 is the tightest value that rounds up fractions
//   while keeping exact divisions unchanged ✅
```

---

## Common Mistakes ⚠️

```cpp
// ❌ Integer overflow in isPossible()
int totalHours = 0;  // overflows for large inputs

// ✅ Always use long long for accumulation
long long totalHours = 0;

// ❌ Passing vector by value (makes unnecessary copy)
bool isPossible(vector<int> piles, int h, int mid)

// ✅ Pass by const reference
bool isPossible(vector<int>& piles, int h, int mid)

// ❌ Wrong loop condition
while (low < high)   // misses last valid value

// ✅ Always use <=
while (low <= high)
```

---

## Problems Solved

### 1. Square Root of N
```
Search space : [1, n]
isPossible   : mid * mid <= n
Pattern      : Maximize → last TRUE
Complexity   : O(log n)
```
```cpp
int mySqrt(int n) {
    int low = 1, high = n, ans = 1;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (mid * mid <= n) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}
```

---

### 2. Koko Eating Bananas
```
Search space : [1, max(piles)]
isPossible   : totalHours <= h
Pattern      : Minimize → first TRUE
Complexity   : O(n log m) where m = max(piles)
```
```cpp
bool isPossible(vector<int>& piles, int h, int mid) {
    long long totalHours = 0;
    for (int i = 0; i < piles.size(); i++) {
        totalHours += (piles[i] + mid - 1) / mid;
    }
    return totalHours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int low  = 1;
    int high = *max_element(piles.begin(), piles.end());
    int ans  = 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(piles, h, mid)) {
            ans  = mid;
            high = mid - 1;
        } else {
            low  = mid + 1;
        }
    }
    return ans;
}
```

---

## Problem Roadmap

| # | Problem | Pattern | Search Space |
|---|---|---|---|
| 1 | Square Root of N | Maximize | `[1, n]` |
| 2 | Koko Eating Bananas | Minimize | `[1, max(piles)]` |
| 3 | Min Days to Make Bouquets | Minimize | `[1, max(bloomDay)]` |
| 4 | Ship Packages in D Days | Minimize | `[max(weights), sum(weights)]` |
| 5 | Aggressive Cows | Maximize | `[1, max(stalls)]` |
| 6 | Book Allocation | Minimize | `[max(arr), sum(arr)]` |
| 7 | Split Array Largest Sum | Minimize | `[max(arr), sum(arr)]` |

---

## One-Liners to Remember 🔥

- *"Binary Search on Answer is not about finding a key — it's about finding the boundary where a condition flips."*
- *"In classic BS, the array is given. In BS on Answer, YOU create the search space."*
- *"Monotonic = once FALSE always FALSE, once TRUE always TRUE — that's why binary search works."*
- *"The search space is the range of possible ANSWERS, not the input array."*
- *"isPossible() uses the input array. Binary search runs on the answer space."*
- *"Always use long long when accumulating sums in isPossible()."*
- *"`(n + k - 1) / k` — ceiling division trick every competitive programmer must know."*
