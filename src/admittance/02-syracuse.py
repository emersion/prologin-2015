#!/usr/bin/env python3


def syracuse(u0, k):
    u = u0
    for i in range(k):
    	if u % 2 == 0:
    		u = u // 2
    	else:
    		u = u*3 + 1
    return u

if __name__ == '__main__':
    u0 = int(input())
    k = int(input())
    print(syracuse(u0, k))