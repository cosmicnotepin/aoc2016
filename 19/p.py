from timeit import default_timer as timer
import sys
from collections import deque

def main1(f):
    elf_count = int(f.read())
    print(f'elf_count : {elf_count }')
    table = deque([[i, 1] for i in range(elf_count)])
    i = 0;
    while len(table) > 1:
        table[0][1] += table[1][1]
        del table[1]
        table.rotate(-1)
    
    return str(table[0][0] + 1)


def main2(f):
    elf_count = int(f.read())
    print(f'elf_count : {elf_count }')
    table_l = deque([[i, 1] for i in range(elf_count//2)])
    table_r = deque([[i, 1] for i in range(elf_count//2, elf_count)])
    i = 0;
    while (ll := len(table_l)) > 0 and (lr := len(table_r)) > 0:
        if ll == 1 and lr == 1:
            return str(table_l[0][0] + 1)
        if lr >= ll:
            table_l[0][1] += table_r.popleft()[1]
        else:
            table_l[0][1] += table_l.pop()[1]

        table_l.append(table_r.popleft())
        table_r.append(table_l.popleft())
    
    return "blah"


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
