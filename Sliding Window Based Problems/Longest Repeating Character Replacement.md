Pattern: Sliding Window (Variable Size)

🧠 Problem Insight

Given a string s and an integer k,
we can replace at most k characters in any substring.

Goal:

Find the length of the longest substring that can be converted into a string of identical characters using at most k replacements.

🔎 Key Observation

In any window:

replacements needed = window_size − maxFreq

Where:

maxFreq = frequency of the most common character in the current window.

We keep the most frequent character and replace the rest.

✅ Window Validity

A window is valid if:

window_size − maxFreq ≤ k

Invalid when:

window_size − maxFreq > k
🪟 Sliding Window Type

Variable Size Window

Expand greedily using right pointer.

Maintain frequency map.

Track maxFreq dynamically.

Shrink window when invalid.

🔄 Window Movement Logic

Expand by moving right.

Update frequency of current character.

Update maxFreq.

If window becomes invalid:

Shrink from left (single step).

Update maximum window length.

⚠️ Important Detail

maxFreq is updated only during expansion.

We do NOT recompute it during shrinking.

This keeps the solution O(n).

```
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();

        unordered_map<char, int> freqMap;

        int left = 0;
        int right = 0;

        int maxFreq = 0;
        int maxLen = 0;

        while(right < n) {
            freqMap[s[right]]++;
            maxFreq = max(maxFreq, freqMap[s[right]]);

            if((right-left+1) - maxFreq > k) {
                freqMap[s[left]]--;
                left++;
            }

            maxLen = max(maxLen, right-left+1);
            right++;
        }
        return maxLen;
    }
};
```

⏱️ Complexity

Time: O(n)
Each character enters and leaves the window once.

Space: O(1)
(At most 26 characters for uppercase letters.)

📌 Pattern Takeaway

Window validity depends on dominant frequency, not distinct count.

Different from “At Most K Distinct”.

Introduces concept of allowed modifications inside window.

Shrinking uses if, not while.
