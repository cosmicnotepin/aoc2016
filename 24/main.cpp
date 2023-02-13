#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <valarray>
#include <map>
#include <deque>
#include <limits>

#include <algorithm>


using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

vector<vector<int>> get_dists(map<int, valarray<int>> targets,
        vector<string> ducts)
{
    // [[00, 01, ... ,0n], [10, 11, ... 1n], ... [n0, n1, ... nn]]
    vector<vector<int>> dists (targets.size(), vector<int>(targets.size()));

    //bfs for every target to find distances to all other targets:
    //[[x,y,dist], [x,y,dist], ... ]
    array<valarray<int>, 4> neighs {{{0, -1, 1}, {1, 0, 1},
                                     {0, 1, 1}, {-1, 0, 1}}};
    for (auto [key, coords] : targets) {
        deque<valarray<int>> todo {{coords[0], coords[1], 0}};
        vector<vector<bool>> visited(ducts.size(), 
                vector<bool> (ducts[0].size()));
        visited[coords[1]][coords[0]] = true;
        while (todo.size()) {
            size_t found = 0;
            auto cur = todo.front();
            todo.pop_front();
            for (auto no : neighs) {
                auto n = cur + no;
                auto ducts_n = ducts[n[1]][n[0]];
                if (visited[n[1]][n[0]] == true || ducts_n == '#')
                    continue;
                if (ducts_n != '.') {
                    dists[key][ducts_n - '0'] = n[2];
                    if (++found == targets.size())
                        return dists;
                }
                todo.push_back(n);
                visited[n[1]][n[0]] = true;
            }
        }
    }
    return dists;
}

string solve(ifstream & ifs, bool part2) {
    vector<string> ducts;
    map<int, valarray<int>> targets;
    int y = 0; 
    for (string line; getline(ifs, line); ++y) {
        
        for (size_t x = 0; x<line.size(); ++x) {
            char c = line[x];
            if (c != '#' && c != '.')
                targets.insert({c - '0', {(int)x, (int)y}});
        }
        ducts.push_back(line);
    }

    for (auto [key, coords] : targets)
        cout<<"targets: "<< key << " : " << coords[0] << "/" << coords[1] << '\n';

    auto dists = get_dists(targets, ducts);
    for (auto ds: dists) {
        for (auto d : ds)
            cout<<d<<", ";
        cout<<'\n';
    }

    vector<size_t> t_nums;
    for (size_t i = 1; i<targets.size(); ++i)
        t_nums.push_back(i);
    int shortest = INT_MAX;
    do {
        int length = dists[0][t_nums[0]]; 
        for (size_t i = 0; i< t_nums.size() - 1; ++i) {
            length += dists[t_nums[i]][t_nums[i+1]];
        }
        if (part2)
            length += dists[t_nums[t_nums.size()-1]][0];
        shortest = min(shortest, length);
    } while (next_permutation(t_nums.begin(), t_nums.end()));

    return to_string(shortest);
}
string run1(ifstream ifs)
{

    return solve(ifs, false);
}

string run2(ifstream ifs)
{
    return solve(ifs, true);
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
