from timeit import default_timer as timer
from hashlib import md5

def  main1(filename):
    with open(filename, "r") as f:
        line = f.read()

    for i in range(999999999):
        hsh = md5((line.strip() + str(i)).encode('utf-8')).hexdigest()
        if hsh[:5] == "00000":
            return str(i)

    return ""


def  main2(filename):
    with open(filename, "r") as f:
        line = f.read()
    for i in range(999999999):
        hsh = md5((line.strip() + str(i)).encode('utf-8')).hexdigest()
        if hsh[:6] == "000000":
            return str(i)

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
