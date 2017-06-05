'''
Problem: https://open.kattis.com/problems/addingwords
Runtime: 0.12 s
'''

from fileinput import input


namespace = {}
valuespace = {}


def plus(x, y):
  if x == 'unknown' or y == 'unknown':
    return 'unknown'
  return x + y


def minus(x, y):
  if x == 'unknown' or y == 'unknown':
    return 'unknown'
  return x - y


def none(x, y):
	return y


def calculate(tokens):
  op = none
  result = 0
  output = []
  for t in tokens:
    if t == '+':
      op = plus
      output.append(t)
    elif t == '-':
      op = minus
      output.append(t)
    elif t == '=':
      output.append('=')
      output.append(valuespace.get(result, 'unknown'))
    else: # symbolname
     output.append(t) 
     result = op(result, namespace.get(t, 'unknown'))
     
  return " ".join([ str(o) for o in output])


for line in input():
  tokens = line.split()  
  cmd = tokens[0]
  
  if cmd == 'def':
    symbol = tokens[1]
    value = int(tokens[2])
    
    if value in valuespace:
      del namespace[valuespace[value]]
      del valuespace[value]
    if symbol in namespace:
      del valuespace[namespace[symbol]] 
      del namespace[symbol]
      
    namespace[symbol] = value
    valuespace[value] = symbol
  elif cmd == 'calc':
    print calculate(tokens[1:])
  else: # clear
    namespace = {}
    valuespace = {}
 
