**1. What Is Recursion?**

Recursion is a problem-solving technique where a problem is expressed in terms of smaller instances of itself, and solved by:

Stopping at the simplest version of the problem → Base Case

Reducing the problem toward that simplest form → Recursive Case

Calling the same function on the reduced problem → Self Call

Recursion ≠ function calling itself.
Recursion = problem decomposition + result propagation.

**2. The Three Laws of Recursion**

Every valid recursive function must satisfy:

*1) Base Case*

The smallest version of the problem. Stops recursion.
Without it → infinite recursion → stack overflow.

*2) Recursive Case*

The part where the function solves a smaller version of itself.

*3) Progress Toward Base Case*

Every recursive call must reduce the problem size.
Otherwise the base case is never reached.

**3. Execution Flow: DOWN Phase & UP Phase**

Understanding recursion requires understanding the two phases:

*⬇ DOWN Phase (Call Expansion)*

Function calls itself repeatedly

Stack grows

Little or no output

Work done before recursive call → DOWN-phase work

*⬆ UP Phase (Return Contraction)*

Base case reached

Values begin returning

Work done after recursion → UP-phase work

**Examples:**

Print N→1: WORK happens in DOWN phase

Print 1→N: WORK happens in UP phase

Sum / Factorial: work in UP phase

**4. The Call Stack — How Recursion Actually Works**

Every recursive call creates a stack frame containing:

local variables

parameters

return address

When the recursive call returns → the frame is popped.

*Key properties:*

Stack depth = recursion depth

Max stack usage = O(depth)

Linear recursion → O(n) space

Binary recursion → still O(n) space (tree height = n)

Even if recursion makes 2ⁿ total calls, stack does NOT store all calls at once.

**5. Value Propagation in Recursion**

*Two modes of recursion:*

*1) Side-Effect Recursion*

Function performs action (like printing or modifying global/array values).
Does not rely on return values.

**Examples:**

Print 1→N

Print N→1

Print name N times

*2) Return-Value Recursion*

Function combines return values from smaller subproblems.
Examples:

Sum

Factorial

Palindrome

Fibonacci

Binary Search

Tree height

**Rule:**

If final result depends on subproblem results → you MUST return the recursive call.

**6. Recursion Tree — Visualizing Recursion**

Recursion trees reveal:

branching structure

time complexity

number of calls

problem decomposition pattern

Linear Recursion = Chain
f(n)
 |
f(n-1)
 |
...


Time: O(n)

Space: O(n)

Binary Recursion = Full Tree

Example: Fibonacci

             f(n)
            /   \
        f(n-1)  (n-2)


Time: O(2ⁿ)

Space: O(n)

Time = number of nodes in recursion tree
Space = height of recursion tree

**7. Foundational Recursion Problems**

Each problem below includes its reason, not its code.

## 1. Print N → 1 (Descending Order)

Base case: n == 0

Work BEFORE recursion (DOWN phase)

Shrink: n → n - 1

Output: N, N-1, …, 1

Reason: You announce floors while going down stairs.

## 2. Print 1 → N (Ascending Order)

Base case: n == 0

Recursion first

Work AFTER recursion (UP phase)

Output: 1, 2, 3, …, N

Reason: You announce floors while climbing up.

## 3. Print Name N Times

Base case: n == 0

Work can be DOWN or UP (order irrelevant)

Shrink: n → n - 1

Reason: Printing order doesn't matter.

## 4. Sum of First N Numbers

Base: 0

Work in UP phase

Formula:

sum(n) = n + sum(n-1)

Reason: Addition depends on results from smaller subproblems.

## 5. Factorial of N

Base: return 1
(1 is identity of multiplication, 0 would zero-out the result)

Work in UP phase

Formula:

n! = n × (n-1)!

## 6. Reverse Array (Two-Pointer Recursion)

Base: left >= right

Work: swap before recursion (DOWN phase)

Shrink: left++, right--

Reason: Fix outer elements → recursively reverse inner portion.

## 7. Palindrome Check

Base: left >= right → true

Early stop: mismatch → false

Shrink: left++, right--

Return-value recursion

## 8. Fibonacci — The Ultimate Recursion Model

fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2)

**Why Two Base Cases?**

Because every call depends on two smaller calls.
Two recursive paths → two termination points required.

Recursion Tree
               fib(n)
              /       \
         fib(n-1)      fib(n-2)
         /    \          /     \
     fib(n-2) fib(n-3) fib(n-3) fib(n-4)

Time Complexity → O(2ⁿ)

Nodes ≈ 2ⁿ → exponential growth.

Space Complexity → O(n)

Only the deepest branch is on the stack.

**When Does Addition Happen?**

In the UP phase (when returns combine).

Reason: Values from fib(n-1) and fib(n-2) must return before adding.

**9. When to Use Recursion**

*Use recursion when:*

Problem definition is naturally recursive

Output depends on exploring multiple possibilities

Result depends on combining smaller subproblem results

Problem follows divide-and-conquer

Data structure is tree-based

*Avoid recursion when:*

Depth is too large → stack overflow risk

Iteration is simpler/faster

Subproblems repeat → use DP