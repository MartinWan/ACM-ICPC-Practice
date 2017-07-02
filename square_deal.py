from fileinput import input

# https://open.kattis.com/problems/squaredeal

def validSquare(W, H):
    return 'YES' if W == H else 'NO'

rectangles = []

for line in input():
  d1, d2 = line.split()
  d1 = int(d1)
  d2 = int(d2)

  R = sorted((d1, d2), reverse=True) # (Width, Height) where Width is the larger dimension
  rectangles.append(R)


rectangles.sort(key=lambda R: R[0]) # sort by width
w1, h1 = rectangles.pop()
w2, h2 = rectangles.pop()
w3, h3 = rectangles.pop()

if w1 == w2 and w2 == w3: # stackable
  if w1 == h1 + h2 + h3:
      print 'YES'
  else:
      print 'NO'
else: # not stackable, try fitting 
    if w1 == w2 + w3:
        if h2 == h3:
          print validSquare(w1, h1 + h2)
        else:
          print 'NO'
    elif w1 == w2 + h3:
        if h2 == w3:
          print validSquare(w1, h1 + h2)
        else:
          print 'NO'
    elif w1 == h2 + h3:
        if w2 == w3:
          print validSquare(w1, h1 + w2)
        else:
          print 'NO'
    elif w1 == h2 + w3:
        if w2 == h3:
          print validSquare(w1, h1 + w2)
        else: 
          print 'NO'
    else:
        print 'NO'

