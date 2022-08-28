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