#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <algorithm>
#include <set>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


struct Bot {
    set<int> chips;
    int targets[2];
};


string run1(ifstream ifs)
{
    int search[2] = {61,17};
    unordered_map<int, Bot> bots;
    for (string line; getline(ifs, line);) {
        unsigned int x,y,z;
        char lc, hc;
        if (sscanf(line.c_str(), "value %d goes to bot %d", &x, &y)) {
            bots[y].chips.insert(x);
        }else if (sscanf(line.c_str(), 
                "bot %d gives low to %c%*s %d and high to %c%*s %d",
                &x, &lc, &y, &hc, &z)) {
            bots[x].targets[0] = lc == 'o' ? -y-1 : y;
            bots[x].targets[1] = hc == 'o' ? -z-1 : z;
        }
    }
    while(true) {
        for (auto botpair : bots) {
            auto bot = botpair.second;
            if (bot.chips.size() < 2)
                continue;

            if (bot.chips.contains(search[0]) && bot.chips.contains(search[1]))
                    return to_string(botpair.first);

            auto chip_it = bot.chips.begin();
            for (auto t : bot.targets)
                bots[t].chips.insert(*(chip_it++));
        }
    }
    
    return to_string(0);
}

string run2(ifstream ifs)
{
    unordered_map<int, Bot> bots;
    unordered_map<int, vector<int>> outputs;
    for (string line; getline(ifs, line);) {
        unsigned int x,y,z;
        char lc, hc;
        if (sscanf(line.c_str(), "value %d goes to bot %d", &x, &y)) {
            bots[y].chips.insert(x);
        }else if (sscanf(line.c_str(), 
                    "bot %d gives low to %c%*s %d and high to %c%*s %d",
                    &x, &lc, &y, &hc, &z)) {
            bots[x].targets[0] = lc == 'o' ? -y-1 : y;
            bots[x].targets[1] = hc == 'o' ? -z-1 : z;
        }
    }
    while(true) {
        for (auto botpair : bots) {
            auto bot = botpair.second;
            if (bot.chips.size() < 2)
                continue;

            auto chip_it = bot.chips.begin();
            for (auto t : bot.targets)
                if (t >=0)
                    bots[t].chips.insert(*(chip_it++));
                else
                    outputs[-t-1].push_back(*(chip_it++));
            bot.chips.clear();
        }
        if (outputs[0].size() > 0 &&
                outputs[1].size() > 0 &&
                outputs[2].size() > 0)
            break;
    }
    return to_string(outputs[0][0] * outputs[1][0] * outputs[2][0]);
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
