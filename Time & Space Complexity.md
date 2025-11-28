# Time Complexity — Key Points to Remember

✅ **1. Big-O measures growth, not actual time**

Focus on how running time increases as n grows.

“Ignore constants and lower-order terms.”

✅ **2. Golden Rule: 1 second ≈ 10⁸ operations**

Use this to check if your code will TLE.

✅ **3. Always check input constraints**

n ≤ 10⁵ → use O(n) or O(n log n)

n ≤ 10⁴ → O(n²) is okay

n ≤ 500 → O(n³) is okay

n ≤ 25 → O(2ⁿ) is okay

n ≤ 10 → O(n!) is okay

✅ **4. Typical complexities to remember**

Loop: O(n)

Nested loop: O(n²)

Sorting: O(n log n)

Binary search: O(log n)

Hashing average: O(1)

✅ **5. Worst case is used most**

Guarantees algorithm will never exceed this time.

Safe for all inputs.

✅ **6. Avoid exact operations**

Because different CPUs/compilers change instruction counts.

Big-O abstracts away hardware.

✅ **7. Recursion affects time too**

Recursive calls → count how many times function is called.


# Space Complexity — Key Points to Remember

✅ **1. Measures EXTRA memory used**

Not input size

Only additional memory used by your algorithm

✅ **2. What counts as space**

Temporary variables → O(1)

Arrays, vectors → O(n)

Maps, sets → O(n)

Recursion stack → depth = space

✅ **3. Auxiliary space vs total space**

Auxiliary space = extra memory (most used in DSA)

Total space = input + extra

✅ **4. Recursion uses stack memory**

Example:

DFS recursion depth = O(n)

Factorial recursion depth = O(n)

✅ **5. Memory-efficient patterns**

Two-pointer technique → O(1) space

In-place sorting → O(1) space

BFS/DFS → O(n) space (queue or recursion)

✅ **6. Ignore constants in space as well**

O(3n) → O(n)

O(n + 100) → O(n)


# Shortcut Table for TC vs Input Size

| Complexity | Safe for n ≤ |
| ---------- | ------------ |
| O(n)       | 10⁷ – 10⁸    |
| O(n log n) | 10⁵ – 10⁶    |
| O(n²)      | 10⁴          |
| O(n³)      | 500          |
| O(2ⁿ)      | 25           |
| O(n!)      | 10           |

# Final 5-Point Summary

1️⃣ Always check input constraints before choosing an approach.
2️⃣ 1 second = ~10⁸ operations in C++.
3️⃣ Avoid O(n²) when n > 10⁵.
4️⃣ Space complexity counts extra memory (arrays, maps, stacks).
5️⃣ Recursion affects both time and space due to call stack.