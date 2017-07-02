from fileinput import input

namespace = dict()

for line in input():
    tokens = line.split()

    if tokens[0] == 'define':
      value = int(tokens[1])
      symbol = tokens[2]
      namespace[symbol] = value
    else: # tokens[0] == 'eval'
      symbol1 = tokens[1]
      op = tokens[2]
      symbol2 = tokens[3]

      if symbol1 not in namespace or symbol2 not in namespace:
          print 'undefined'
      else:
          if op == '<':
              output = namespace[symbol1] < namespace[symbol2]
          elif op == '>':
              output = namespace[symbol1] > namespace[symbol2]
          else: # op is =
              output = namespace[symbol1] == namespace[symbol2]
          
          print str(output).lower() # convert True into true

