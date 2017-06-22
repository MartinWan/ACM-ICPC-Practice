from fileinput import input

def solution(words):
  words.sort(key=lambda w: w[::-1])
  maxWord = max(len(w) for w in words)
  for w in words:
    print ' ' * (maxWord-len(w)) + w

groups = []
words = []
for line in list(input()) + [' ']:
  if line.isspace():
    groups.append(words)
    words = []
  else:
    words.append(line.strip())

for i, group in enumerate(groups):
  solution(group)
  if i != len(groups) - 1: # if not at end print group separator
    print ''
