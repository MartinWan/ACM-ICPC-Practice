from fileinput import input

# https://open.kattis.com/problems/evenodd

L, R = next(input()).split()
L = int(L)
R = int(R)

def f(x):
    i = 0
    while x != 1:
        if x % 2 == 0:
            x /= 2
        else:
            x += 1
        i += 1
    return i

def S(L, R):
    if L == R:
        return f(L)

    if L == 1:
        return S(L+1, R)

    if L % 2 == 0:
        return S(L+1, R) + f(L)

    if R % 2 == 1:
        return S(L, R-1) + f(R)

    return 2*S((L+1)/2, R/2) + 3*(R-L+1)/2


print S(L, R) % (10**9 + 7)

    

    


