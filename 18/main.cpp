#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(ifstream ifs)
{
    size_t rows = 400000;
    string line;
    getline(ifs, line);
    line.insert(line.begin(), '.');
    line.insert(line.end(), '.');
    vector<string> lines {line,};
    while (--rows) {
        auto cur = lines[lines.size() -1];
        string next {"."};
        for (size_t i=1; i<cur.size()-1; ++i) {
            auto l = cur[i-1] == '^';
            auto r = cur[i+1] == '^';
            if (l != r)
                    next.push_back('^');
            else
                next.push_back('.');
        }
        next.push_back('.');
        lines.push_back(next);
    }
    size_t ret = 0;
    for (auto l : lines) {
        for (size_t i=1; i<l.size()-1; ++i) {
            ret += l[i] == '.';
        }
    }

    return to_string(ret);
}
//Bitwise using 128-bit integers in C. Compile with -march=native
//
int solve(__uint128_t traps, __uint128_t mask, int rows)
{
    int n_safe = 0;
    while (rows--) {
        n_safe += __builtin_popcountl((uint64_t) ((mask ^ traps) >> 64));
        n_safe += __builtin_popcountl((uint64_t)  (mask ^ traps));
        traps = (traps << 1) ^ (traps >> 1);
        traps &= mask;
    }
    return n_safe;
}

string run2(ifstream ifs)
{
    string line;
    getline(ifs, line);
    __uint128_t traps = 0, mask = 0;

    for (auto c : line) {
        traps = (traps << 1) | (c == '^');
        mask  = (mask  << 1) | 1;
    }
    printf("Part 2: %d\n", solve(traps, mask, 400000));

    return to_string(0);
}

int main(int argc, char** argv)
{
    string (*funs[])(ifstream) = {&run1, &run2};
    auto start = chrono::steady_clock::now();
    auto res = funs[atoi(argv[1])-1](ifstream {argv[2]});
    auto end = chrono::steady_clock::now();
    chrono::duration<double> time_s = end-start;
    cout<<"result: "<<res<<'\n';
    cout<<fixed;
    cout.precision(6);
    cout<<"time: "<<time_s.count()<<'\n';
}
