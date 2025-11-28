# ⭐ C++ STL Revision Sheet (Ultimate One-Page Guide)

## (containers → iterators → algorithms → adapters)

**🔷 1. SEQUENCE CONTAINERS**

These store elements in a sequence (like arrays/lists).

*1️⃣ vector*

Dynamic array (contiguous memory)

Random access: O(1)

Insert/delete at end: O(1) amortized

Insert/delete at front/middle: O(n)

Best for: indexing, fast access, resizing.

*2️⃣ deque*

Double-ended vector

Fast at both ends: O(1)

Random access supported

Used as base for queue, stack

*3️⃣ list (doubly linked list)*

Not contiguous

No random access

Insert/delete anywhere: O(1)

Good for when you remove elements frequently

**🔷 2. ASSOCIATIVE CONTAINERS**

These store data in sorted order using balanced BST (red-black tree).

*1️⃣ set*

Stores unique elements

Sorted

All operations: O(log n)

*2️⃣ multiset*

Sorted

Duplicates allowed

Erase(key) removes ALL duplicates

Erase(iterator) removes one instance

Great for sliding window, median, frequency tracking

*3️⃣ map*

Key → Value

Unique keys

Sorted by key

O(log n)

*4️⃣ multimap*

Key → Value

Duplicate keys

Sorted by key

Useful for grouping

**🔷 3. UNORDERED CONTAINERS (HASH TABLES)**

These are super fast on average.

*1️⃣ unordered_set*

Unique elements

No sorting

Average O(1) lookup

Good for: duplicates check, hashing problems

*2️⃣ unordered_map*

Key → Value

No sorting

O(1) average

BEST for: frequency maps, Two-Sum, anagrams

*3️⃣ unordered_multiset / unordered_multimap*

Same as above, allows duplicates

Rarely needed in beginner DSA

**🔷 4. ITERATORS (very important)**

| Type              | Examples          | Supports                      |
| ----------------- | ----------------- | ----------------------------- |
| **Random Access** | vector, deque     | `it + n`, `it[n]`, fast moves |
| **Bidirectional** | list, set, map    | only `++it`, `--it`           |
| **Forward**       | unordered_set/map | only `++it`                   |

Remember:

*vector → all pointer-like operations*
*list → cannot do it+1*
*set/map → sorted traversal*

**🔷 5. IMPORTANT STL ALGORITHMS**

*🔥 Searching*

binary_search() → x exists? (sorted only)

lower_bound() → first element ≥ x

upper_bound() → first element > x

*🔥 Sorting*

sort(begin, end) → quicksort+mergesort+heapsort hybrid

reverse(begin, end)

*🔥 Utility*

max_element() → iterator to max

min_element() → iterator to min

find() → iterator to value (O(n))

count() → frequency (O(n))

accumulate() → sum of range

**🔷 6. CONTAINER ADAPTERS (built on top of other containers)**

*1️⃣ stack (LIFO)*

Underlying: deque

push, pop, top → O(1)

*2️⃣ queue (FIFO)*

Underlying: deque

push back, pop front → O(1)

*3️⃣ priority_queue (heap)*

Underlying: vector

max heap by default

For min heap:
priority_queue<int, vector<int>, greater<int>>

**🔷 7. WHICH CONTAINER TO USE? (Cheat Sheet)**

|               **Need**               | **Use**        |
| ------------------------------------ | -------------- |
| Fast search + no duplicates + sorted | set            |
| Fast search + duplicates + sorted    | multiset       |
| Fast search + any order + O(1)       | unordered_set  |
| Key-value + sorted                   | map            |
| Key-value + duplicates + sorted      | multimap       |
| Key-value + O(1)                     | unordered_map  |
| Fast indexing                        | vector         |
| Fast push/pop both ends              | deque          |
| Lots of insert/delete in middle      | list           |
| Kth largest/smallest                 | priority_queue |
| DFS/parenthesis/undo                 | stack          |
| BFS/task scheduling                  | queue          |

**🔷 8. THE MOST IMPORTANT DIFFERENCES TO MEMORIZE**

*✔ set vs unordered_set*

set → sorted, log(n)
unordered_set → fast, O(1), no sorting

*✔ map vs unordered_map*

map → sorted
unordered_map → fastest, hashing

*✔ set vs multiset*

set: no duplicates
multiset: duplicates allowed

*✔ map vs multimap*

map: unique keys
multimap: duplicate keys

*✔ vector vs list*

vector: random access
list: fast insert/delete

*✔ deque vs vector*

deque: fast at both ends
vector: fast only at back