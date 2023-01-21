from timeit import default_timer as timer

def main1(filename):
    keypad = [['1','2','3'],
              ['4','5','6'],
              ['7','8','9']]
    pos = 1 + 1j
    instr = {'U': 0 -1j, 'D': 0 + 1j, 'L': -1, 'R': 1}
    code = ''
    with open(filename, "r") as f:
        for line in f:
            for c in line.strip():
                pos_n = pos + instr[c]
                pos = max(0, min(2, pos_n.real)) \
                    + max(0, min(2, pos_n.imag)) * 1j
            code += keypad[int(pos.imag)][int(pos.real)]

    return code


def main2(filename):
    keypad = [['0','0','1','0','0',],
              ['0','2','3','4','0'],
              ['5','6','7','8','9'],
              ['0','A','B','C','0'],
              ['0','0','D','0','0',]]
    instr = {'U': 0 -1j, 'D': 0 + 1j, 'L': -1, 'R': 1}
    code = ''
    pos = 2j
    with open(filename, "r") as f:
        for line in f:
            for c in line.strip():
                pos_n = pos + instr[c]
                if abs(2-pos_n.real) + abs(2-pos_n.imag) > 2:
                    continue
                pos = pos_n
            code += keypad[int(pos.imag)][int(pos.real)]

    return code


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
