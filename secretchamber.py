'''
Problem: https://open.kattis.com/problems/secretchamber
Runtime: 0.18 seconds
'''

from fileinput import input


def dfs(c1, c2, translation, visited):
  if c1 == c2:
    return True
  if c1 in visited:
    return False

  visited.add(c1)
  for t in translation.get(c1, []):
    if dfs(t, c2, translation, visited):
      return True

  return False


def possible(word1, word2, translation):
  if len(word1) != len(word2):
    return 'no'
  
  for c1, c2 in zip(word1, word2):
    if not dfs(c1, c2, translation, set()):
      return 'no'
  return 'yes'


lines = list(input())

m, n = lines[0].split()
m = int(m)
n = int(n)

translation = dict()
for l in lines[1: m + 1]:
  x, y = l.split()
  translation.setdefault(x, []).append(y)


for words in lines[m + 1: m + 1 + n + 1]:
 w1, w2 = words.split()
 print possible(w1, w2, translation)

   
