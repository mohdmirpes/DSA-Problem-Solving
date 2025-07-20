class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max=0
        lstring=[]
        for k in range(0,len(s),1):
            lstring.append(s[k])
            for x in range(k+1,len(s),1):
                if s[x] not in lstring:
                    lstring.append(s[x])
                else:
                    break
            count=len(lstring)
            if max<count:
                max=count
            lstring.clear()
        return max


        