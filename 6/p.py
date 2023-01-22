from timeit import default_timer as timer
from collections import Counter

def main1(f):
    inp = f.readlines()
    message = ''.join(Counter(pos).most_common()[0][0] for pos in zip(*inp))
    return message


def main2(f):
    inp = f.readlines()
    message = ''.join(Counter(pos).most_common()[-1][0] for pos in zip(*inp))
    return message


def main():
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            with open(inp, "r") as f:
                res = fun(f)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')

if __name__ == "__main__":
    main()
