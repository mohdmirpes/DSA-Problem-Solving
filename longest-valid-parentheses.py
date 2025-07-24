class Solution:
    def longestValidParentheses(self, s: str) -> int:
        max_len=0
        lst=[-1]
        for i,ch in enumerate(s):
            if ch == "(":
                lst.append(i)
            else:
                lst.pop()
                if not bool(lst):
                    lst.append(i)
                else:
                    max_len=max(max_len,i-lst[-1])
        return max_len