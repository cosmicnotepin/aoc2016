#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(ifstream ifs)
{
    unordered_map<char, long long int> regs 
    {{'a', 0}, {'b', 0}, {'c', 1}, {'d', 0}};
    vector<string> prog;
    for (string line; getline(ifs, line);) {
        prog.push_back(line);
    }
    size_t pc = 0;
    while (pc<prog.size()) {
        string cl = prog[pc];
        int val1, val2;
        char reg1, reg2;
        switch (cl[0]) {
            case 'i':
                sscanf(cl.c_str(), "%*s %c", &reg1);
                ++regs[reg1];
                ++pc;
                break;
            case 'd':
                sscanf(cl.c_str(), "%*s %c", &reg1);
                --regs[reg1];
                ++pc;
                break;
            case 'c':
                if (sscanf(cl.c_str(), "%*s %d %c", &val1, &reg2))
                    regs[reg2] = val1;
                else if (sscanf(cl.c_str(), "%*s %c %c", &reg1, &reg2))
                    regs[reg2] = regs[reg1];
                ++pc;
                break;
            case 'j':
                if (sscanf(cl.c_str(), "%*s %d %d", &val1, &val2)) {
                    if (val1 != 0)
                        pc += val2;
                    else
                        ++pc;
                }
                else if (sscanf(cl.c_str(), "%*s %c %d", &reg1, &val2)) {
                    if (regs[reg1] != 0)
                        pc += val2;
                    else
                        ++pc;
                }
                break;
        }
    }
    return to_string(regs['a']);
}

string run2(ifstream ifs)
{
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
