# Book Allocation 📚

> **Pattern:** Binary Search on Answer — Minimize
> **Difficulty:** Hard
> **Platform:** GFG / Striver SDE Sheet

---

## Problem Statement

Given an array `books[]` where `books[i]` represents number of pages in `i`th book, and integer `k` (number of students):
- Each student gets **at least one book**
- Each student gets **contiguous books** only
- Return **minimum of the maximum pages** assigned to a student

**Example:**
```
books = [12, 34, 67, 90], k = 2
Output: 113  (split: [12,34,67] | [90])
```

---

## Key Insight — What Are We Minimizing?

```
Split 1: [12,34,67] | [90]
         113 pages    90 pages
         max = 113 ✅ (better!)

Split 2: [12,34] | [67,90]
         46 pages   157 pages
         max = 157 ❌ (worse!)
```

> We want to minimize the maximum pages any student has to read.

---

## Why Binary Search Works Here?

As max pages limit increases → easier to fit all books in k students:

```
maxPages:  90    100    113    150    203
works?:    ❌    ❌     ✅     ✅     ✅
```

**Monotonic pattern: FALSE → TRUE**
- Once a limit works → all higher limits also work ✅
- Once a limit fails → all lower limits also fail ❌

> 🔥 This monotonic behavior = Binary Search applicable!

---

## Search Space

| Bound | Value | Reason |
|---|---|---|
| `low` | `max(books)` | Largest book must go to someone — can't go below this |
| `high` | `sum(books)` | One student reads everything — no point going higher |
| `ans` | `-1` | Default — updated when isPossible() is true |

```
books = [12, 34, 67, 90]
low  = max = 90
high = sum = 203
```

---

## How to Derive `low` and `high` for ANY Problem 🔥

```
low  = minimum value below which problem BREAKS
       → "below this, some element can never be handled"

high = maximum value beyond which answer is POINTLESS
       → "at this value, everything fits in 1 unit"
```

| Problem | low | high |
|---|---|---|
| Ship Packages | `max(weights)` | `sum(weights)` |
| Book Allocation | `max(books)` | `sum(books)` |
| Koko Bananas | `1` | `max(piles)` |

---

## Edge Case

```cpp
if (k > arr.size()) return -1;
```

> If students > books → impossible! Each student needs at least 1 book.

---

## isPossible() Logic

> Given max pages limit `mid` — can we allocate all books to k students?

```
Walk array left to right, accumulate pages:
totalPages += books[i]
if totalPages > mid:
    → new student needed (students++)
    → reset totalPages = books[i]  ← current book goes to new student!
after loop:
    → students++  ← count last student!
return students <= k
```

**Why `students <= k`?**
```
students needed <= students available → possible ✅
students needed >  students available → impossible ❌
```

---

## Dry Run

```
books = [12, 34, 67, 90], mid = 113, k = 2
totalPages = 0, students = 0
```

| i | books[i] | totalPages | > 113? | students |
|---|---|---|---|---|
| 0 | 12 | 12 | ❌ | 0 |
| 1 | 34 | 46 | ❌ | 0 |
| 2 | 67 | 113 | ❌ | 0 |
| 3 | 90 | 203 | ✅ new student! reset=90 | 1 |

After loop → `students++ = 2`
`2 <= 2` → ✅ **max pages 113 works!**

---

## Final Code (C++)

```cpp
class Solution {
public:
    bool isPossible(vector<int>& arr, int k, int pages) {
        int students   = 0;
        int totalPages = 0;

        for (int i = 0; i < arr.size(); i++) {
            totalPages += arr[i];

            if (totalPages > pages) {
                students++;                // new student needed
                totalPages = arr[i];       // current book goes to new student
            }
        }
        students++;                        // count last student!

        return students <= k;              // students needed <= available?
    }

    int findPages(vector<int>& arr, int k) {
        // Edge case — more students than books
        if (k > (int)arr.size()) return -1;

        int low  = *max_element(arr.begin(), arr.end());
        int high = 0;
        for (auto val : arr) high += val;

        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(arr, k, mid)) {
                ans  = mid;
                high = mid - 1;            // minimize → go left
            } else {
                low  = mid + 1;            // too small → go right
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
| Time | O(n log s) — log s iterations × O(n) isPossible |
| Space | O(1) |

Where `n` = number of books, `s` = sum(books)

---

## Ship Packages vs Book Allocation 🔥

> Same problem — different story!

| | Ship Packages | Book Allocation |
|---|---|---|
| Array | `weights` | `books` |
| Constraint | `days` | `k students` |
| low | `max(weights)` | `max(books)` |
| high | `sum(weights)` | `sum(books)` |
| isPossible | `days <= d` | `students <= k` |
| Pattern | Minimize | Minimize |
| Edge case | None | `k > n → -1` |

---

## Common Mistakes ⚠️

```cpp
// ❌ Forgetting edge case
// k > n is impossible — each student needs at least 1 book!
if (k > arr.size()) return -1;

// ❌ Forgetting to count last student
return students <= k;   // last student never counted!

// ✅ Always increment after loop
students++;
return students <= k;

// ❌ Resetting totalPages to 0
totalPages = 0;         // current book lost!

// ✅ Reset to current book
totalPages = arr[i];    // current book goes to new student
```

---

## Key Takeaways 🔥

- *"low = max(books) because largest book must go to someone — can't go below this."*
- *"high = sum(books) because one student reads everything — no point going higher."*
- *"Always count last student after loop — easiest bug to miss."*
- *"students <= k means students NEEDED are within students AVAILABLE."*
- *"Book Allocation and Ship Packages are the same problem with different stories!"*
- *"Edge case: more students than books → impossible → return -1."*
