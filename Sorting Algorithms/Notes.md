# 1. Selection Sort

**Idea:**

Repeatedly select the minimum element from the unsorted part and put it in the sorted part.

**Process:**

For each index i, find the minimum in i+1…n−1.

Swap it with i.

**Passes:**

n − 1

**Time Complexity:**

*Best:* O(n²)

*Avg:* O(n²)

*Worst:* O(n²)

**Space Complexity:**

O(1)

**Stable?:**

No (because long-distance swaps change order of equals)

**Adaptive?:**

No (even sorted arrays take full time)

**Key Insight:**

Few swaps → at most n − 1.


# 2. Bubble Sort

**Idea:**

Repeatedly compare adjacent elements and swap if out of order.
Large elements bubble to the end.

**Process:**

For each pass, scan from 0 to n−i−2.

Swap adjacent out-of-order pairs.

If no swap in a pass → array is sorted → stop early.

**Passes:**

Up to n − 1, but may stop early.

**Time Complexity:**

*Best:* O(n) (optimized version detects no swaps)

*Avg:* O(n²)

*Worst:* O(n²)

**Space Complexity:**

O(1)

**Stable?:**

Yes (adjacent swaps maintain order of duplicates)

**Adaptive?:**

Yes (optimized version)

**Key Insight:**

Optimized bubble sort stops early on sorted arrays.


# 3. Insertion Sort

**Idea:**

Build a sorted portion on the left and insert each new element into its correct position by shifting larger elements to the right.

**Process:**

For each index i, take key = a[i].

Move left while elements are greater than key.

Insert at correct position.

**Passes:**

n − 1

**Time Complexity:**

*Best:* O(n) (already sorted, zero shifts)

*Avg:* O(n²)

*Worst:* O(n²) (reverse sorted)

**Space Complexity:**

O(1)

**Stable?:**

Yes (no jumping over equals)

**Adaptive?:**

Yes (fast on nearly sorted arrays)

**Key Insight:**

Shifting is cheaper than swapping → very efficient for small or nearly-sorted data.


# 4. Merge Sort

*Idea:*

Use Divide & Conquer — split the array into halves, sort each half recursively, then merge the sorted halves.

*Process:*

Divide array into two halves until subarrays are size 1

Recursively sort left and right halves

Merge two sorted halves using two pointers and a temp array

*Levels:*

Splitting levels ≈ ⌈log₂(n)⌉ + 1

Merging levels ≈ ⌈log₂(n)⌉

*Time Complexity:*

Best: O(n log n)

Average: O(n log n)

Worst: O(n log n)

(At every merge level, all n elements are processed once.)

*Space Complexity:*

O(n) extra space (temporary array used during merging)

*Stable?:*

Yes (using <= during merge preserves order of equal elements)

*In-place?:*

No (requires extra memory for merging)

*Adaptive?:*

No (still performs full merge even if array is sorted)

*Key Insight:*

Although subarrays get smaller, all elements are merged at every level, leading to n × log n operations.

*When to Use:*

Large datasets

When stable sorting is required

When guaranteed O(n log n) worst-case time is needed

External sorting (disk-based data)

*Comparison Highlight:*

Faster and more predictable than O(n²) sorts

Uses more memory than Quick Sort