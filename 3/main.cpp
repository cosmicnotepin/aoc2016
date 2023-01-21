#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


template<typename InputIt>
bool is_triangle(InputIt it) {
    size_t j=0;
    for (; j<3; ++j)
        if (*(it+j) >= *(it + ((j+1) % 3)) + *(it + ((j+2) % 3)))
            break;
    if (j == 3)
        return true;
    return false;
}

string run1(string const filename)
{
    using sri = sregex_iterator;
    ifstream ifs {filename};
    static regex pat {R"(\d+)"};
    int count = 0;
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        vector<int> vals(3);
        transform(it, {}, vals.begin(), [](auto & v) {return stoi(v.str());});
        if (is_triangle(vals.begin()))
            ++count;
    }
    return to_string(count);
}

string run2(string const filename)
{
    using sri = sregex_iterator;
    ifstream ifs {filename};
    static regex pat {R"(\d+)"};
    vector<vector<int>> rds(3);
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        for (auto & v : rds) {
            v.push_back(stoi((*it++).str()));
        }
    }

    int count = 0;
    for (auto v : rds) {
        for (auto it=v.begin(); it<v.end()-2; it+=3) {
            if (is_triangle(it))
                ++count;
        }
    }
    return to_string(count);
}

int main(int argc, char** argv)
{
    for (auto [p,fun] : (pair<string, decltype(&run1)>[]) {{"p1: ", run1}, {"p2: ", run2}}) {
        cout<<p<<'\n';
        for (auto inp : {"tinput", "input"}) {
            auto start = chrono::steady_clock::now();
            auto res = fun(inp);
            auto end = chrono::steady_clock::now();
            chrono::duration<double> time_s = end-start;
            cout<<inp<<": "<<res<<'\n';
            cout<<fixed;
            cout.precision(6);
            cout<<"time: "<<time_s.count()<<'\n';
        }
    }
}
