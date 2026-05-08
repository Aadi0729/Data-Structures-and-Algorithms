# Square Root of N — Interview Style 🎯
## Brute Force → Better → Optimal

> **Pattern:** Binary Search on Answer
> **Difficulty:** Easy
> **Platform:** GFG / Leetcode #69

---

## Problem Statement

Given a non-negative integer `n`, return the **integer (floor) square root** of `n`
without using any built-in power or square root functions.

```
n = 25 → return 5
n = 30 → return 5  (floor of 5.47)
n = 0  → return 0
n = 1  → return 1
```

---

## Clarifying Questions to Ask Interviewer

```
1. Should I start from brute force and optimize step by step?
2. Should I return floor value or ceiling value?
3. What is the range of n? (32-bit? 64-bit?)
4. Can n be negative?
5. Can you confirm with an example?
```

**Interviewer Answers:**
```
→ Yes, start from brute force
→ Floor value (integer part only)
→ 0 ≤ n ≤ 2^31 - 1 (32-bit non-negative)
→ n is always non-negative
→ n=25→5, n=30→5, n=0→0
```

> 🔥 **Tip:** Asking about constraints before coding shows
> you think about overflow and edge cases upfront.

---

## APPROACH 1 — Brute Force

### Intuition:
```
Check every value i from 1 to n.
If i*i <= n → valid candidate, save it.
Return last valid candidate.
```

### Code:
```cpp
int floorSqrt(int n) {
    if(n == 0) return 0;

    int ans = 1;
    for(int i = 1; (long long)i * i <= n; i++) {
        ans = i;    // every i here satisfies i*i <= n
    }
    return ans;
}
```

### Complexity:
```
TC : O(n)  — checks every value from 1 to n
SC : O(1)  — only ans variable used
```

### Bottleneck:
```
For n = 10^9 → 1,000,000,000 iterations 😬
We're checking every single value linearly
even though we don't need to.
```

### What to say in interview:
```
"This brute force works correctly but has a significant
 performance issue. We're checking every value from 1 to n
 linearly — that's O(n). For n = 10^9, that's 1 billion
 iterations which will definitely TLE.

 The bottleneck is the linear scan.
 Can I think of a better approach?"
```

---

## APPROACH 2 — Better (Loop till √n)

### Key Observation:
```
The answer x always satisfies x*x <= n.
So we never need to check beyond √n.
Change loop condition to i*i <= n →
loop automatically stops at √n!
```

### Code:
```cpp
int floorSqrt(int n) {
    if(n == 0) return 0;

    int ans = 1;
    for(int i = 1; (long long)i * i <= n; i++) {
        ans = i;
    }
    return ans;
}
```

### Complexity:
```
TC : O(√n) — loop stops naturally at √n
SC : O(1)  — unchanged
```

### Improvement:
```
n = 10^9:
Brute Force → 1,000,000,000 iterations
Better      →        31,623 iterations ✅
```

### What to say in interview:
```
"By changing the loop condition to i*i <= n,
 the loop naturally terminates at √n.
 This brings us from O(n) to O(√n).

 For n = 10^9 — from 1 billion to ~31,623 iterations.
 Significant improvement!

 But we can do even better.
 O(log n) is possible here.
 Should I think about that?"
```

---

## APPROACH 3 — Optimal (Binary Search on Answer)

### Key Observation:
```
Look at the condition i*i <= n as i increases:

i:    1    2    3    4    5    6    7
i*i:  1    4    9   16   25   36   49

For n=30:
      ✅   ✅   ✅   ✅   ✅   ❌   ❌

The condition is MONOTONIC — TRUE→FALSE flip.
Once FALSE → always FALSE.
Once TRUE  → always TRUE before it.

Clean boundary exists → Binary Search applicable!
```

### Monotonic Pattern:
```
✅ ✅ ✅ ✅ ✅ ❌ ❌ ❌
               ↑
         BOUNDARY
    (last TRUE = answer)

Pattern  : TRUE → FALSE
Goal     : Find LAST TRUE
Type     : MAXIMIZE
Direction: when TRUE → ans=mid, low=mid+1 (go right)
           when FALSE → high=mid-1 (go left)
```

### Search Space:
```
low  = 1  (minimum possible answer)
high = n  (maximum possible answer — x*x=n means x≤n)
```

### isPossible(mid):
```
mid * mid <= n
```

### Code:
```cpp
int floorSqrt(int n) {
    if(n == 0) return 0;

    int low = 1, high = n;
    int ans = 1;

    while(low <= high) {
        long long mid = low + (high - low) / 2;  // long long → overflow safe

        if(mid * mid <= n) {
            ans = mid;          // valid → save (last TRUE)
            low = mid + 1;      // maximize → go right
        }
        else {
            high = mid - 1;     // too big → go left
        }
    }
    return ans;
}
```

### Complexity:
```
TC : O(log n) — binary search on [1, n]
SC : O(1)     — no extra space
```

### Dry Run (n = 30):
```
low=1, high=30, ans=1

Iter 1: mid=15 → 15*15=225 > 30 → high=14
Iter 2: mid=7  → 7*7=49   > 30 → high=6
Iter 3: mid=3  → 3*3=9    ≤ 30 → ans=3, low=4
Iter 4: mid=5  → 5*5=25   ≤ 30 → ans=5, low=6
Iter 5: mid=6  → 6*6=36   > 30 → high=5

low=6 > high=5 → STOP
return 5 ✅

Only 5 iterations vs 30 (brute) vs 6 (better)!
```

---

## Complete Tradeoff Table 🔥

| Approach | TC | SC | n=10^9 iterations | When to use |
|---|---|---|---|---|
| Brute Force | O(n) | O(1) | 1,000,000,000 | Never in interviews |
| Better | O(√n) | O(1) | ~31,623 | If BS not allowed |
| Optimal | O(log n) | O(1) | ~30 | Always preferred |

---

## Interview Presentation Script 🎤

```
STEP 1 — CLARIFY:
"Before I start — let me clarify a few things.
 Should I return floor or ceiling?
 What's the range of n — do I need to worry about overflow?
 [get answers]
 Great. Let me start with brute force."

STEP 2 — BRUTE FORCE:
"Naive approach — check every i from 1 to n.
 If i*i <= n → valid candidate.
 TC: O(n), SC: O(1).
 Bottleneck: linear scan for large n.
 For n=10^9 → 1 billion iterations. Too slow."

STEP 3 — BETTER:
"Key observation — answer x satisfies x*x<=n,
 so loop naturally stops at √n.
 TC: O(√n), SC: O(1).
 10^9 iterations → 31,623. Much better!
 But O(log n) is possible. Should I continue?"

STEP 4 — OPTIMAL:
"Notice i*i is monotonically increasing.
 Condition i*i<=n gives TRUE→FALSE pattern.
 Monotonic condition → Binary Search applicable!
 Search space: [1, n]
 isPossible(mid): mid*mid <= n
 Maximize → last TRUE → go right when TRUE.
 TC: O(log n), SC: O(1).
 10^9 iterations → only 30!"

STEP 5 — CODE:
"Let me write the clean solution.
 I'll use long long for mid to handle overflow."
[write code]
[dry run with n=30]

STEP 6 — EDGE CASES:
"Edge cases I've handled:
 n=0 → return 0 (separate check)
 n=1 → loop runs, mid=1, 1*1<=1, returns 1 ✅
 overflow → long long mid handles it ✅"
```

---

## Common Mistakes in Interviews ⚠️

```
1. Forgetting n=0 edge case → returns 1 instead of 0
2. Using (low+high)/2 → overflow for large n
3. Not casting to long long → mid*mid overflows
4. Wrong loop condition i<n → misses perfect squares
5. Saying "monotonically decreasing" for TRUE→FALSE boolean pattern
   → Correct term: "monotonic condition with TRUE→FALSE flip"
```

---

## Key Takeaways 🔥

- *"Always clarify constraints before coding — overflow is real."*
- *"Bottleneck of brute force = linear scan = O(n)."*
- *"Better approach = reduce loop bound from n to √n."*
- *"Optimal = monotonic condition → binary search on answer."*
- *"TRUE→FALSE pattern = maximize = go right when TRUE."*
- *"long long mid — not int mid — for overflow safety."*
