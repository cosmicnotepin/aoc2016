from timeit import default_timer as timer
import sys
import re

pat = re.compile(r'\((\d+)x(\d+)\)')

def main1(f):
    line = f.read().strip()
    i = 0
    res = ''
    while m := re.search(pat,line[i:]):
        res += line[i:i+m.start()]
        for _ in range(int(m[2])):
            res += line[i+m.end():i+m.end()+int(m[1])]
        i = i + m.end() + int(m[1])

    res += line[i:]

    return str(len(res))


def reclen(line):
    if not (m := re.search(pat, line)):
        return len(line)
    res = m.start()
    res += int(m[2]) * reclen(line[m.end(): m.end() + int(m[1])])
    res += reclen(line[m.end() + int(m[1]):])
    return res


def main2(f):
    return str(reclen(f.read().strip()))


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
