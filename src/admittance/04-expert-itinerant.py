#!/usr/bin/env python3

def path(N, D, A, T, d, a):
    times = [False] * N
    times[d - 1] = 0

    while 1:
        changed = False
        for i in range(len(D)):
            streetFrom = D[i]
            streetTo = A[i]
            streetTime = T[i]

            fromTime = times[streetFrom - 1]
            toTime = times[streetTo - 1]
            if fromTime is False:
                continue

            travelTime = fromTime + streetTime

            if toTime is False or toTime > travelTime:
                times[streetTo - 1] = travelTime
                changed = True

        if not changed:
            break

    return times[a - 1]


def expert_itinerant(N, M, R, D, A, T, d, a):
    for i in range(len(d)):
        print(path(N, D, A, T, d[i], a[i]))

if __name__ == '__main__':
    N, M, R = (int(i) for i in input().split())

    D = []
    A = []
    T = []
    for _ in range(M):
        my_D, my_A, my_T = (int(i) for i in input().split())
        D.append(my_D)
        A.append(my_A)
        T.append(my_T)

    d = []
    a = []
    for _ in range(R):
        my_d, my_a = (int(i) for i in input().split())
        d.append(my_d)
        a.append(my_a)

    expert_itinerant(N, M, R, D, A, T, d, a)