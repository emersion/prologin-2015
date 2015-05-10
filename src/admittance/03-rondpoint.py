#!/usr/bin/env python3

import math

def vect(a, b):
    return (b[0] - a[0], b[1] - a[1])

def dist(a, b):
    return math.sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

def norm(v):
    return math.sqrt(v[0]**2 + v[1]**2)

def rondpoint(x, y, n, sorties):
    centre = (x, y)

    entree = sorties[0]
    u = vect(centre, entree)
    a = norm(u)

    shortestAngle = 2 * math.pi
    shortest = -1

    i = 1
    for s in sorties[1:]:
        v = vect(centre, s)
        b = norm(v)

        scalar = u[0] * v[0] + u[1] * v[1]
        det = u[0] * v[1] - u[1] * v[0]

        angle = math.acos(scalar / (a*b))
        angle = math.copysign(angle, det)

        if angle > 0 and angle < shortestAngle:
            shortestAngle = angle
            shortest = i

        i += 1

    return sorties[shortest]

if __name__ == "__main__":
    x, y = tuple(map(int, input().split()))
    n = int(input())
    sorties = [tuple(map(int, input().split())) for _ in range(n)]
    print("%d %d" % rondpoint(x, y, n, sorties))