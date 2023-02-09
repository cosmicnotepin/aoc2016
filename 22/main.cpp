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
// too high 2749
    unordered_map<string, vector<uint32_t>> nodes;
    for (string line; getline(ifs, line);) {
        char nc[8];
        uint32_t size, used, avail, use;
        sscanf(line.c_str(), "/dev/grid/node-%s %uT %uT %uT %u", nc, &size, &used, &avail, &use);
        string node_coords {nc};
        nodes.emplace(std::make_pair(node_coords, vector<uint32_t> {size, used, avail, use}));
    }

    uint32_t viable = 0;
    for (auto [nco, valso] : nodes)
        for (auto [nci, valsi] : nodes) {
            if (nco == nci || valso[1] == 0)
                continue;
            if (valso[1] <= valsi[2])
                ++viable;
        }

    return to_string(viable);
}

struct Node {
    int16_t size;
    int16_t used;
    int16_t avail;
    int16_t use;
};

using Map = vector<vector<Node>>;

vector<array<int16_t, 2>> neighs(Map& map, int16_t x, int16_t y) 
{
    static array<array<int16_t, 2>, 4> neigh_off  {{{-1,0}, {1,0}, {0,1}, {0,-1}}};
    vector<array<int16_t, 2>> neighs;
    for (auto [yo, xo] : neigh_off) {
        int16_t nx = x + xo, ny = y + yo;
        if (nx >= 0 && nx < (int)map[0].size() &&
                ny >= 0 && ny < (int)map.size())
            neighs.push_back({nx, ny});
    }
    
    return neighs;
}

string run2(ifstream ifs)
{
    Map map(25, vector<Node> (37));
    string line;
    getline(ifs, line);
    getline(ifs, line);
    for (; getline(ifs, line);) {
        int32_t x, y, size, used, avail, use;
        sscanf(line.c_str(), "/dev/grid/node-x%u-y%u %uT %uT %uT %u", &x, &y, &size, &used, &avail, &use);
        map[y][x] = {(int16_t)size, (int16_t)used, (int16_t)avail, (int16_t)use};
    }

    uint16_t tx = 36, ty = 0, tused = map[ty][tx].used;
    std::cout<<"tused : "<<tused <<'\n';
    for (int16_t y=0; y<(int)map.size(); ++y) {
        for (int16_t x=0; x<(int)map[0].size(); ++x) {
            if (map[y][x].used == 0) {
                cout<<'_';
                goto cont;
            }
            if (map[y][x].used > 400) {
                cout<<'#';
                goto cont;
            }
            //for (auto [nx, ny] : neighs(map, x, y)) {
            //    if (map[ny][nx].avail >= map[y][x].used) {
            //        cout<<'#';
            //        goto cont;
            //    }
            //}
            cout<<'.';
cont:       ;
        }
        cout<<'\n';
    }
    

    return "did this by hand with the help of the visualization above :)";

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
