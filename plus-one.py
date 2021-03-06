'''
Problem: https://leetcode.com/problems/plus-one/#/description
Runtime: 39 ms
'''

class Solution(object):
    def plusOne(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        i = len(digits) - 1
        carry = 1
        while i >= 0:
            digits[i] += carry
            carry, digits[i] = divmod(digits[i], 10)
            i -= 1
        
        if carry != 0:
            digits.insert(0, carry)

        return digits