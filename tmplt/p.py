from timeit import default_timer as timer

def main1(filename):
    with open(filename, "r") as f:
        line = f.read()

    return ""


def main2(filename):
    with open(filename, "r") as f:
        line = f.read()

    return ""


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
