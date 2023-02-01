from timeit import default_timer as timer
import sys
import re
from math import prod

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def chin_rem(f, part2):
    ais = []
    mis = []
    for line in f:
        no, mi, t, pos = map(int, (re.findall('\d+', line)))
        ais.append((mi - pos-no)%mi)
        mis.append(mi)

    if part2:
        ais.append((11 - 0 - (len(ais)+1))%11)
        mis.append(11)

    M = prod(mis)
    Mis = [M//m for m in mis]
    siMis = [egcd(mi, Mi)[2] * Mi for mi,Mi in zip(mis, Mis)]
    t = sum(ai*siMi for ai, siMi in zip(ais, siMis)) % M

    return str(t)

def main1(f):
    return chin_rem(f, False)
    ais = []
    mis = []
    wheels = []
    for line in f:
        no, mi, t, pos = map(int, (re.findall('\d+', line)))
        wheels.append((no, mi, t, pos))
        ais.append((mi - pos-no)%mi)
        mis.append(mi)

    M = prod(mis)
    Mis = [M//m for m in mis]
    siMis = [egcd(mi, Mi)[2] * Mi for mi,Mi in zip(mis, Mis)]
    t = sum(ai*siMi for ai, siMi in zip(ais, siMis)) % M

    return str(t)


def main2(f):
    return chin_rem(f, True)


def main():
    funs = (main1, main2)
    start = timer()
    with open(sys.argv[2], "r") as f:
        res = funs[int(sys.argv[1])-1](f)
    end = timer()
    print('result: ' + res)
    print("time: " + f'{end - start:3.6f}')

if __name__ == "__main__":
    main()
