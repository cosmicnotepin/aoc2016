from timeit import default_timer as timer

def main1(f):
    line = f.read()

    return ""


def main2(f):
    line = f.read()

    return ""


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
