from fileinput import *

def solution(n):
  return n + max(n - 2, 0)

for line in input():
  print solution(int(line))
