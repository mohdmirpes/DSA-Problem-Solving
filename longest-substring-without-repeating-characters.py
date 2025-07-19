class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max=1
        lstring=[]
        for k in range(1,len(s)-1,1):
            lstring.append(s[k])
            for x in range(k+1,len(s),1):
                if s[x] not in lstring:
                    lstring.append(s[x])
                else:
                    count=len(lstring)
                    if max<count:
                        max=count
                    break
            lstring.clear()
        return max


        