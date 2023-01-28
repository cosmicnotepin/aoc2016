from timeit import default_timer as timer
import sys
import re
from copy import deepcopy
from itertools import combinations

gen_pat = re.compile('(\S+) generator')
mic_pat = re.compile('(\S+)-compatible')

def parse(f, part2):
    gens = {}
    mics = {}
    for floor, line in enumerate(f):
        for mic in mic_pat.findall(line):
            mics[mic] = floor
        for gen in gen_pat.findall(line):
            gens[gen] = floor

    stuff = []
    for key, value in mics.items():
        stuff.append(list((value, gens[key])))

    if part2:
        stuff.extend([[0,0], [0,0]])

    return [0, 0, list(sorted(stuff))]


def safe(fs):
    for m,g in fs:
        if m == g:
            continue
        if m in (g for _,g in fs):
            return False
    return True


def bfs(state):
    visited = set()
    todo = [state]
    while len(todo) > 0:
        state = todo.pop(0)
        for fc in [fc for fc in [1,-1] if 0<=state[1]+fc<=3]:
            iof = [(i,t) for i in range(len(state[2])) for t in range(2)
                    if state[2][i][t] == state[1]]
            for cb in list(combinations(iof, 2)) + [[e] for e in iof]:
                sc = deepcopy(state)
                sc[0] += 1
                sc[1] += fc
                for c in cb:
                    sc[2][c[0]][c[1]] += fc
                sc[2] = sorted(sc[2])
                sc_tuple = tuple([sc[1], tuple(tuple(i) for i in sc[2])])
                if safe(sc[2]) and not (sc_tuple in visited):
                    if all(sc[2][i] == [3,3] for i in range(len(sc[2]))):
                        return sc[0]
                    visited.add(sc_tuple)
                    todo.append(sc)
    return "nothing"

def main1(f):
    state = parse(f, False)
    return str(bfs(state))


def main2(f):
    state = parse(f, True)
    return str(bfs(state))


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
