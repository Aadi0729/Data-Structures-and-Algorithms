# Median of Two Sorted Arrays

**LeetCode #4 | Difficulty: Hard | Pattern: Binary Search on Partition | Problem #13**  
**Language: C++**

---

## 1. Problem Statement

Given two sorted arrays `nums1` and `nums2` of sizes `m` and `n` respectively, return the **median of the two sorted arrays**.

> The overall runtime complexity must be **O(log(min(m,n)))**.

| Constraint | Value |
|---|---|
| nums1 size (m) | 0 to 1000 |
| nums2 size (n) | 0 to 1000 |
| Element range | -10^6 to 10^6 |
| At least one array | non-empty |

---

## 2. Approaches Overview

| Approach | Time Complexity | Space Complexity | Key Idea |
|---|---|---|---|
| Brute Force | O(m+n) | O(m+n) | Merge both arrays, find middle |
| Better | O(m+n) | O(1) | Two-pointer walk without storing merged array |
| **Optimal (BS)** | **O(log(min(m,n)))** | **O(1)** | **Binary search on partition position** |

---

## 3. Brute Force — O(m+n) Time, O(m+n) Space

### Intuition

Both arrays are already sorted. Merge them using the two-pointer technique into a new array, then directly access the middle element(s).

### Step-by-Step Logic

1. Use two pointers `left` and `right` on `nums1` and `nums2` respectively
2. At each step pick the smaller element and push to `temp` array
3. Drain remaining elements from whichever array has leftovers
4. If total size is **odd** → return `temp[mid]`
5. If total size is **even** → return `(temp[mid] + temp[mid+1]) / 2.0`

### Code

```cpp
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<int> temp;

    int left = 0, right = 0;
    while(left < m && right < n) {
        if(nums1[left] <= nums2[right]) temp.push_back(nums1[left++]);
        else temp.push_back(nums2[right++]);
    }
    while(left < m)  temp.push_back(nums1[left++]);
    while(right < n) temp.push_back(nums2[right++]);

    int i = 0, j = m + n - 1;
    if(temp.size() % 2 != 0) {
        int mid = (i + j) / 2;
        return temp[mid];
    } else {
        int mid = (i + j) / 2;
        return (temp[mid] + temp[mid+1]) / 2.0;
    }
}
```

> ⚠️ **Why this is wasteful:** We build a million-element array just to read 1 or 2 elements from the middle. The arrays are already sorted — we are throwing away that information completely.

---

## 4. Optimal — O(log(min(m,n))) Time, O(1) Space

### Core Insight — The Partition Idea

We do **not** need to merge. The median divides the combined virtual array into two equal halves. We need to find a **cut** on `nums1` and `nums2` such that:

- Left half of combined array ≤ Right half of combined array
- Both halves have equal size (or left has one extra for odd total)

> 💡 **Key Realization:** If I fix the cut position on `nums1`, the cut on `nums2` is **automatically determined** because left half size is fixed. This means we only need to binary search on **ONE array**.

---

### Visualizing the Cut

Imagine two scissors cutting both arrays:

```
nums1:  [1,  3] | [5,  8]      L1=3,  R1=5
nums2:  [2,  4] | [6,  9]      L2=4,  R2=6

Left half  = everything LEFT  of both cuts → [1, 3, 2, 4]
Right half = everything RIGHT of both cuts → [5, 8, 6, 9]
```

The 4 boundary elements are:

| Variable | Meaning |
|---|---|
| `L1` | Last element of `nums1` on the LEFT of cut |
| `R1` | First element of `nums1` on the RIGHT of cut |
| `L2` | Last element of `nums2` on the LEFT of cut |
| `R2` | First element of `nums2` on the RIGHT of cut |

---

### Validity Condition

For the partition to be valid — left half must truly contain all smaller elements:

```
L1 <= R2   (last of nums1 left  <=  first of nums2 right)
L2 <= R1   (last of nums2 left  <=  first of nums1 right)
```

We don't need to check `L1 <= R1` or `L2 <= R2` — those are guaranteed since each array is already sorted.

---

### Median Calculation

| Case | Formula | Reason |
|---|---|---|
| Even total size | `(max(L1,L2) + min(R1,R2)) / 2.0` | Average of last-of-left and first-of-right |
| Odd total size | `max(L1, L2)` | Left half has the extra element — its max is the median |

---

### Binary Search Direction

| Condition | Meaning | Action |
|---|---|---|
| `L1 > R2` | cut1 took too much from nums1 — L1 must go to right half | `high = cut1 - 1` (move cut1 left) |
| `L2 > R1` | cut2 took too much — need to give more to nums1 | `low = cut1 + 1` (move cut1 right) |
| `L1<=R2 && L2<=R1` | Valid partition found! | Calculate and return median |

**Why these directions?**
- `L1 > R2` → cut1 grabbed too many elements from nums1. The last element of nums1's left portion is too large and belongs in the right half. So we shrink cut1 → `high = cut1 - 1`.
- `L2 > R1` → cut2 is too large, meaning cut1 is too small. We need to move cut1 right to give fewer elements to nums2's left portion → `low = cut1 + 1`.

---

### Edge Cases — INT_MIN / INT_MAX

When cut is at boundary (0 or m), there is no element on one side. We handle this with sentinels:

```cpp
int L1 = cut1 == 0 ? INT_MIN : nums1[cut1-1];  // nothing on left  → -infinity
int L2 = cut2 == 0 ? INT_MIN : nums2[cut2-1];  // nothing on left  → -infinity
int R1 = cut1 == m ? INT_MAX : nums1[cut1];     // nothing on right → +infinity
int R2 = cut2 == n ? INT_MAX : nums2[cut2];     // nothing on right → +infinity
```

- `INT_MIN` ensures a missing left element **never wrongly blocks** the validity condition
- `INT_MAX` ensures a missing right element **never wrongly blocks** the validity condition

---

### Why `(m+n+1)/2` and not `(m+n)/2`

```
Total = 6 (even) → (6)/2 = 3,  (6+1)/2 = 3  → SAME ✅
Total = 5 (odd)  → (5)/2 = 2,  (5+1)/2 = 3  → DIFFERENT
```

| Formula | Odd total behaviour | Return value |
|---|---|---|
| `(m+n)/2` | Left gets 2, right gets 3 | Must return `min(R1, R2)` |
| `(m+n+1)/2` | Left gets 3, right gets 2 | Must return `max(L1, L2)` ✅ |

The `+1` and returning `max(L1, L2)` are a **matched pair** — change one, change the other.

---

### Why Binary Search on the Smaller Array

We always enforce `m <= n` (swap if needed). This guarantees:

```
cut2 = (m+n+1)/2 - cut1
```

Since `cut1` ranges from `0 to m`, and `m <= n`, `cut2` always stays within `[0, n]`. Without this guarantee, `cut2` could go negative or exceed `n`.

---

### Final Optimal Code

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        // Always binary search on the smaller array
        if(m > n)
            return findMedianSortedArrays(nums2, nums1);

        int low = 0;
        int high = m;

        while(low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = (m + n + 1) / 2 - cut1;

            int L1 = cut1 == 0 ? INT_MIN : nums1[cut1-1];
            int L2 = cut2 == 0 ? INT_MIN : nums2[cut2-1];
            int R1 = cut1 == m ? INT_MAX : nums1[cut1];
            int R2 = cut2 == n ? INT_MAX : nums2[cut2];

            if(L1 <= R2 && L2 <= R1) {
                // Valid partition found — calculate median
                if((m + n) % 2 == 0)
                    return (max(L1, L2) + min(R1, R2)) / 2.0;
                else
                    return max(L1, L2);
            }
            else if(L1 > R2)
                high = cut1 - 1;
            else
                low = cut1 + 1;
        }
        return 0;
    }
};
```

---

## 5. Complexity Analysis

| Approach | Time | Space | Note |
|---|---|---|---|
| Brute Force | O(m+n) | O(m+n) | Merges entire array into temp |
| Optimal (BS) | O(log(min(m,n))) | O(1) | BS only on the smaller array |

---

## 6. Interview Guide

### How to Open This Problem

> *"Both arrays are sorted — instead of merging, I want to binary search for the right partition position. The median splits the combined array into two equal halves. If I fix the cut on nums1, the cut on nums2 is automatically determined. So I only need to search in one dimension."*

### Common Mistakes

| Mistake | Why it breaks | Fix |
|---|---|---|
| Not swapping arrays | cut2 can go out of bounds on nums2 | Always ensure m <= n |
| Using `(m+n)/2` without `+1` | Wrong left half size for odd total | Use `(m+n+1)/2` |
| Missing INT_MIN/INT_MAX | Validity check crashes at boundaries | Always add sentinel handling |
| Integer overflow in median | max(L1,L2) + min(R1,R2) can overflow | Use `2.0` cast or `long long` |

### Expected Follow-up Questions

- **Why O(log(min(m,n))) and not O(log(m+n))?** — We only binary search in one array (the smaller one).
- **What if one array is empty?** — INT_MIN/INT_MAX sentinels handle it automatically.
- **What if both arrays have one element?** — Handled correctly by the even/odd formula.
- **Can you do it without binary search?** — Yes, O(m+n) merge, but that wastes the sorted property entirely.
- **Does the order of nums1/nums2 matter?** — No, the swap at the top handles any ordering.

---

## 7. YouTube Explanation Notes

### Hook (First 30 Seconds)
> *"This is LeetCode Hard #4. Most people either memorize it or avoid it. Today we will derive it from first principles — once you understand the partition idea, the code writes itself."*

### Explanation Flow
1. Start with brute force — merge and find middle. Clean, correct, but wasteful.
2. Ask: *do we really need to build the whole array? What is median REALLY telling us?*
3. Introduce the **cut visualization** — two scissors on two arrays.
4. Derive the validity condition `L1<=R2` and `L2<=R1` interactively.
5. Show **linked cuts** — fix cut1, cut2 is determined. One dimension of search.
6. Show BS direction with monotonic argument — L1 too big means cut1 too far right.
7. Handle edge cases — boundary cuts with INT_MIN/INT_MAX.
8. Derive `(m+n+1)/2` naturally from odd/even convention.

### Whiteboard Visuals to Draw
- Two arrays with a vertical cut line on each
- L1, R1, L2, R2 labeled clearly at boundaries
- Arrow showing: move cut1 right → cut2 moves left automatically
- Validity condition as two crossing arrows between the arrays

---

## 8. Pattern Summary — Binary Search on Partition

### When to Use This Pattern

Use Binary Search on Partition when:
- Problem involves finding a split across **two sorted arrays**
- Fixing one partition **automatically determines** the other
- Validity can be checked with **O(1) boundary comparisons**
- There is **monotonic behavior** in the validity condition

### Pattern Template

```cpp
// Always BS on the smaller array (enforce m <= n)
int low = 0, high = m;

while(low <= high) {
    int cut1 = low + (high - low) / 2;
    int cut2 = (total_left_size) - cut1;

    // Get 4 boundary elements with sentinel handling
    int L1 = cut1 == 0 ? INT_MIN : arr1[cut1-1];
    int L2 = cut2 == 0 ? INT_MIN : arr2[cut2-1];
    int R1 = cut1 == m ? INT_MAX : arr1[cut1];
    int R2 = cut2 == n ? INT_MAX : arr2[cut2];

    if(valid(L1, L2, R1, R2)) {
        // compute answer from boundary elements
    }
    else if(L1 > R2) high = cut1 - 1;  // cut1 too far right
    else             low  = cut1 + 1;   // cut1 too far left
}
```

### Related Problems
- Median of Two Sorted Arrays (this problem)
- K-th Element of Two Sorted Arrays
- Find the Median of a Data Stream (different approach, same median intuition)

---

*Binary Search on Answer Series — Problem #13 of 13*  
*DSA Learning Journey | C++ | Brute → Optimal*
