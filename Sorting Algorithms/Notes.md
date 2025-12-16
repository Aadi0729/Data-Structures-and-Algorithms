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



# 5. QUICK SORT

1️⃣ What is Quick Sort?

Quick Sort is a Divide and Conquer sorting algorithm that sorts an array by:

choosing a pivot

partitioning the array around the pivot

recursively sorting the left and right subarrays

2️⃣ Core Idea (Must Remember)

Place one element (pivot) in its correct position, then solve the same problem on smaller subarrays.

Quick Sort does not try to sort everything at once.

3️⃣ Principle Used

Divide & Conquer

Divide → partition around pivot

Conquer → recursively sort subarrays

Combine → no explicit merge required

4️⃣ Pivot

A pivot is a chosen element around which the array is partitioned.

Pivot selection strategies:

First element

Last element

Random element

Median of three

👉 Pivot choice strongly affects performance.

5️⃣ Partitioning (Key Operation)

Partitioning rearranges elements such that:

All elements ≤ pivot are on the left

All elements > pivot are on the right

Pivot ends up in its final sorted position

After partition:

Left Subarray | Pivot | Right Subarray


The pivot index is called the partition index.

6️⃣ Recursive Structure
quickSort(low, high):
    if low >= high → return
    p = partition(low, high)
    quickSort(low, p-1)
    quickSort(p+1, high)

7️⃣ Base Case (Very Important)
if (low >= high) return;


Why?

low == high → single element (already sorted)

low > high → empty subarray

Partitioning can create empty subarrays, so both must stop recursion.

8️⃣ How Quick Sort Works (Execution Flow)

quickSort() is called

Base case checked

partition() is executed

Pivot reaches correct position

Left and right recursive calls are made

Process repeats until array is sorted

9️⃣ Time Complexity (TC)
🔹 Partition Cost

Partition always scans the subarray once

Cost = O(n)

🔹 Best Case — O(n log n)

Pivot divides array into nearly equal subarrays

Work per level = O(n)

Number of levels = log n

O(n) × log n = O(n log n)

🔹 Average Case — O(n log n)

Random pivot usually produces reasonably balanced splits

Most real-world cases fall here

🔹 Worst Case — O(n²)

Occurs when:

Pivot is always smallest or largest

Array already sorted

Partition produces:

0 elements | n-1 elements


Total work:

n + (n-1) + (n-2) + ... + 1 = O(n²)

🔹 Time Complexity Summary
Case	Time
Best	O(n log n)
Average	O(n log n)
Worst	O(n²)
🔟 Space Complexity (SC)

Quick Sort is in-place, but recursion uses stack space.

🔹 What counts as space?

Only recursive quickSort() calls

partition() is temporary → O(1) space

🔹 Best / Average Case — O(log n)

Balanced recursion

Stack depth ≈ log n

🔹 Worst Case — O(n)

Skewed recursion

Each call reduces problem size by 1

🔹 Space Complexity Summary
Case	Space
Best / Average	O(log n)
Worst	O(n)
1️⃣1️⃣ Stability

❌ Not Stable

Equal elements may change relative order due to swapping

1️⃣2️⃣ In-place?

✅ Yes

No extra array required

1️⃣3️⃣ Adaptive?

❌ No

Does not become faster automatically for sorted arrays

Sorted input can cause worst case

1️⃣4️⃣ Advantages

Very fast in practice

In-place sorting

Cache-friendly

Widely used in standard libraries

1️⃣5️⃣ Disadvantages

Worst-case O(n²)

Not stable

Performance depends on pivot choice

1️⃣6️⃣ How to Improve Quick Sort

Randomized pivot selection

Median-of-three pivot

Hybrid approaches (Introsort)

1️⃣7️⃣ Real-World Usage

std::sort() → Introsort (Quick Sort + Heap Sort)

Java primitive array sort → Dual-Pivot Quick Sort

Used when performance & memory efficiency matter

1️⃣8️⃣ Quick Sort vs Merge Sort (One-liner)

Merge Sort → stable, extra space, guaranteed O(n log n)

Quick Sort → in-place, faster in practice, but worst case exists

1️⃣9️⃣ One-Line Interview Summary (Gold)

“Quick Sort is an in-place divide-and-conquer algorithm that partitions the array around a pivot and recursively sorts subarrays, achieving O(n log n) average time but O(n²) in the worst case.”

2️⃣0️⃣ Key Takeaways (Must Remember)

Partition does the real work

Pivot choice decides performance

Recursion depth decides space complexity

Balanced recursion → fast

Skewed recursion → slow