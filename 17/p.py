from timeit import default_timer as timer
import sys
from hashlib import md5

def bfs (x, y, path, f, part2):
    salt = f.read().strip()
    doors = {'U': (0,-1), 'D': (0,1), 'L': (-1,0), 'R': (1,0)}
    todo = [(x,y,path)]
    m_pth_len = 0
    while len(todo) > 0:
        x,y,pth = todo.pop(0)
        hsh = md5((salt + pth).encode('utf-8')).hexdigest()
        for (key,(xc, yc)), hshc in zip(doors.items(), hsh):
            if not (hshc in 'bcdef'):
                continue
            xn = x + xc;
            yn = y + yc;
            if xn == 3 and yn == 3:
                if part2:
                    m_pth_len = max(m_pth_len, len(pth) + 1)
                    continue
                else:
                    return pth+key

            if not (0<=xn<=3) or not (0<=yn<=3):
                continue
            todo.append((xn,yn,pth+key))

    return str(m_pth_len)


def main1(f):
    return bfs(0,0,'', f, False)


def main2(f):
    return bfs(0,0,'', f, True)


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
