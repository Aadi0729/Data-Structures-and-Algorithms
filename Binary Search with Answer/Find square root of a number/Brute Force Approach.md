Given a positive integer n. Find and return its square root. If n is not a perfect square, then return the floor value of sqrt(n).
```
Example 1
Input: n = 36

Output: 6

Explanation: 6 is the square root of 36.
```
```
Example 2

Input: n = 28

Output: 5

Explanation: The square root of 28 is approximately 5.292. So, the floor value will be 5.
```
```
class Solution {
public:
    int floorSqrt(int n)  {
        int ans = 1;
      for(int i=1; i<=n; i++) {
        if(i*i <= n)
            ans = i;
        else
            break;
      }
      return ans;
    }
};
```

O(n) - Brute force — for n = 10⁹, this is 1,000,000,000 iterations. Times out every time.
