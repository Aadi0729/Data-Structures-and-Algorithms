```
class Solution {
public:
    int floorSqrt(int n)  {
      int low = 1;
      int high = n;

      int ans = 1;

      while(low <= high) {
        int mid = low + (high-low)/2;

        if(mid*mid <= n) {
            ans = mid;
            low = mid+1;
        }
        else
            high = mid-1;
      }

      return ans;
    }
};
```
O(log n) - Binary Search — for n = 10⁹, this is only ~30 iterations. log₂(10⁹) ≈ 30.
