# Book Allocation — Interview Style 📚
## Brute Force → Optimal

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Hard
> **Platform:** GFG / Striver SDE Sheet

---

## Problem Statement

Given array `books[]` where `books[i]` = pages in ith book, integer `k` (students):
- Each student gets **at least one book**
- Books allocated **contiguously** only
- Return **minimum of maximum pages** assigned to a student
- Return `-1` if impossible

```
books=[12,34,67,90], k=2 → Output: 113
books=[15,17,20], k=5    → Output: -1 (impossible!)
```

---

## Clarifying Questions to Ask Interviewer

```
1. What is the range of books[i] and k?
2. What if k > books.size()? Return -1?
3. Can books be rearranged? (CRITICAL!)
4. Can books array be empty?
5. What is length range of books array?
6. Should I start from brute force?
```

**Interviewer Answers:**
```
→ 1 ≤ books[i] ≤ 10^9
→ 1 ≤ k ≤ 10^5
→ k > books.size() → return -1 (impossible!)
→ Books CANNOT be rearranged — contiguous only!
→ books always non-empty (1 ≤ books.size() ≤ 10^5)
→ Yes, start from brute force
```

> 🔥 **Key constraint:** Books CANNOT be rearranged!
> This is the constraint that makes isPossible() work
> exactly like Ship Packages!

---

## Pattern Recognition — The KEY Insight 🔥

> This problem is **structurally identical** to Ship Packages!

```
Ship Packages:          Book Allocation:
────────────────────────────────────────
weights[] array    →    books[] array
days               →    k students
capacity per day   →    pages per student
ship in ORDER      →    allocate CONTIGUOUS
minimize capacity  →    minimize max pages
low = max(weights) →    low = max(books)
high = sum(weights)→    high = sum(books)
```

> Only difference:
> Book Allocation has impossible case → k > books.size() → -1!

---

## Why k > books.size() is Impossible?

```
books = [10, 20, 30], k = 5 students
3 books, 5 students → 2 students get nothing ❌
Each student MUST get at least 1 book!
→ return -1
```

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(books)` | Largest book must go to someone — can't go below |
| `high` | `sum(books)` | One student reads everything — no point going higher |
| `ans` | `-1` | Default — updated when canGetPages() is true |

---

## Why students needed <= k? 🎯

```
At MINIMUM pages limit:
→ Students are maximally utilized
→ Each student gets at least 1 book automatically!

At pages limit = sum(books):
→ 1 student reads everything → technically works
→ BUT binary search returns MINIMUM limit
→ At minimum → students needed ≈ k → each gets books ✅

Edge case k > books.size() handled separately → -1
```

> 🔥 *"Binary search finds MINIMUM pages limit.
>      At minimum — students maximally utilized —
>      each gets at least 1 book automatically!"*

---

## APPROACH 1 — Brute Force

### Intuition:
```
Try every pages limit from max(books) to sum(books).
For each limit → count students needed.
First valid limit → minimum pages! Stop immediately.
```

### Code:
```cpp
class Solution {
public:
    bool canGetPages(vector<int>& arr, int k, int pages) {
        int students  = 0;
        int totalPage = 0;

        for(int i = 0; i < arr.size(); i++) {
            totalPage += arr[i];
            if(totalPage > pages) {
                students++;              // new student needed
                totalPage = arr[i];      // current book → new student
            }
        }
        students++;                      // count last student!
        return students <= k;            // students needed <= available?
    }

    int findPages(vector<int>& arr, int k) {
        if(k > (int)arr.size()) return -1;  // impossible!

        int maxPages   = *max_element(arr.begin(), arr.end());
        int totalPages = 0;
        for(auto val : arr) totalPages += val;

        int ans = totalPages;

        for(int i = maxPages; i <= totalPages; i++) {
            if(canGetPages(arr, k, i)) {
                ans = i;    // first valid = minimum!
                break;      // no need to check further
            }
        }
        return ans;
    }
};
```

### Complexity:
```
TC : O((sum-max) × n)
     → outer loop runs (sum-max) times
     → each iteration → canGetPages() → O(n)

SC : O(1) — no extra space
```

### Bottleneck:
```
For books=[10^9, 10^9...] (10^5 elements):
sum ≈ 10^14, max = 10^9
range ≈ 10^14 iterations × 10^5 = astronomical 😬
Way too slow!
```

---

## APPROACH 2 — Optimal (Binary Search on Answer)

### Key Observation:
```
Page limits follow FALSE→TRUE pattern:

pages:   max  ....  X  ....  sum
works?:  ❌   ....  ✅  ....  ✅

→ Larger limit → easier to fit books ✅
→ Smaller limit → harder to fit books ❌
→ Monotonic → Binary Search applicable!
First TRUE = minimum pages = answer!
```

### Monotonic Pattern:
```
❌ ❌ ❌ ✅ ✅ ✅ ✅
         ↑
    BOUNDARY
  (first TRUE = answer)

Pattern   : FALSE → TRUE
Goal      : Find FIRST TRUE
Type      : MINIMIZE
Direction : when TRUE  → ans=mid, high=mid-1 (go left)
            when FALSE → low=mid+1 (go right)
```

### Code:
```cpp
class Solution {
public:
    bool canGetPages(vector<int>& arr, int k, int pages) {
        int students  = 0;
        int totalPage = 0;

        for(int i = 0; i < arr.size(); i++) {
            totalPage += arr[i];
            if(totalPage > pages) {
                students++;
                totalPage = arr[i];
            }
        }
        students++;
        return students <= k;
    }

    int findPages(vector<int>& arr, int k) {
        if(k > (int)arr.size()) return -1;  // impossible!

        int low  = *max_element(arr.begin(), arr.end());
        int high = 0;
        for(auto val : arr) high += val;

        int ans = high;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canGetPages(arr, k, mid)) {
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
     → log s iterations of binary search
     → each iteration → canGetPages() → O(n)
     → total: O(n log s)
     where n = arr.size()
           s = sum - max = search space size

SC : O(1) — no extra space
```

### Dry Run (books=[12,34,67,90], k=2):
```
Edge check: 2 <= 4 → proceed
low=90, high=203, ans=203

Iter 1: mid=146
        12→46→113→203>146 → students=1, totalPage=90
        students++=2 → 2<=2 ✅ → ans=146, high=145

Iter 2: mid=117
        12→46→113→203>117 → students=1, totalPage=90
        students++=2 → 2<=2 ✅ → ans=117, high=116

Iter 3: mid=103
        12→46→113>103 → students=1, totalPage=67
        67→157>103 → students=2, totalPage=90
        students++=3 → 3>2 ❌ → low=104

Iter 4: mid=110
        12→46→113>110 → students=1, totalPage=67
        67→157>110 → students=2, totalPage=90
        students++=3 → 3>2 ❌ → low=111

Iter 5: mid=113
        12→46→113<=113 ✅
        113→203>113 → students=1, totalPage=90
        students++=2 → 2<=2 ✅ → ans=113, high=112

low=113 > high=112 → STOP
return 113 ✅
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
"Range of books[i] and k?
 What if k > books.size()?
 Can books be rearranged?
 [get answers]
 Books CANNOT be rearranged — contiguous only!"

STEP 2 — PATTERN RECOGNITION:
"I notice this is structurally identical
 to Ship Packages in D Days!
 Same search space [max, sum].
 Same isPossible() logic.
 Only difference: impossible case k > n → -1!"

STEP 3 — BRUTE FORCE:
"Try every pages limit from max to sum.
 Count students needed for each limit.
 First valid → minimum! Break.
 TC: O((sum-max) × n), SC: O(1). Too slow!"

STEP 4 — OPTIMAL:
"Page limits follow FALSE→TRUE pattern.
 Binary Search applicable!
 low=max(books), high=sum(books)
 canGetPages() stays exactly same!
 Minimize → high=mid-1 when TRUE.
 TC: O(n log s), SC: O(1)"

STEP 5 — EDGE CASES:
"k > books.size() → return -1 ✅
 students++ after loop → count last ✅
 Reset to arr[i] not 0 → current book kept ✅"
```

---

## Common Mistakes in Interviews ⚠️

```
1. Missing edge case k > books.size() → return -1
2. return students >= k → WRONG! should be students <= k
3. Forgetting students++ after loop → last student missed!
4. Resetting totalPage=0 → current book lost! → use arr[i]
5. Not connecting to Ship Packages → missed pattern recognition!
6. Wrong direction → low=mid+1 when TRUE → that's maximize!
```

---

## Key Takeaways 🔥

- *"Book Allocation = Ship Packages — same soul, different story!"*
- *"k > books.size() → impossible → return -1 immediately."*
- *"students needed <= k → possible. Not >=!"*
- *"Binary search finds minimum → students maximally utilized → each gets books!"*
- *"Pattern recognition = highest interview skill — mention the connection!"*
- *"canGetPages() identical in brute force and optimal — only loop changes!"*
