'''
Prolem: https://open.kattis.com/problems/triangle
Runtime: 0.03 s
'''

from math import log10
from fileinput import input


def solution(i):
  # Each iteration tripples the number of triangles
  # Each iteration halves the length of the triangles
  # 
  # From that we can derive the following ...
  return int((i + 1) * log10(3) - i * log10(2)) + 1


for i, line in enumerate(input()):
  print 'Case {}: {}'.format(i + 1, solution(int(line)))

