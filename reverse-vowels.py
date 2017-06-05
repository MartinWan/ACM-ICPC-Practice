'''
Problem: https://leetcode.com/problems/reverse-vowels-of-a-string/#/description
Runtime: 68ms
'''

class Solution(object):
    def reverseVowels(self, s):
        """
        :type s: str
        :rtype: str
        """
        s = list(s)
        vowels = set('aeiouAEIOU')
        v = [i for i, c in enumerate(s) if c in vowels]
        
        n = len(v)
        for i in range(n / 2):
            j = n - i - 1
            s[v[i]], s[v[j]] = s[v[j]], s[v[i]]
        
        return ''.join(s)