from timeit import default_timer as timer

def main1(f):
    line = f.read()

    return ""


def main2(f):
    line = f.read()

    return ""


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
