from timeit import default_timer as timer
import sys

def space_f(fav):
    def space(x,y):
        return bin(x*x + 3*x + 2*x*y + y + y*y + fav).count('1') % 2 == 0
    return space


def pm(space):
    for y in range(40):
        for x in range(40):
            if space(x,y):
                print('.', end='')
            else:
                print('#', end='')
        print()

def bfs(space, part2, t_x, t_y):
    n_os = [(0,1), (0,-1), (1,0), (-1,0)]
    todo = [(1,1,0)]
    visited = set()
    while len(todo) > 0:
        x,y,p_l = todo.pop(0)

        if part2 and p_l == 51:
            return str(len(visited))
        
        if not part2 and x==t_x and y == t_y:
            return str(p_l)

        visited.add((x,y))
        for x_o, y_o in n_os:
            n_x = x + x_o
            n_y = y + y_o
            if n_x < 0 or n_y < 0 \
               or not space(n_x,n_y) or (n_x, n_y) in visited:
                continue
            todo.append((n_x, n_y, p_l+1))


def main1(f):
    fav, t_x, t_y = map(int, f.readlines())
    space = space_f(fav)
    pm(space)

    return bfs(space, False, t_x, t_y)


def main2(f):
    fav, t_x, t_y = map(int, f.readlines())
    space = space_f(fav)
    pm(space)

    return bfs(space, True, t_x, t_y)


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
