#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>

using namespace std;
using Regs = unordered_map<string, int64_t>;
int64_t np;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct Instr;
unordered_map<string, void (Instr::*)()> name2func;

struct Instr {
    Instr(vector<Instr> & prog, int64_t * pc, string cmd_string) : pc{pc}, prog{prog}, cmd_string{cmd_string} {};
    Instr(const Instr& rhs) : cmd{rhs.cmd}, pc{rhs.pc}, prog{rhs.prog}, cmd_string{rhs.cmd_string}
    {
        for (size_t i=0; i<2; ++i) {
            if (rhs.args[i] == &rhs.argvs[i])
                args[i] = & argvs[i];
            else
                args[i] = rhs.args[i];
            argvs[i] = rhs.argvs[i];
        }
    };

    void (Instr::*cmd)();
    int64_t * pc;
    array<int64_t *, 2> args;
    array<int64_t, 2> argvs;
    vector<Instr> & prog;
    string cmd_string;

    void operator()()
    {
        (this->*(this->cmd))();
    }

    void inc()
    {
        ++*args[0];
        ++*pc;
    }


    void dec()
    {
        --*args[0];
        ++*pc;
    }
    void cpy()
    {
        if (args[1] != &argvs[1])
            *args[1] = *args[0];
        ++*pc;
    }
    void jnz()
    {
        if (*args[0] != 0)
            *pc += *(args[1]);
        else
            ++*pc;
    }
    void tgl()
    {
        static unordered_map<string, string> tgl_map {
            {"inc", "dec"},
                {"dec", "inc"},
                {"tgl", "inc"},
                {"cpy", "jnz"},
                {"jnz", "cpy"}};
        int64_t tgl_i = *pc + *args[0];
        if (tgl_i < 0 || tgl_i >= (int64_t) prog.size()) {
            ++*pc;
            return;
        }
        Instr & t_instr = prog[tgl_i];
        string new_cmd_string = tgl_map[t_instr.cmd_string];
        t_instr.cmd = name2func[new_cmd_string];
        t_instr.cmd_string = new_cmd_string;
        ++*pc;
    }
};


void init_instr(Regs & regs, Instr & instr, const string cmd, 
        vector<string> args)
{
    instr.cmd = name2func[cmd];
    for (size_t i = 0; i<args.size(); ++i) {
        auto & arg = args[i];
        if (regs.contains(arg))
            instr.args[i] = &regs[arg];
        else {
            instr.argvs[i] = stoi(arg);
            instr.args[i] = &(instr.argvs[i]);
        }
    }
}

string crack(int eggs, ifstream& ifs)
{
    name2func = { {"inc", &Instr::inc}, {"dec", &Instr::dec},
        {"cpy", &Instr::cpy}, {"jnz", &Instr::jnz},
        {"tgl", &Instr::tgl}};
    Regs regs {{"a", eggs}, {"b", 0}, {"c", 0}, {"d", 0}};
    vector<Instr> prog;
    int64_t pc = 0;
    for (string line; getline(ifs, line);) {
        char cmd[4];
        char lhs[4];
        char rhs[4];
        int count = sscanf(line.c_str(), "%s %s %s", cmd, lhs, rhs);
        vector<string> args {lhs};
        if (count == 3)
            args.push_back(rhs);
        Instr instr {prog, &pc, string(cmd)};
        init_instr(regs, instr, cmd, args);
        prog.push_back(Instr(instr));
    }

    while (pc<(int64_t)prog.size()) {
        prog[pc]();
    }
    return to_string(regs["a"]);
}

string run1(ifstream ifs)
{
    return crack(7, ifs);
}

string run2(ifstream ifs)
{
    return crack(12, ifs);
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
