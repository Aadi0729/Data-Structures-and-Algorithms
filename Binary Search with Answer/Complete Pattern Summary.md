# Binary Search on Answer — Complete Pattern Summary 🔍

> The master reference for the entire pattern.

---

## The One-Line Definition

> *"Binary Search on Answer is not about finding a key in an array — it's about finding the boundary where a condition flips from TRUE to FALSE (or FALSE to TRUE)."*

---

## Classic BS vs BS on Answer

| | Classic Binary Search | Binary Search on Answer |
|---|---|---|
| Input | Sorted array | Any problem |
| Search space | The array itself | Range YOU define |
| Question | `arr[mid] == key?` | `isPossible(mid)?` |
| Example | Find 7 in [1,3,5,7,9] | Find minimum speed for Koko |

> 🔥 *"In classic BS, array is given. In BS on Answer, YOU create the search space."*

---

## 3 Signals That Scream BS on Answer

```
1. Asked to MINIMIZE or MAXIMIZE some value
2. Answer lies in a definable NUMERIC RANGE
3. There exists a MONOTONIC condition:
   → if X works, all values before/after X also work
```

---

## Two Monotonic Patterns

```
Maximize (Last TRUE):           Minimize (First TRUE):
✅ ✅ ✅ ✅ ❌ ❌ ❌             ❌ ❌ ❌ ✅ ✅ ✅ ✅
           ↑                              ↑
     answer here                    answer here
```

---

## Universal Template (C++)

```cpp
int binarySearchOnAnswer(vector<int>& input) {
    int low  = minimum_possible_answer;   // derived from constraints
    int high = maximum_possible_answer;   // derived from constraints
    int ans  = high;                      // or -1 if impossible case exists

    while (low <= high) {
        int mid = low + (high - low) / 2; // never (low+high)/2 → overflow!

        if (isPossible(mid)) {
            ans  = mid;
            high = mid - 1;  // MINIMIZE → go left (first TRUE)
            // low = mid + 1 → MAXIMIZE → go right (last TRUE)
        } else {
            low  = mid + 1;  // MINIMIZE → too small, go right
            // high = mid - 1 → MAXIMIZE → too large, go left
        }
    }
    return ans;
}
```

---

## Minimize vs Maximize — Once and For All

| | When TRUE | When FALSE | Hunting For |
|---|---|---|---|
| **Minimize** | `ans=mid, high=mid-1` | `low=mid+1` | First TRUE |
| **Maximize** | `ans=mid, low=mid+1` | `high=mid-1` | Last TRUE |

> 🔥 *"Minimize = go left when TRUE. Maximize = go right when TRUE."*

---

## How to Derive Search Space

```
low  = minimum value below which problem BREAKS
       → "below this, some element can never be handled"

high = maximum value beyond which answer is POINTLESS
       → "at this value, everything fits in 1 unit"
```

---

## Ceiling Division Trick

```cpp
// ceil(a / b) without math library
int result = (a + b - 1) / b;

// Why b-1?
// → b-1 is tightest value that:
//   rounds up non-exact divisions ✅
//   keeps exact divisions unchanged ✅
```

---

## Overflow Checklist for isPossible()

```cpp
// Always ask:
// 1. Accumulating sum in loop?          → long long
// 2. Multiplying two large numbers?     → long long cast
// 3. Comparing product with size/sum?   → long long cast

// Example:
long long totalHours = 0;              // accumulation
if ((long long)m * k > n) return -1;  // multiplication check
```

---

## Complete Problem Reference

### 1. Square Root of N
```
Type       : Maximize (last TRUE)
low        : 1
high       : n
isPossible : mid * mid <= n
Direction  : ans=mid, low=mid+1
Complexity : O(log n)
```

### 2. Koko Eating Bananas
```
Type       : Minimize (first TRUE)
low        : 1
high       : max(piles)
isPossible : ceil(pile/speed) sum <= h
Trick      : ceiling division (pile+speed-1)/speed
Direction  : ans=mid, high=mid-1
Complexity : O(n log m) where m=max(piles)
```

### 3. Minimum Days to Make Bouquets
```
Type       : Minimize (first TRUE)
low        : 1
high       : max(bloomDay)
isPossible : can make m bouquets of k adjacent bloomed flowers?
Edge case  : m*k > n → return -1
Direction  : ans=mid, high=mid-1
Complexity : O(n log d) where d=max(bloomDay)
Key        : reset count=0 when flower not bloomed (adjacency breaks)
```

### 4. Ship Packages in D Days
```
Type       : Minimize (first TRUE)
low        : max(weights)   ← NOT 1!
high       : sum(weights)
isPossible : can ship all packages in days days with capacity mid?
Direction  : ans=mid, high=mid-1
Complexity : O(n log s) where s=sum(weights)
Key        : always sum actual array — never use n*(n+1)/2 formula
```

### 5. Aggressive Cows
```
Type       : Maximize (last TRUE)
low        : 1
high       : max(stalls) - min(stalls)
isPossible : can place k cows with minimum distance mid?
Pre-step   : sort stalls first!
Direction  : ans=mid, low=mid+1
Complexity : O(n log n) sort + O(n log d)
Key        : track lastPlaced, not adjacent difference
             place first cow at stalls[0] → cows=1
```

### 6. Book Allocation
```
Type       : Minimize (first TRUE)
low        : max(books)     ← NOT 1!
high       : sum(books)
isPossible : can allocate books to k students with max pages mid?
Edge case  : k > n → return -1
Direction  : ans=mid, high=mid-1
Complexity : O(n log s) where s=sum(books)
```

### 7. Split Array Largest Sum
```
Type       : Minimize (first TRUE)
low        : max(nums)      ← NOT 1!
high       : sum(nums)
isPossible : can split into k subarrays with max sum mid?
Direction  : ans=mid, high=mid-1
Complexity : O(n log s) where s=sum(nums)
Note       : IDENTICAL to Book Allocation and Ship Packages!
```

---

## The Three Brothers 🔥

> Ship Packages = Book Allocation = Split Array
> Same soul — different story!

```
All three ask:
"Find minimum limit such that
 array can be divided into k parts
 without any part exceeding that limit"

isPossible() for all three:
→ Walk array, accumulate sum
→ When sum > limit → new bucket, reset sum
→ Count buckets needed
→ return buckets <= k
```

---

## Common Mistakes Master List ⚠️

```cpp
// 1. Integer overflow in loop accumulation
long long totalHours = 0;          // always long long for sums

// 2. Integer overflow in multiplication checks
if ((long long)m * k > n)          // cast before multiplying

// 3. Using wrong sum formula
int high = n*(n+1)/2;              // WRONG — only for [1..n]
for(auto v : arr) high += v;       // CORRECT — always sum actual array

// 4. Forgetting last bucket/day/student
subarrays++;                       // after loop — count last one!

// 5. Wrong reset on overflow
sum = 0;                           // WRONG — loses current element!
sum = arr[i];                      // CORRECT — current goes to new bucket

// 6. Missing curly braces
if(count == k) bouquets++;         // WRONG
    count = 0;                     // runs always!
if(count == k) { bouquets++; count = 0; }  // CORRECT

// 7. Comparing adjacent difference in Aggressive Cows
diff = stalls[i] - stalls[i-1];   // WRONG
diff = stalls[i] - lastPlaced;    // CORRECT

// 8. Forgetting to sort in Aggressive Cows
sort(stalls.begin(), stalls.end()); // ALWAYS sort first!

// 9. Wrong binary search direction
// Minimize → high=mid-1 when TRUE
// Maximize → low=mid+1 when TRUE

// 10. Wrong loop condition
while(low < high)                  // WRONG — misses last value
while(low <= high)                 // CORRECT
```

---

## One-Liners to Remember 🔥

- *"BS on Answer finds the boundary where condition flips — not a key in array."*
- *"Search space is range of POSSIBLE ANSWERS — not the input array."*
- *"Monotonic = once FALSE always FALSE, once TRUE always TRUE."*
- *"low = can't go below this or problem breaks."*
- *"high = no point going above this."*
- *"Minimize = go left when TRUE. Maximize = go right when TRUE."*
- *"isPossible() uses input array. Binary search runs on answer space."*
- *"`(n+k-1)/k` — ceiling division without math library."*
- *"Always long long when accumulating or multiplying large numbers."*
- *"Last bucket/day/student — always count after loop."*
- *"Ship Packages = Book Allocation = Split Array — same soul, different story."*
