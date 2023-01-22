import re
from timeit import default_timer as timer
from itertools import chain
from collections import Counter
from functools import reduce
from operator import add
from string import ascii_lowercase

def main1(file):
    real_rooms_id_sum = 0
    for line in file:
        parts = line.strip().split('-')
        name = reduce(add, parts[:-1])
        counts = Counter(name)
        name_checksum = ''.join(sorted(list(counts.keys()), \
                key=lambda x:counts[x]*100 - ord(x), reverse=True))[:5]
        sect_id, checksum = parts[-1].split('[')
        checksum = checksum[:-1]
        if name_checksum == checksum:
            real_rooms_id_sum += int(sect_id)

    return str(real_rooms_id_sum)


def get_trans(count):
    shift = count % 26
    az = ascii_lowercase
    return str.maketrans(az+'-', az[shift:] + az[:shift]+' ')


def main2(file):
    pat = re.compile(r'([a-z-]+)(\d+)\[(\w+)\]')
    for name, sect_id, checksum in pat.findall(file.read()):
        counts = Counter(name.replace('-', ''))
        name_checksum = ''.join(sorted(list(counts.keys()), \
                key=lambda x:-counts[x]*100 + ord(x)))[:5]
        if name_checksum == checksum:
            room_name_decr = name.translate(get_trans(int(sect_id)))
            if ('pole' in room_name_decr):
                print(sect_id + ' : ' + room_name_decr)

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
