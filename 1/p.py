from timeit import default_timer as timer

def main1(filename):
    with open(filename, "r") as f:
        dirs = f.read().split(', ')

    facing = 0 -1j
    pos = 0 + 0j
    visited = set()
    visited.add(pos)
    for d in dirs:
        if d[0] == 'L':
            facing *= 1j
        else:
            facing *= -1j

        for _ in range(int(d[1:])):
            pos += facing
            if pos in visited:
                return  str(int(abs(pos.real) + abs(pos.imag)))
            visited.add(pos)

    return  ""


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
