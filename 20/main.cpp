#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <limits>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(ifstream ifs)
{
    vector<array<unsigned int, 2>> bounds;
    for (string line; getline(ifs, line);) {
        unsigned int l,u;
        sscanf(line.c_str(), "%u-%u", &l, &u);
        bounds.push_back({l, u});
    }
    ranges::sort(bounds, [](const auto lhs, const auto rhs)
            {return lhs[0] < rhs[0];});

    unsigned int lowest = 0;
    auto [l, u] = bounds[0];
    if (lowest < l)
        return to_string(lowest);
    size_t i = 1;
    while (bounds[i][0] <= u + 1)
        u = max(u, bounds[i++][1]);
    return to_string(u+1);
}

string run2(ifstream ifs)
{
    unsigned int highest = numeric_limits<unsigned int>::max();
    vector<array<unsigned int, 2>> bounds;
    for (string line; getline(ifs, line);) {
        unsigned int l,u;
        sscanf(line.c_str(), "%u-%u", &l, &u);
        bounds.push_back({l, u});
    }
    ranges::sort(bounds, [](const auto lhs, const auto rhs)
            {return lhs[0] < rhs[0];});

    unsigned int count = 0;
    unsigned int u=0;
    string blah;
    for (auto [cl,cu] : bounds) {
        if (cl <= u + 1)
            u = max(u, cu);
        else {
            count += cl - u - 1;
            u = cu;
        }
        if (u == highest)
            break;
    }
    if (u != highest)
        count += highest - u;
    return to_string(count);
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
