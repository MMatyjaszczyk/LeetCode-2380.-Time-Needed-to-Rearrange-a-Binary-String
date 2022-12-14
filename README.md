## Problem number 2380

# Brute-force

The problem asks us how many seconds is needed untill the process is completed. That basically translates into: "How many iterations will it take till the process is completed?". With question like this, we can try to do a simulation and count number of iterations as we go. \
Let's focuse now on how one iteration should look like. Pretty simple: swap all `01` into `10`. For me, the most logicall approach is a simple for loop.
```
for ii in 0 to len(arr) - 1
  if arr[ii] == '0' and arr[ii+1] == '1' do
    swap(ii,ii+1)
    ii += 1
  fi
```
As it could be seen we increse 'ii' once more when swap is done. To understand why, we can look at example: `011`. If we didn't do this, the process would end after one iteration (first iteration: `011` -> `101` -> `110`), when 2 are needed (first iteration `011` -> `101`; second iteration: `101` -> `110`). When `1` has another `1` on the left, it has to *wait*. \
Last question would be: how do we know that the process ended? The process ends when there are no more `01`. That means, we haven't done any `swap` during last iteration. We can just have a boolean telling us whether the change was made or not. \
**C++**
```
class Solution {
public:
    int secondsToRemoveOccurrences(std::string s) {
        int iterations = 0;
        bool changed = true;
        while(changed){
            changed = false;
            int ii = 0;
            while(ii < s.length()-1){
                if(s[ii] == '0' and s[ii+1] == '1'){
                    s[ii] = '1';
                    s[ii+1] = '0';
                    ii += 1;
                    changed = true;
                }
                ii += 1;
            }
            iterations += 1;
        }
        return iterations - 1;
    }
};
```
**python3**
```
class Solution:
    def secondsToRemoveOccurrences(self, s: str) -> int:
        s = list(s)
        iterations = 0
        changed = True
        while changed:
            changed = False
            ii = 0
            while ii < len(s)-1:
                if s[ii] == '0' and s[ii+1] == '1':
                    s[ii],s[ii+1] = s[ii+1],s[ii]
                    changed = True
                    ii += 1
                ii += 1
            iterations += 1
        return iterations - 1
```
**Complexity Analisys**
- Time Complexity: **O(n^2)**

Every iteration we go through the string. That gives us time complexity of `O(n*iter)`, where `n` is a length of string and `iter` is number of iterations (answere). We will see later on, that the number of iterations is never greater than `2n`, so time complexity is `O(n^2)`.

Space complexity: **O(1)**.

# DP

It is sometimes usefull to redefine a problem. We are asked: "How many iterations will it take for process to end?". Process will end when there won't be any `01` in our string. That is, when every `1` will "move" as much as it can to the left. (Swap from `01` to `10` can be seen as "move" of `1` to the left.) Don't stop there. When all `1`s will be max to the left? *When the last one will be.* \
Now we're talking. This logic tells us that we can narrow the problem to the question: "How many iterations will it take for the last `1` to move max to the left?"

We can see that by every iteration, for every `1` that still is not on it's destinated place there are 2 options: "when `0` on the left: move to the left" or "when `1` on the left: *wait*". So, the number of iterations needed for the last `1` to move to the left is equal the number of iterations the last `1` will *move* and the number of iterations it will *wait*. \
Number of times the last `1` will *move* is: it's index - number of `1`s in the string (index of it's destinated place).

*Wait* is a little bit more difficult to figure out. \
It's logical (it just is :>) that the nuber of *wait* iterations for every `1` in the string (expect the first) is dependent of the number of *waits* of `1` on the left. And here our DP begins. \
The hard part in (probably) every DP problem is to come up with the way one part is dependent on the other. Let's begin with the first `1` in our string. It is obvious (it just is :>) the number of *waits* for it, is 0. \
We have a base of DP, now we just need the equation. \
Let's see 2 examples, and let's focuse on the last `1` in both of them.

`0111011` and `0001111`. \
As we can see, both have the same number of *waits*. What is very important here, is the fact that the substring on the left of them are different, but the number of *waits* of `1`s on the left *are the same*. To be more precise: the number of *waits* for the last `1` in both cases is equal the number of *waits* of the `1` before the last plus 1. We can conclude from that, that when some `1` in the string has an `1` on the left, number of its *waits* is equal the number of *waits* of the previous `1` plus 1.
[Actually that is correct and there is a pretty proof for that but the file is too narrow to contain it. Will add later]

Almost there, now let's focuse on examples: `01111`, `011101`, `0111001`, and `01110001`. \
In the first example, the last `1` has 3 *waits*. In the second example, the last `1` has 2 *waits*. We can see that the strings are almost identical, just one extra `0` in the second. In the fird example there is one more `0` and the number of *waits* for the last `1` is one smaller - 1. In the last example we have 0 *waits* for the last `1`. From that we can conclude, that the number of *waits* for chosen `1` is dependent of the number of `0` beetwen the previous `1`. Being precise, with every `0` the number of *waits* decrises by 1.

Now we have everything. Keeping in mind, that the number of *waits* can not be smaller than 0, the number of waits is equal:
*max(w + 1 - z, 0)*, where "w" is a number of *waits* of the previous `1`, and "z" is a number of `0`s between the chosen `1` and the previous.
One more thing, let's consider `110`. From our previous logic it could be concluded that the last `1` has 1 *wait*. But it's obviously false. To repare it we can just find the first `0` in our string, and aplay our logic from that point.

[Looking at this, we can see that the number of waits for the last `1` could never be greater than the number of `1`s in the string. In conclusion, the number of iterations could never be greater than 2*len(s) (even smaller but that is enough). That is 2*n. And here is the reason that brute force aproach is O(n^2). :> ]

Now the easu part. Algorith will go something like: \
- Let's find the first `0` and consider a substring from that point - let call it s.
- Make an array of pairs - index of `1`, number of *waits* for a specific `1`.
- Set a number of *waits* for the first `1` to 0.
- *DP:* Using the equation *max(w + 1 - z, 0)*, iterate through the array and calculate the number of *waits* for the last `1`.
- The answer will be the the index of the last `1` minus the number of `1`s in our substring 's' plus number of *waits* of the last `1`.
THE END :>

**C++**
```
class Solution {
public:
    int secondsToRemoveOccurrences(std::string s) {
        
    }
};
```
**python3**
```
class Solution:
    def secondsToRemoveOccurrences(self, s: str) -> int:
        
```
**Complexity**
- Time Complexity:*O(n)*

We take a substring and then iterate through it. Time complexity is *O(n)*, where n is length of the string.

- Space complexity: *O(n)*

*O(n)*, because we could have at max an array of the length `n-1`.
[Extra: it could be done in constant space]

# DP - constant extra space
