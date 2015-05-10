#!/usr/bin/env python3


def triangles(n):
    pts = 0
    while n > 0:
    	pts += n
    	n -= 1
    return pts


if __name__ == '__main__':
    print(triangles(int(input())))