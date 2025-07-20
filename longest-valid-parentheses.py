class Solution:
    def longestValidParentheses(self, s: str) -> int:
        i=0
        count=0
        while i < len(s)-1:
            if s[i] is "(" and s[i+1] is ")":
                count+=2  
                i+=2
            else:
                i+=1
        return count

