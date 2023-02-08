from timeit import default_timer as timer
import sys
import re

def main1(f):
    #pw = list('abcde')
    pw = list('abcdefgh')
    for line in f:
        line = line[:-1]
        print(f'pw : {pw }')
        print(f'line: {line}')
        lc = line[12]
        rc = line[-1]
        if line[:8] == 'swap let':
            ln = pw.index(lc)
            rn = pw.index(rc)
            swp = pw[ln]
            pw[ln] = pw[rn]
            pw[rn] = swp
        if line[:8] == 'swap pos':
            ln, rn = map(int, re.findall('\d', line))
            swp = pw[ln]
            pw[ln] = pw[rn]
            pw[rn] = swp
        if line[:8] == 'reverse ':
            ln, rn = map(int, re.findall('\d', line))
            pw[ln:rn+1] = reversed(pw[ln:rn+1])
        if line[:8] == 'move pos':
            ln, rn = map(int, re.findall('\d', line))
            c = pw[ln]
            del pw[ln]
            pw.insert(rn,c)
        if line[:8] == 'rotate b':
            i = pw.index(rc)
            if i >= 4:
                i += 1
            for _ in range(i+1):
                pw.insert(0, pw.pop())
        if line[:8] == 'rotate l':
            ln, = map(int, re.findall('\d', line))
            for _ in range(ln):
                pw.append(pw.pop(0))
        if line[:8] == 'rotate r':
            ln, = map(int, re.findall('\d', line))
            for _ in range(ln):
                pw.insert(0, pw.pop())

        print(f'pw : {pw }')
        print()
    

    return ''.join(pw)


def main2(f):
    pw = list('fbgdceah')
    ops = reversed(list(line[:-1] for line in f))
    for line in ops:
        print(f'pw : {pw }')
        print(f'line: {line}')
        lc = line[12]
        rc = line[-1]
        if line[:8] == 'swap let':
            ln = pw.index(lc)
            rn = pw.index(rc)
            swp = pw[ln]
            pw[ln] = pw[rn]
            pw[rn] = swp
        if line[:8] == 'swap pos':
            ln, rn = map(int, re.findall('\d', line))
            swp = pw[ln]
            pw[ln] = pw[rn]
            pw[rn] = swp
        if line[:8] == 'reverse ':
            ln, rn = map(int, re.findall('\d', line))
            pw[ln:rn+1] = reversed(pw[ln:rn+1])
        if line[:8] == 'move pos':
            ln, rn = map(int, re.findall('\d', line))
            c = pw[rn]
            del pw[rn]
            pw.insert(ln,c)
        if line[:8] == 'rotate b':
            backrot = {0:-1, 6:0, 4:1, 2:2, 7:-4, 5:-3, 3:-2, 1:-1}
            i = pw.index(rc)
            rot = backrot[i]
            if rot > 0:
                for _ in range(rot):
                    pw.insert(0, pw.pop())
            else:
                for _ in range(-rot):
                    pw.append(pw.pop(0))
        if line[:8] == 'rotate l':
            ln, = map(int, re.findall('\d', line))
            for _ in range(ln):
                pw.insert(0, pw.pop())
        if line[:8] == 'rotate r':
            ln, = map(int, re.findall('\d', line))
            for _ in range(ln):
                pw.append(pw.pop(0))

        print(f'pw : {pw }')
        print()
    

    return ''.join(pw)


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
