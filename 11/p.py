from timeit import default_timer as timer
import sys
import re
from copy import deepcopy
from itertools import combinations
from collections import defaultdict

gen_pat = re.compile('(\S+) generator')
mic_pat = re.compile('(\S+)-compatible')

no_mics = 0
no_mics_ones = 0
two_mics_ones = 0

def bitf(floor):
    return floor*2*no_mics

def bitm(m,floor):
    return m+bitf(floor)

def bitg(g,floor):
    return bitm(g,floor) + no_mics

def m(state, i, floor):
    return state[2] & 1<<bitm(i, floor)

def g(state, i, floor):
    return state[2] & 1<<bitg(i, floor)


def pp(state):
    for f in range(4):
        for i in range(no_mics):
            mic = str(int(state[2] & 1<<bitm(i,f) > 0))
            gen = str(int(state[2] & 1<<bitg(i,f) > 0))
            print(mic + "," + gen, end='  ')
        if state[1] == f:
            print("#", end='')

        print()


def safe(state):
    for floor in range(4):
        if not state[2] & no_mics_ones << bitg(0,floor):
            continue
        if any(m(state, i, floor) and not g(state, i,floor)
                for i in range(no_mics)):
            return False

    return True


def combis(state):
    items = [1<<i for i in range(no_mics*2) 
            if state[2] & 1<<(bitf(state[1])+i)]
    return items + [a+b for a,b in combinations(items,2)]


best_steps = 9999999
visited = defaultdict(lambda:9999999)

def dfs(state):
    if visited[tuple(state[1:])] < state[0]:
        return
    visited[tuple(state[1:])] = state[0]
    pp(state)
    global best_steps
    print(f'best_steps : {best_steps }')
    if best_steps < state[0]:
        print("skipping")
        return

    print(bin(two_mics_ones << bitf(3)))
    print(bin(state[2]))
    print(bin(two_mics_ones << bitf(3) & state[2]))
    if (two_mics_ones << bitf(3)) & state[2] == two_mics_ones << bitf(3):
        print("found one solution")
        best_steps = min(state[0], best_steps)


    for tf in [f for f in [state[1] + 1, state[1] -1] if 0<=f<=3]:
        print(f'tf : {tf }')
        print(f'combis(state): {combis(state)}')
        for cb in combis(state):
            print(f'cb : {cb }')
            sc = state.copy()
            sc[0] += 1
            sc[1] = tf
            sc[2] |= cb << bitf(tf)
            sc[2] &= ~(cb << bitf(state[1]))
            print('iiiiiiiiiiiiiiiiiiii')
            pp(state)
            pp(sc)
            print('iiiiiiiiiiiiiiiiiiii')
            if safe(sc):
                print("doing smth")
                dfs(sc)


def main1(f):
    gens = {}
    mics = {}
    for floor, line in enumerate(f):
        for mic in mic_pat.findall(line):
            mics[mic] = floor
        for gen in gen_pat.findall(line):
            gens[gen] = floor

    #[steps, elev, poss]
    global no_mics, no_mics_ones, two_mics_ones
    no_mics = len(mics)
    no_mics_ones = (2**no_mics -1)
    two_mics_ones = (2**(2*no_mics) -1)
    state = [0, 0, 0]
    for i, (key, value) in enumerate(mics.items()):
        state[2] |= 1<<bitm(i, value)
        state[2] |= 1<<bitg(i, gens[key])


    #for i in range(no_mics):
    #    state[2] |= 1<<bitg(i, 3)
    #    state[2] |= 1<<bitm(i, 3)
    dfs(state)
    return str(best_steps)


def main2(f):
    line = f.read()

    return ""


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
